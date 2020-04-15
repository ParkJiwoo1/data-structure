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
		free(matrix[i]);                               //for문으로 행렬의 열 부분 메모리 해제
	}
	free(matrix);                                      //행 부분 메모리 해제

	return 0;
}
int print_matrix(int** matrix, int row, int col) {

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {

			printf("%d ", matrix[i][j]);                //for문으로 저장된건 행렬들 출력
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
				sum += matrix[i][k] * matrix_t[k][j];    //sum인자에 for문을 통해 matrix_a행렬값과 matrix_t행렬 값 연산 저장
			}
			matrix_axt[i][j] = sum;                      //연산 결과 matrix_axt행렬에 저장

		}
	}
	print_matrix(matrix_axt, row, row);
	return 0;
}
int transpose_matrix(int** matrix, int** matrix_t, int row, int col) {
	int temp = 0;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (row == col) {                               //row와 col이 같을때
				if (i == j) {                               //i와 j가 같다면
					matrix_t[i][j] = matrix[i][j];          //matrix행렬의 i행j열값은 matrix i행 j열과 같다
				}
				else {                                      //i와 j가 다르면
					temp = matrix[i][j];
					matrix_t[i][j] = matrix[j][i];          //matrix_t행렬의 i행j열값에 matrix행렬의 j행 i열의값 넣어줌
					matrix_t[j][i] = temp;
				}

			}
			else {                                          //row와 col이 다를때
				if (i == j) {                               //i와 j가 같다면
					matrix_t[i][j] = matrix[i][j];          //matrix행렬의 i행j열값은 matrix i행 j열과 같다
				}
				temp = matrix[i][j];
				matrix_t[j][i] = matrix[i][j];              //matrix_t행렬의 j행i열값에 matrix행렬의 i행 j열의값 넣어줌
				matrix_t[j][i] = temp;
			}
		}
	}
	if (row == col)                                         //row와 col이 같을때
		print_matrix(matrix_t, row, col);                   //matrix_t행렬 출력
	else                                                    //row와 col이 다를때
		print_matrix(matrix_t, col, row);                   //matrix_t행렬 출력 시 row와 col값 바꿔서 함수 실행
	return 0;
}
int subtraction_matrix(int** matrix, int** matrix_t, int** matrix_sub, int row, int col) {

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			matrix_sub[i][j] = matrix[i][j] - matrix_t[i][j];  //2중 for문으로 matrix_a행렬과 그것의 전치행렬 matrix_t의 값 뺄셈연산
		}
	}
	print_matrix(matrix_sub, row, col);
	return 0;
}
int addition_matrix(int** matrix, int** matrix_t, int row, int col) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			matrix_sum[i][j] = matrix[i][j] + matrix_t[i][j];  //2중 for문으로 matrix_a행렬과 그것의 전치행렬 matrix_t의 값 덧셈연산
		}
	}
	print_matrix(matrix_sum, row, col);
	return 0;
}
int fill_data(int** matrix, int row, int col) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			matrix[i][j] = rand() % 19;                       //2중 for문을 이용해 행렬에 0~19사이의 값 채워줌
		}
	}
	print_matrix(matrix, row, col);                           //결과값 출력해주는 함수로 이동
	return 0;
}


int** create_matrix(int row, int col) {

	if (row <= 0 || col <= 0) {                                //입력받았던 값이 0이하이면 경고 출력 후 종료
		printf("Check the sizes of row and col!");
		return NULL;
	}
	else if (row == col) {                                     //row와 col이 같을경우 동적할당,입력받은 a행 b열의 배열 생성
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
		fill_data(matrix_a, row, col);                            //순서대로 함수 구현
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
	else {                                                             //row와 col이 다를경우 메모리 행렬마다 다르게 할당
		matrix_a = (int**)malloc(sizeof(int*) * row);
		matrix_b = (int**)malloc(sizeof(int*) * col);
		matrix_t = (int**)malloc(sizeof(int*) * col);
		matrix_axt = (int**)malloc(sizeof(int*) * row);
		for (int i = 0; i < col; i++) {
			matrix_b[i] = (int*)malloc(sizeof(int) * row);            //b행 a열 배열 생성
			matrix_t[i] = (int*)malloc(sizeof(int) * row);            //b행 a열 배열 생성

		}

		for (int j = 0; j < row; j++) {
			matrix_a[j] = (int*)malloc(sizeof(int) * col);            //a행 b열 배열 생성
			matrix_axt[j] = (int*)malloc(sizeof(int) * row);          //a행 a열 배열 생성
		}
		printf("matrix_a\n");
		fill_data(matrix_a, row, col);                                //순서대로 함수 구현
		printf("matrix_b\n");
		fill_data(matrix_b, col, row);
		printf("matrix_transpose\n");
    	transpose_matrix(matrix_a, matrix_t, row,col);
		printf("matrix_multiply\n");
		multiply_matrix(matrix_a, matrix_t, matrix_axt, row, col);

	}
                                           //각 행렬들을 row행 col열 크기만큼 메모리 해제
	free_matrix(matrix_a, row, col);
	free_matrix(matrix_b, col, row);
	if(row==col){                          //row와 col이 다를시 행과 열이 다른 행렬끼리는 연산이 덧셈과 뺄셈이 불가해 메모리 할당하지않음
		free_matrix(matrix_sum, row, col); //따라서 메모리 해제도 row와col값이 같을때만 실행
		free_matrix(matrix_sub, row, col);
		}
	free_matrix(matrix_t, col, row);
	free_matrix(matrix_axt, row, row);



	return 0;
}
int main(void) {
	float a , b;
	srand(time(NULL));
	scanf("%f %f", &a,&b);                        //실수도 입력가능
	printf("\n");
	printf("[----박지우----2016031032----]\n");
	create_matrix((int)a, (int)b);                //함수 구현 전 실수 입력시 소수점 버림으로 정수형 변환
	return 0;
}
