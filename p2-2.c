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
	printf("----[������] [2016031032]------\n");
	int one[]={0,1,2,3,4};

	printf("one=%p\n",one);                  //one �迭�� �ּ�
	printf("&one=%p\n",&one);                //one �迭�� ù��° ������ �ּ�
	printf("&one[0]=%p\n",&one[0]);          //one[0]�� �ּ�
	printf("\n");

	print1(&one[0],5);                       //print1�Լ� ȣ��

	return 0;
}
void print1(int *ptr,int rows){
	int i;
	printf("Address \t contents\n");
	for(i=0;i<rows;i++)
		printf("%p\t %5d\n",ptr+i,*(ptr+i)); //������ ptr�� input�� one[0]�� �ּ� ����Ű�� ����,����
	printf("\n");
}
