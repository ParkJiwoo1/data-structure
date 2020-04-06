/*
 ============================================================================
 Name        : ap2.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int list[5];
	int *plist[5];

	list[0]=10;
	list[1]=11;

	plist[0]=(int*)malloc(sizeof(int));

	printf("----[冠瘤快] [2016031032]------\n");
	printf("list[0]\t=%d\n",list[0]);             //list[0]狼 蔼
	printf("address of list/t=%p\n",list);        //list狼 林家
	printf("address of list[0]/t=%p\n",&list[0]); //list[0]狼 林家
	printf("address of list+0/t=%p\n",list+0);    //list[0+0]狼 林家
	printf("address of list+1/t=%p\n",list+1);    //list[0+1]狼 林家
	printf("address of list+2/t=%p\n",list+2);    //list[0+2]狼 林家
	printf("address of list+3/t=%p\n",list+3);    //list[0+3]狼 林家
	printf("address of list+4/t=%p\n",list+4);    //list[0+4]狼 林家
	printf("address of list[4]/t=%p\n",&list[4]); //list[4]狼 林家

	free(plist[0]);
}
