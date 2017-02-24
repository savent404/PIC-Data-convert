// PIC Data convert.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

static void printHelp(void);

int main(int argc, char *argv[])
{
	if (argc < 2 || !strcmp(argv[1], "-h")) {
		printHelp();
	}
    return 0;
}

void printHelp(void)
{
	const char helpstring[] = "PIC Data Convert\n"
		"\n"
		"-T1 \t转换BMP格式文件到Type1:DTA格式（灰阶墨水屏文件格式）\n"
		"-T2 \t转换两个BMP格式文件到Type2:ATD格式（双色墨水屏文件格式）\n"
		"-h  \t帮助文件";
	puts(helpstring);
}
