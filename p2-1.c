/*
 ============================================================================
 Name        : p2-1.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>

#define MAX_SIZE 100
float sum(float[],int);
float input[MAX_SIZE],answer;
int i;
void main(void) {
	printf("----[������] [2016031032]------\n");
	for(i=0;i<MAX_SIZE;i++)
		input[i]=i;              //input �迭�� �� ����

	answer=sum(input,MAX_SIZE);  //sum()�Լ��� return���� answer�� ����
	printf("The sum is %f\n",answer);
}
float sum(float list[],int n){
	int i;
	float tempsum=0;
	for(i=0;i<n;i++)
		tempsum+=list[i];         //�ݺ��� ���� tempsum�� list�迭 ���� ���� ����
	return tempsum;               //main()�Լ��� tempsum�� return������
}
