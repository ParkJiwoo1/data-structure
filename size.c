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

	printf("----[������] [2016031032]------\n");
	printf("sizeof(x)=%lu\n",sizeof(x));    //64��Ʈ ���α׷��̶� 8byte ũ���� �ּ�����
	printf("sizeof(*x)=%lu\n",sizeof(*x));  //64��Ʈ ���α׷��̶� 8byte�� ũ���� �ּ�����
	printf("sizeof(**x)=%lu\n",sizeof(**x));//int���̶� ���� ũ��� 4byte
}
