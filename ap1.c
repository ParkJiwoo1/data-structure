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
    printf("----[������] [2016031032]------\n");
	printf("value of list[0]=%d\n",list[0]);    //list[0]�� ��
	printf("address of list[0]=%p\n",&list[0]); //list[0] �ּ�
	printf("value of list=%p\n",list);          //list[0] �ּ��� ��
	printf("address of list(&list)=%p\n",&list);//list�迭�� �ּ�(�� list[0]�� ������)

	printf("--------------------------\n\n");
	printf("value of list[1]=%d\n",list[1]);     //list[1]�� ��
	printf("address of list[1]=%p\n",&list[1]);  //list[1] �ּ�
	printf("value of *(list+1)=%d\n",*(list+1)); //list[0+1]���� �� ĭ�� ��
	printf("address of list+1=%p\n",(list+1));   //list[0+1]���� �� ĭ�� �ּ�

	printf("--------------------------\n\n");

	printf("value of *plist[0]=%d\n",*plist[0]); //plist[0]�� ����Ű�� �ּ��� ��
	printf("&plist[0]=%p\n",&plist[0]);          //plist[0]�� �ּ�
	printf("&plist=%p\n",&plist);                //plist�迭 ù���� ĭ�� �ּ�
	printf("plist=%p\n",plist);                  //plist�迭�� ����Ű�� �ּ�
	printf("plist[0]=%p\n",plist[0]);            //plist[0]�� ��(==plist[0]�� ����Ű�� �ּ�)
	printf("plist[1]=%p\n",plist[1]);            //plist[1]�� ��(==plist[1]�� ����Ű�� �ּ�)
	printf("plist[2]=%p\n",plist[2]);            //plist[2]�� ��(==plist[2]�� ����Ű�� �ּ�)
	printf("plist[3]=%p\n",plist[3]);            //plist[3]�� ��(==plist[3]�� ����Ű�� �ּ�)
	printf("plist[4]=%p\n",plist[4]);            //plist[4]�� ��(==plist[4]�� ����Ű�� �ּ�)

	free(plist[0]);
}
