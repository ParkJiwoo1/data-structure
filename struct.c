/*
 ============================================================================
 Name        : struct.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>

struct student1{          //student1�̶�� ����ü ����
	char lastname;
	int studentID;
	char grade;
};

typedef struct{          //student2��� ����ü ����
	char lastname;       //typedef�� struct Ű������� ����ü ����
		int studentID;
		char grade;
} student2;

int main(void) {
	struct student1 st1={'A',100,'A'};

	printf("----[������] [2016031032]------\n");
	printf("st1.lastname=%c\n",st1.lastname);
	printf("st1.studentID=%d\n",st1.studentID);
	printf("st1.grade=%c\n",st1.grade);

	student2 st2={'8',200,'B'};

	printf("\nst2.lastname=%c\n",st2.lastname);
	printf("st2.studentID=%d\n",st2.studentID);
	printf("st2.grade=%c\n",st2.grade);

	student2 st3;
	st3=st2;             //����ġȯ

	printf("\nst3.lastname=%c\n",st3.lastname);
	printf("st3.studentID=%d\n",st3.studentID);
	printf("st3.grade=%c\n",st3.grade);
}
