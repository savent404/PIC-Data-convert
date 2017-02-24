#ifndef _BMP_HPP_
#define _BMP_HPP_

#include <stdint.h>
#include <stdio.h>
#include <iostream>

#pragma pack(push)
#pragma pack(2)

typedef struct _BMP_Header_Structure{
	char bfType[2];		//位图文件类型
	uint32_t bfSize;	//位图文件大小
	uint16_t Reserved1;	//保留
	uint16_t Reserved2;	//保留
	uint32_t bfOffBits; //位图数据起始位置
}BMP_Header_Typedef_t;

typedef struct _BMP_Info_Structure {
	uint32_t biSize;	//本结构体占用字节
	uint32_t biWith;	//位图宽度
	uint32_t biHeight;	//位图高度
	uint16_t biPlanes;	//目标设备的级别
	uint16_t biBitCount;//像素位数
	uint32_t biCompression;//压缩类型
	uint32_t biSizeImage;//位图大小，包含字节对齐的空字节
	uint32_t biXPelsPerMeter;//位图水平分辨率
	uint32_t biYPelsPerMeter;//位图垂直分辨率
	uint32_t biClrUsed;	//位图实际使用的颜色表中的颜色数
	uint32_t biClrImportant;//位图显示过程中重要的颜色数
} BMP_Info_Typedef_t;

typedef struct _BMP_ColorMap_Structure {
	uint8_t rgbB;
	uint8_t rgbG;
	uint8_t rgbR;
	uint8_t Reserved;
} BMP_ColorMap_Typedef_t;

#pragma pack(pop)

typedef uint32_t BMP_ColorMapCount_Typedef_t;


typedef class _BMP_Class {
private:
	BMP_Header_Typedef_t	BMP_Header;
	BMP_Info_Typedef_t		BMP_Info;
	BMP_ColorMap_Typedef_t	*pBMPColorMap;
	BMP_ColorMapCount_Typedef_t BMPColorMapCount;
	FILE					*fBMP;
public:
	_BMP_Class();
	_BMP_Class(const char *filePath);
	~_BMP_Class();

	int open(const char *filePath);
	int read(void *des, size_t size);
	int seek(uint32_t offset);
	int read_format();
	/**
	 * Brief: 按照定义严格性判断文件是否符合要求，
	          以达到后期扩展如：自动完成颜色转换的功能
			                    自动完成画布延伸
			  而不再严格要求图片颜色深度为2位
	 * Para: @level = 0; 要求 宽高为600*800 或 800*600, 颜色深度2位
	 */
	int check_format(int level);
	int close();

	// Information Get

	/**
	 * Brief: 得到文件大小
	 */
	uint32_t get_file_size();

	/**
	 * Brief: 得到图片数据起始偏移量
	 */
	uint32_t get_data_addr();

	/**
	 * Brief: 得到图片高度
	 */
	uint32_t get_h();

	/**
	 * Brief: 得到图片宽度
	 */
	uint32_t get_w();

	/**
	 * Brief: 得到像素位数
	 */
	uint32_t get_BitCount();

	/**
	 * Brief: 得到位图大小
	 */
	uint32_t get_SizeImage();

	/**
	 * Brief: 得到压缩类型
	 */
	uint32_t get_Compression();

	/**
	 * Brief: 得到位图使用颜色个数
	 */
	uint32_t get_ClrUsed();

} BMP;


#endif
