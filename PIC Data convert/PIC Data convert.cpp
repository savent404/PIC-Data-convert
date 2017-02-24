// PIC Data convert.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "BMP.hpp"


#define DEBUG 1

#if DEBUG
void testFunc(void);
#endif


static void printHelp(void);
static int checkInfo(BMP *bmp);
static void printInfo(BMP *bmp);

int main(int argc, char *argv[])
{
#if DEBUG
	testFunc();
	system("pause");
#else
	if (argc < 2 || !strcmp(argv[1], "-h")) {
		printHelp();
	}
	else if (!strcmp(argv[1], "-Info")) {
		if (argc != 3) {
			printf("No FIlePath!!!\n");
			printHelp();
		}
		BMP bmp(argv[2]);
		bmp.read_format();
		printInfo(bmp);
	}
#endif
    return 0;
}

void testFunc(void)
{
	BMP bmp("F:\\BUFFER\\tmp1.bmp");
	bmp.read_format();
	if (!checkInfo(&bmp))
	{
		int i, j;
		int cnt = 0;
		char byte;
		printf("File Data:\n");
		for (i = 0; i < bmp.get_h(); i++)
		{
			for (j = 0; j < bmp.get_w(); j++)
			{
				bmp.read(&byte, 1);
				printf("%02X ", byte);
				if (++cnt > 20)
				{
					putchar('\n'); cnt = 0;
				}
			}
		}
	}
}

void printHelp(void)
{
	const char helpstring[] = "PIC Data Convert\n"
		"\n"
		"-T1            转换BMP格式文件到Type1:DTA格式（灰阶墨水屏文件格式）\n"
		"-T2            转换两个BMP格式文件到Type2:ATD格式（双色墨水屏文件格式）\n"
		"-Info FilePath 查看该图片信息\n"
		"-h             帮助文件\n";
	puts(helpstring);
}
int checkInfo(BMP *bmp)
{
	if (bmp->check_format(0))
	{
		printf("文件格式错误\n");
		printf("当前文件信息:\n");
		printInfo(bmp);
		return -1;
	}
	return 0;
}
void printInfo(BMP *bmp)
{
	printf("\t文件大小:       %.2fKb\n", bmp->get_file_size() / (float)1024);
	printf("\t图片起始偏移量: 0x%x\n", bmp->get_data_addr());
	printf("\t图片高度:       %dbpp\n", bmp->get_h());
	printf("\t图片宽度:       %dbpp\n", bmp->get_w());
	printf("\t颜色深度:       %dbit\n", bmp->get_BitCount());
	printf("\t位图大小:       %.2fKb\n", bmp->get_SizeImage() / (float)1024);
	printf("\t压缩类型:       %d\n", bmp->get_Compression());
	printf("\t颜色个数:       %d\n", bmp->get_ClrUsed());
}