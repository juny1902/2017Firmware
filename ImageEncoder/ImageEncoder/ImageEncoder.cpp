#pragma warning(disable:4996)
#include<stdio.h>


unsigned short R;
unsigned short G;
unsigned short B;
unsigned short pixel;

void main(void)
{
	int i = 0, j = 0, size;
	int c = 0;
	int x, y;
	char file_name[30];
	char output_name[30];
	char var_name[30];
	printf("�̹��� ���� �̸� ? (*.bmp) : ");
	scanf("%s", &file_name);
	printf("����� ����� �̸� ? (*.h) : ");
	scanf("%s", &output_name);
	printf("������ �̸� ?");
	scanf("%s", &var_name);
	printf("����� ����� ������ ? (size*size) : ");
	scanf("%d", &size);

	FILE *eq, *re;
	eq = fopen(file_name, "rb");		//�������� �б�

	re = fopen(output_name, "wb");		//�������� ����

	fseek(eq, 54, SEEK_SET);
	// ��Ʈ�� ��ġ ����
	//fseek(stream, offset, origin)
	//stream : FILE ��ü�� ����Ű�� ������
	//offset : origin���� ������ ��ġ
	//origin : offset�� �������� ��ġ
	//SEEK_SET : ������ ����


	fprintf(re, "unsigned short %s[%d*%d] = { ",var_name, size, size);
	//���Ͽ� ���

	for (j = 0; j<size; j++)
	{
		for (i = 0; i<size; i++)
		{
			fread(&B, sizeof(unsigned char), 1, eq);
			fread(&G, sizeof(unsigned char), 1, eq);
			fread(&R, sizeof(unsigned char), 1, eq);

			//fread(ptr, size, count, stream)
			//ptr : size * count ũ�⸦ ������ �迭�� ����Ű�� ������
			//size : �о���� ������ ũ��, ������ byte
			//count : �о���� ������ ����
			//stream : FILE ��ü�� ����Ű�� ������


			pixel = ((R >> 3) << 11) | ((G >> 2) << 5) | B >> 3;
			// RGB���� bit������ ���� �ϳ��� ������ ����
			if (c == 10)
			{
				fprintf(re, "0x%x, \n", pixel);		//���Ͽ� ���
				c = 0;
			}
			else
			{
				fprintf(re, "0x%x, ", pixel);
				c++;
			}

		}
	}

	fseek(re, -2, SEEK_END);
	fprintf(re, "};");
	fcloseall();				//������ ��� ����
	return;
}

