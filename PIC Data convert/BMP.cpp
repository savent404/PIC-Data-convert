#include "stdafx.h"
#include "BMP.hpp"

_BMP_Class::_BMP_Class()
{
	fBMP = NULL;
	pBMPColorMap = NULL;
}

_BMP_Class::_BMP_Class(const char * filePath)
{
	fBMP = NULL;
	pBMPColorMap = NULL;
	open(filePath);
}

_BMP_Class::~_BMP_Class()
{
	close();
}

int _BMP_Class::open(const char * filePath)
{
	errno_t e;
	e = fopen_s(&fBMP, filePath, "r");
	if (!e)
		return 0;
	else
		return -1;
}

int _BMP_Class::read(void * des, size_t size)
{
	fread(des, sizeof(char), size, fBMP);
	return 0;
}

int _BMP_Class::seek(uint32_t offset)
{
	fseek(fBMP, get_data_addr() + offset, SEEK_SET);
	return 0;
}

int _BMP_Class::read_format()
{
	if (!fBMP)
		return -1;

	// Header first
	fread_s(&BMP_Header, sizeof(BMP_Header_Typedef_t), sizeof(char), sizeof(BMP_Header_Typedef_t), fBMP);

	// Info then
	fread_s(&BMP_Info, sizeof(BMP_Info_Typedef_t), sizeof(char), sizeof(BMP_Info_Typedef_t), fBMP);

	BMPColorMapCount = get_ClrUsed();
	if (BMPColorMapCount != 0)
	{
		pBMPColorMap = (BMP_ColorMap_Typedef_t*)malloc(sizeof(BMP_ColorMap_Typedef_t) * BMPColorMapCount);
		if (pBMPColorMap == NULL)
			return -1;
		fread_s(pBMPColorMap,
				sizeof(BMP_ColorMap_Typedef_t)*BMPColorMapCount,
				sizeof(BMP_ColorMap_Typedef_t),
				BMPColorMapCount,
				fBMP);
	}
	seek(0);
	return 0;
}

int _BMP_Class::check_format(int level)
{
	switch (level)
	{
	//600*800 或 800*600大小
	//颜色深度2位
	case 0:
		if ((get_w() == 600 && get_h() == 800)||
			(get_w() == 800 && get_h() == 600))
		{
			;
		}
		else
		{
			return -1;
		}
		if (get_ClrUsed() != 4)
		{
			return -1;
		}
		return 0;
	default:
		return -1;
	}
}

int _BMP_Class::close()
{
	if (fBMP != NULL)
	{
		fclose(fBMP);
		fBMP = NULL;
	}
	if (pBMPColorMap != NULL)
	{
		free(pBMPColorMap);
		pBMPColorMap = NULL;
	}
	return 0;
}

uint32_t _BMP_Class::get_file_size()
{
	return uint32_t(BMP_Header.bfSize);
}

uint32_t _BMP_Class::get_data_addr()
{
	return uint32_t(BMP_Header.bfOffBits);
}

uint32_t _BMP_Class::get_h()
{
	return uint32_t(BMP_Info.biHeight);
}

uint32_t _BMP_Class::get_w()
{
	return uint32_t(BMP_Info.biWith);
}

uint32_t _BMP_Class::get_BitCount()
{
	return uint32_t(BMP_Info.biBitCount);
}

uint32_t _BMP_Class::get_SizeImage()
{
	return uint32_t(BMP_Info.biSizeImage);
}

uint32_t _BMP_Class::get_Compression()
{
	return uint32_t(BMP_Info.biCompression);
}

uint32_t _BMP_Class::get_ClrUsed()
{
	return uint32_t(BMP_Info.biClrUsed);
}
