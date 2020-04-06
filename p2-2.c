/*
 ============================================================================
 Name        : p2-2.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>

void print1(int *ptr,int rows);

int main(void) {
	printf("----[박지우] [2016031032]------\n");
	int one[]={0,1,2,3,4};

	printf("one=%p\n",one);                  //one 배열의 주소
	printf("&one=%p\n",&one);                //one 배열의 첫번째 원소의 주소
	printf("&one[0]=%p\n",&one[0]);          //one[0]의 주소
	printf("\n");

	print1(&one[0],5);                       //print1함수 호출

	return 0;
}
void print1(int *ptr,int rows){
	int i;
	printf("Address \t contents\n");
	for(i=0;i<rows;i++)
		printf("%p\t %5d\n",ptr+i,*(ptr+i)); //포인터 ptr이 input값 one[0]의 주소 가리키게 대입,연산
	printf("\n");
}
