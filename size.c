/*
 ============================================================================
 Name        : size.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

void main() {
	int **x;

	printf("----[박지우] [2016031032]------\n");
	printf("sizeof(x)=%lu\n",sizeof(x));    //64비트 프로그램이라 8byte 크기의 주소저장
	printf("sizeof(*x)=%lu\n",sizeof(*x));  //64비트 프로그램이라 8byte의 크기의 주소저장
	printf("sizeof(**x)=%lu\n",sizeof(**x));//int형이라 값의 크기는 4byte
}
