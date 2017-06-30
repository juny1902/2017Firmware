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
	printf("이미지 파일 이름 ? (*.bmp) : ");
	scanf("%s", &file_name);
	printf("출력할 헤더의 이름 ? (*.h) : ");
	scanf("%s", &output_name);
	printf("변수의 이름 ?");
	scanf("%s", &var_name);
	printf("출력할 헤더의 사이즈 ? (size*size) : ");
	scanf("%d", &size);

	FILE *eq, *re;
	eq = fopen(file_name, "rb");		//이진모드로 읽기

	re = fopen(output_name, "wb");		//이진모드로 쓰기

	fseek(eq, 54, SEEK_SET);
	// 스트림 위치 지정
	//fseek(stream, offset, origin)
	//stream : FILE 객체를 가리키는 포인터
	//offset : origin에서 떨어진 위치
	//origin : offset이 더해지는 위치
	//SEEK_SET : 파일의 시작


	fprintf(re, "unsigned short %s[%d*%d] = { ",var_name, size, size);
	//파일에 출력

	for (j = 0; j<size; j++)
	{
		for (i = 0; i<size; i++)
		{
			fread(&B, sizeof(unsigned char), 1, eq);
			fread(&G, sizeof(unsigned char), 1, eq);
			fread(&R, sizeof(unsigned char), 1, eq);

			//fread(ptr, size, count, stream)
			//ptr : size * count 크기를 가지는 배열을 가리키는 포인터
			//size : 읽어들일 원소의 크기, 단위는 byte
			//count : 읽어들일 원소의 개수
			//stream : FILE 객체를 가리키는 포인터


			pixel = ((R >> 3) << 11) | ((G >> 2) << 5) | B >> 3;
			// RGB값을 bit연산을 통해 하나의 변수에 저장
			if (c == 10)
			{
				fprintf(re, "0x%x, \n", pixel);		//파일에 출력
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
	fcloseall();				//파일을 모두 종료
	return;
}

