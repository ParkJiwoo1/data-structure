/*
 ============================================================================
 Name        : Homework4.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include<time.h>

int** matrix_a, ** matrix_b, ** matrix_sum, ** matrix_sub, ** matrix_t, ** matrix_axt;

int free_matrix(int** matrix, int row, int col) {
	for (int i = 0; i < row; i++) {
		free(matrix[i]);                               //for������ ����� �� �κ� �޸� ����
	}
	free(matrix);                                      //�� �κ� �޸� ����

	return 0;
}
int print_matrix(int** matrix, int row, int col) {

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {

			printf("%d ", matrix[i][j]);                //for������ ����Ȱ� ��ĵ� ���
		}
		printf("\n");
	}
	printf("\n");

	return 0;
}
int multiply_matrix(int** matrix, int** matrix_t, int** matrix_axt, int row, int col) {
	int sum;

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < row; j++) {
			sum = 0;
			for (int k = 0; k < col; k++) {
				sum += matrix[i][k] * matrix_t[k][j];    //sum���ڿ� for���� ���� matrix_a��İ��� matrix_t��� �� ���� ����
			}
			matrix_axt[i][j] = sum;                      //���� ��� matrix_axt��Ŀ� ����

		}
	}
	print_matrix(matrix_axt, row, row);
	return 0;
}
int transpose_matrix(int** matrix, int** matrix_t, int row, int col) {
	int temp = 0;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (row == col) {                               //row�� col�� ������
				if (i == j) {                               //i�� j�� ���ٸ�
					matrix_t[i][j] = matrix[i][j];          //matrix����� i��j������ matrix i�� j���� ����
				}
				else {                                      //i�� j�� �ٸ���
					temp = matrix[i][j];
					matrix_t[i][j] = matrix[j][i];          //matrix_t����� i��j������ matrix����� j�� i���ǰ� �־���
					matrix_t[j][i] = temp;
				}

			}
			else {                                          //row�� col�� �ٸ���
				if (i == j) {                               //i�� j�� ���ٸ�
					matrix_t[i][j] = matrix[i][j];          //matrix����� i��j������ matrix i�� j���� ����
				}
				temp = matrix[i][j];
				matrix_t[j][i] = matrix[i][j];              //matrix_t����� j��i������ matrix����� i�� j���ǰ� �־���
				matrix_t[j][i] = temp;
			}
		}
	}
	if (row == col)                                         //row�� col�� ������
		print_matrix(matrix_t, row, col);                   //matrix_t��� ���
	else                                                    //row�� col�� �ٸ���
		print_matrix(matrix_t, col, row);                   //matrix_t��� ��� �� row�� col�� �ٲ㼭 �Լ� ����
	return 0;
}
int subtraction_matrix(int** matrix, int** matrix_t, int** matrix_sub, int row, int col) {

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			matrix_sub[i][j] = matrix[i][j] - matrix_t[i][j];  //2�� for������ matrix_a��İ� �װ��� ��ġ��� matrix_t�� �� ��������
		}
	}
	print_matrix(matrix_sub, row, col);
	return 0;
}
int addition_matrix(int** matrix, int** matrix_t, int row, int col) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			matrix_sum[i][j] = matrix[i][j] + matrix_t[i][j];  //2�� for������ matrix_a��İ� �װ��� ��ġ��� matrix_t�� �� ��������
		}
	}
	print_matrix(matrix_sum, row, col);
	return 0;
}
int fill_data(int** matrix, int row, int col) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			matrix[i][j] = rand() % 19;                       //2�� for���� �̿��� ��Ŀ� 0~19������ �� ä����
		}
	}
	print_matrix(matrix, row, col);                           //����� ������ִ� �Լ��� �̵�
	return 0;
}


int** create_matrix(int row, int col) {

	if (row <= 0 || col <= 0) {                                //�Է¹޾Ҵ� ���� 0�����̸� ��� ��� �� ����
		printf("Check the sizes of row and col!");
		return NULL;
	}
	else if (row == col) {                                     //row�� col�� ������� �����Ҵ�,�Է¹��� a�� b���� �迭 ����
		matrix_a = (int**)malloc(sizeof(int*) * row);
		matrix_b = (int**)malloc(sizeof(int*) * row);
		matrix_sum = (int**)malloc(sizeof(int*) * row);
		matrix_sub = (int**)malloc(sizeof(int*) * row);
		matrix_t = (int**)malloc(sizeof(int*) * row);
		matrix_axt = (int**)malloc(sizeof(int*) * row);

		for (int i = 0; i < row; i++) {
			matrix_a[i] = (int*)malloc(sizeof(int) * col);
			matrix_b[i] = (int*)malloc(sizeof(int) * col);
			matrix_sum[i] = (int*)malloc(sizeof(int) * col);
			matrix_sub[i] = (int*)malloc(sizeof(int) * col);
			matrix_t[i] = (int*)malloc(sizeof(int) * col);
			matrix_axt[i] = (int*)malloc(sizeof(int) * col);
		}
		printf("matrix_a\n");
		fill_data(matrix_a, row, col);                            //������� �Լ� ����
		printf("matrix_b\n");
		fill_data(matrix_b, col,row);
		printf("matrix_sum\n");
		addition_matrix(matrix_a, matrix_b, row, col);
		printf("matrix_subtraction\n");
		subtraction_matrix(matrix_a, matrix_b, matrix_sub, row, col);
		printf("matrix_transpose\n");
		transpose_matrix(matrix_a, matrix_t, row, col);
		printf("matrix_multiply\n");
		multiply_matrix(matrix_a, matrix_t, matrix_axt, row, col);
	}
	else {                                                             //row�� col�� �ٸ���� �޸� ��ĸ��� �ٸ��� �Ҵ�
		matrix_a = (int**)malloc(sizeof(int*) * row);
		matrix_b = (int**)malloc(sizeof(int*) * col);
		matrix_t = (int**)malloc(sizeof(int*) * col);
		matrix_axt = (int**)malloc(sizeof(int*) * row);
		for (int i = 0; i < col; i++) {
			matrix_b[i] = (int*)malloc(sizeof(int) * row);            //b�� a�� �迭 ����
			matrix_t[i] = (int*)malloc(sizeof(int) * row);            //b�� a�� �迭 ����

		}

		for (int j = 0; j < row; j++) {
			matrix_a[j] = (int*)malloc(sizeof(int) * col);            //a�� b�� �迭 ����
			matrix_axt[j] = (int*)malloc(sizeof(int) * row);          //a�� a�� �迭 ����
		}
		printf("matrix_a\n");
		fill_data(matrix_a, row, col);                                //������� �Լ� ����
		printf("matrix_b\n");
		fill_data(matrix_b, col, row);
		printf("matrix_transpose\n");
    	transpose_matrix(matrix_a, matrix_t, row,col);
		printf("matrix_multiply\n");
		multiply_matrix(matrix_a, matrix_t, matrix_axt, row, col);

	}
                                           //�� ��ĵ��� row�� col�� ũ�⸸ŭ �޸� ����
	free_matrix(matrix_a, row, col);
	free_matrix(matrix_b, col, row);
	if(row==col){                          //row�� col�� �ٸ��� ��� ���� �ٸ� ��ĳ����� ������ ������ ������ �Ұ��� �޸� �Ҵ���������
		free_matrix(matrix_sum, row, col); //���� �޸� ������ row��col���� �������� ����
		free_matrix(matrix_sub, row, col);
		}
	free_matrix(matrix_t, col, row);
	free_matrix(matrix_axt, row, row);



	return 0;
}
int main(void) {
	float a , b;
	srand(time(NULL));
	scanf("%f %f", &a,&b);                        //�Ǽ��� �Է°���
	printf("\n");
	printf("[----������----2016031032----]\n");
	create_matrix((int)a, (int)b);                //�Լ� ���� �� �Ǽ� �Է½� �Ҽ��� �������� ������ ��ȯ
	return 0;
}
