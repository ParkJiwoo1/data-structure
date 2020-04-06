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
	printf("----[박지우] [2016031032]------\n");
	for(i=0;i<MAX_SIZE;i++)
		input[i]=i;              //input 배열에 값 넣음

	answer=sum(input,MAX_SIZE);  //sum()함수의 return값을 answer에 저장
	printf("The sum is %f\n",answer);
}
float sum(float list[],int n){
	int i;
	float tempsum=0;
	for(i=0;i<n;i++)
		tempsum+=list[i];         //반복문 동안 tempsum에 list배열 값들 덧셈 연산
	return tempsum;               //main()함수로 tempsum값 return시켜줌
}
