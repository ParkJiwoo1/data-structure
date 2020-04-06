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
	char lastname[13];   //13byte 공간 차지하나 padding으로 인해 16byte 차지
	int dtudentID;       //4byte 차지
	short grade;         //2byte 공간 차지하나 padding으로 인해 4byte 차지
};

int main(void) {
	struct student pst;

	printf("----[박지우] [2016031032]------\n");
	printf("size of student=%ld\n",sizeof(struct student)); //padding처리로인해 16+4+4=24byte
	printf("size of int=%ld\n",sizeof(int));
	printf("size of short=%ld\n",sizeof(short));

	return 0;
}
