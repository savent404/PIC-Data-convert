// PIC Data convert.cpp : �������̨Ӧ�ó������ڵ㡣
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
		"-T1 \tת��BMP��ʽ�ļ���Type1:DTA��ʽ���ҽ�īˮ���ļ���ʽ��\n"
		"-T2 \tת������BMP��ʽ�ļ���Type2:ATD��ʽ��˫ɫīˮ���ļ���ʽ��\n"
		"-h  \t�����ļ�";
	puts(helpstring);
}
