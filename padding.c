/*
 ============================================================================
 Name        : padding.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>

struct student{
	char lastname[13];   //13byte ���� �����ϳ� padding���� ���� 16byte ����
	int dtudentID;       //4byte ����
	short grade;         //2byte ���� �����ϳ� padding���� ���� 4byte ����
};

int main(void) {
	struct student pst;

	printf("----[������] [2016031032]------\n");
	printf("size of student=%ld\n",sizeof(struct student)); //paddingó�������� 16+4+4=24byte
	printf("size of int=%ld\n",sizeof(int));
	printf("size of short=%ld\n",sizeof(short));

	return 0;
}
