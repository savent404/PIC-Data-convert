// PIC Data convert.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "BMP.hpp"
#include "DTA.hpp"

#define DEBUG 0

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
			return 0;
		}
		BMP bmp(argv[2]);
		bmp.read_format();
		printInfo(&bmp);
	}

	else if (!strcmp(argv[1], "-T1")) {
		if (argc != 4) {
			printf("Wrong Parameter!!!\n");
			printHelp();
			return 0;
		}
		BMP bmp(argv[2]);
		bmp.read_format();
		if (!checkInfo(&bmp))
		{
			DTA dta(DTA_2BPP);
			char buffer[400];
			dta.create(argv[3]);
			
			//ÿ�ζ�ȡһ��
			for (int i = 0; i < 600; i++)
			{
				bmp.read(buffer, 400);
				dta.write(buffer, 400);
			}
			printf("Convert compelet\n");
			dta.close();
			return 0;
		}
	}

	else if (!strcmp(argv[1], "-T2")) {
		printf("��δ�����������ڴ�\n");
		return 0;
	}
	else {
		printf("����Ĳ���\n");
		printHelp();
		return 0;
	}
#endif
    return 0;
}


void printHelp(void)
{
	const char helpstring[] = "PIC Data Convert\n"
		"\n"
		"-T1            ת��BMP��ʽ�ļ���Type1:DTA��ʽ���ҽ�īˮ���ļ���ʽ��\n"
		"-T2            ת������BMP��ʽ�ļ���Type2:ATD��ʽ��˫ɫīˮ���ļ���ʽ��\n"
		"-Info FilePath �鿴��ͼƬ��Ϣ\n"
		"-h             �����ļ�\n";
	puts(helpstring);
}
int checkInfo(BMP *bmp)
{
	if (bmp->check_format(0))
	{
		printf("�ļ���ʽ����\n");
		printf("��ǰ�ļ���Ϣ:\n");
		printInfo(bmp);
		return -1;
	}
	return 0;
}
void printInfo(BMP *bmp)
{
	printf("\t�ļ���С:       %.2fKb\n", bmp->get_file_size() / (float)1024);
	printf("\tͼƬ��ʼƫ����: 0x%x\n", bmp->get_data_addr());
	printf("\tͼƬ�߶�:       %dbpp\n", bmp->get_h());
	printf("\tͼƬ���:       %dbpp\n", bmp->get_w());
	printf("\t��ɫ���:       %dbit\n", bmp->get_BitCount());
	printf("\tλͼ��С:       %.2fKb\n", bmp->get_SizeImage() / (float)1024);
	printf("\tѹ������:       %d\n", bmp->get_Compression());
	printf("\t��ɫ����:       %d\n", bmp->get_ClrUsed());
}