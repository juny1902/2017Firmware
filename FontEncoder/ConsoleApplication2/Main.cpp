#pragma warning(disable:4996)
#include<stdio.h>

unsigned char dot;

void main(void)
{
	int i = 0, j = 0;
	int c = 0;
	int _FONT_SIZE = 0;
	char _INPUT_NAME[20] = { 0, };
	char _OUTPUT_NAME[20] = { 0 , };
	char _VAR_NAME[20] = { 0 , };
	FILE *eq, *re;
	printf("�Է� ���� �� (*.bmp) : ");
	scanf("%s", &_INPUT_NAME);
	printf("��� ���� �� (*.h) : ");
	scanf("%s", &_OUTPUT_NAME);
	printf("���� �� : ");
	scanf("%s", &_VAR_NAME);
	printf("��Ʈ ũ�� ? (n X n) : ");
	scanf("%d", &_FONT_SIZE);
	eq = fopen(_INPUT_NAME, "rb");		//�������� �б�
	
	
	re = fopen(_OUTPUT_NAME, "wb");		//�������� ����

	fseek(eq, 54, SEEK_SET);

	fprintf(re, "unsigned int %s[%d] = { ", _VAR_NAME,_FONT_SIZE);
	//���Ͽ� ���

	for (j = 0; j<_FONT_SIZE; j++)
	{

		unsigned int temp = 0;

		for (i = 0; i<_FONT_SIZE; i++)
		{

			fread(&dot, sizeof(unsigned char), 1, eq);
			fread(&dot, sizeof(unsigned char), 1, eq);
			fread(&dot, sizeof(unsigned char), 1, eq);

			if (dot > 0) {
				temp = temp << 1;
			}
			else {
				temp = temp | 1;
				temp = temp << 1;
			}

			if (i == _FONT_SIZE - 1) {
				fprintf(re, "0x%x, ",temp);
			}


		}
	}

	fseek(re, -2, SEEK_END);
	fprintf(re, "};");
	fcloseall();				//������ ��� ����
	return;
}

