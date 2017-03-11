#ifndef _DTA_HPP_
#define _DTA_HPP_

#include <stdint.h>
#include <stdio.h>

typedef enum {
	DTA_2BPP = 2,
} DTA_FORMAT;

typedef class _DTA_Class {
private:
	DTA_FORMAT Format;
	FILE *pf;

	uint8_t convert_2BPP22BPP(uint16_t data);
public:
	_DTA_Class();
	_DTA_Class(DTA_FORMAT format);
	_DTA_Class(DTA_FORMAT format, const char *path);
	~_DTA_Class();

	void set_format(DTA_FORMAT format);
	void create(const char *FilePath);
	void write(void *src, size_t size);
	void write_string(const char* pt, size_t size);
	void close();
}DTA;


#endif
