#include "stdafx.h"
#include "DTA.hpp"

uint8_t _DTA_Class::convert_2BPP22BPP(uint16_t data)
{
	//for (int i = 0; i < 4; i++) {
	//	uint8_t buf = (data >> (i * 4)) & 0x03;
	//	ret |= (buf << (i * 2));
	//}
	uint8_t ret = 0;

	ret |= ((data & 0x3000) >> 12) << 2;
	ret |= ((data & 0x0300) >> 8) << 0;
	ret |= ((data & 0x0030) >> 4) << 6;
	ret |= ((data & 0x0003) >> 0) << 4;
	return uint8_t(ret);
}

_DTA_Class::_DTA_Class()
{
	pf = NULL;
	set_format(DTA_2BPP);
}

_DTA_Class::_DTA_Class(DTA_FORMAT format)
{
	pf = NULL;
	set_format(format);
}

_DTA_Class::_DTA_Class(DTA_FORMAT format, const char * path)
{
	pf = NULL;
	set_format(format);
	create(path);
}

_DTA_Class::~_DTA_Class()
{
	close();
}

void _DTA_Class::set_format(DTA_FORMAT format)
{
	Format = format;
}

void _DTA_Class::create(const char * FilePath)
{
	fopen_s(&pf, FilePath, "w");
}

void _DTA_Class::write(void * src, size_t size)
{
	size_t real_size;
	uint8_t *dpt = (uint8_t*)src;
	uint8_t *spt = (uint8_t*)src;

	switch (Format)
	{
	case DTA_2BPP:
		for (size_t i = 0; i < size; i+=2) {
			*dpt = convert_2BPP22BPP(*(uint16_t*)spt);
			dpt += 1;
			spt += 2;
		}
		real_size = size / 2;
		break;
	default:
		break;
	}
	fwrite(src, sizeof(char), real_size, pf);
}

void _DTA_Class::close()
{
	if (pf != NULL)
		fclose(pf);
	pf = NULL;
}
