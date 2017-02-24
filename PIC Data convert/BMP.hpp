#ifndef _BMP_HPP_
#define _BMP_HPP_

#include <stdint.h>
#include <stdio.h>
#include <iostream>

#pragma pack(push)
#pragma pack(2)

typedef struct _BMP_Header_Structure{
	char bfType[2];		//λͼ�ļ�����
	uint32_t bfSize;	//λͼ�ļ���С
	uint16_t Reserved1;	//����
	uint16_t Reserved2;	//����
	uint32_t bfOffBits; //λͼ������ʼλ��
}BMP_Header_Typedef_t;

typedef struct _BMP_Info_Structure {
	uint32_t biSize;	//���ṹ��ռ���ֽ�
	uint32_t biWith;	//λͼ���
	uint32_t biHeight;	//λͼ�߶�
	uint16_t biPlanes;	//Ŀ���豸�ļ���
	uint16_t biBitCount;//����λ��
	uint32_t biCompression;//ѹ������
	uint32_t biSizeImage;//λͼ��С�������ֽڶ���Ŀ��ֽ�
	uint32_t biXPelsPerMeter;//λͼˮƽ�ֱ���
	uint32_t biYPelsPerMeter;//λͼ��ֱ�ֱ���
	uint32_t biClrUsed;	//λͼʵ��ʹ�õ���ɫ���е���ɫ��
	uint32_t biClrImportant;//λͼ��ʾ��������Ҫ����ɫ��
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
	 * Brief: ���ն����ϸ����ж��ļ��Ƿ����Ҫ��
	          �Դﵽ������չ�磺�Զ������ɫת���Ĺ���
			                    �Զ���ɻ�������
			  �������ϸ�Ҫ��ͼƬ��ɫ���Ϊ2λ
	 * Para: @level = 0; Ҫ�� ���Ϊ600*800 �� 800*600, ��ɫ���2λ
	 */
	int check_format(int level);
	int close();

	// Information Get

	/**
	 * Brief: �õ��ļ���С
	 */
	uint32_t get_file_size();

	/**
	 * Brief: �õ�ͼƬ������ʼƫ����
	 */
	uint32_t get_data_addr();

	/**
	 * Brief: �õ�ͼƬ�߶�
	 */
	uint32_t get_h();

	/**
	 * Brief: �õ�ͼƬ���
	 */
	uint32_t get_w();

	/**
	 * Brief: �õ�����λ��
	 */
	uint32_t get_BitCount();

	/**
	 * Brief: �õ�λͼ��С
	 */
	uint32_t get_SizeImage();

	/**
	 * Brief: �õ�ѹ������
	 */
	uint32_t get_Compression();

	/**
	 * Brief: �õ�λͼʹ����ɫ����
	 */
	uint32_t get_ClrUsed();

} BMP;


#endif
