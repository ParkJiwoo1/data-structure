/*
 ============================================================================
 Name        : ap1.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
	int list[5];
	int *plist[5]={NULL,};

	plist[0]=(int *)malloc(sizeof(int));

	list[0]=1;
	list[1]=100;

	*plist[0]=200;
    printf("----[박지우] [2016031032]------\n");
	printf("value of list[0]=%d\n",list[0]);    //list[0]의 값
	printf("address of list[0]=%p\n",&list[0]); //list[0] 주소
	printf("value of list=%p\n",list);          //list[0] 주소의 값
	printf("address of list(&list)=%p\n",&list);//list배열의 주소(즉 list[0]과 같은말)

	printf("--------------------------\n\n");
	printf("value of list[1]=%d\n",list[1]);     //list[1]의 값
	printf("address of list[1]=%p\n",&list[1]);  //list[1] 주소
	printf("value of *(list+1)=%d\n",*(list+1)); //list[0+1]연산 한 칸의 값
	printf("address of list+1=%p\n",(list+1));   //list[0+1]연산 한 칸의 주소

	printf("--------------------------\n\n");

	printf("value of *plist[0]=%d\n",*plist[0]); //plist[0]이 가리키는 주소의 값
	printf("&plist[0]=%p\n",&plist[0]);          //plist[0]의 주소
	printf("&plist=%p\n",&plist);                //plist배열 첫번쨰 칸의 주소
	printf("plist=%p\n",plist);                  //plist배열이 가리키는 주소
	printf("plist[0]=%p\n",plist[0]);            //plist[0]의 값(==plist[0]이 가리키는 주소)
	printf("plist[1]=%p\n",plist[1]);            //plist[1]의 값(==plist[1]이 가리키는 주소)
	printf("plist[2]=%p\n",plist[2]);            //plist[2]의 값(==plist[2]이 가리키는 주소)
	printf("plist[3]=%p\n",plist[3]);            //plist[3]의 값(==plist[3]이 가리키는 주소)
	printf("plist[4]=%p\n",plist[4]);            //plist[4]의 값(==plist[4]이 가리키는 주소)

	free(plist[0]);
}
