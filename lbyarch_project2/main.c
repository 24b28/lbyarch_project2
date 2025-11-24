#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

extern double** imgCvtGrayIntToDouble(int n1, int n2, int** pixel, double** result);

double** imgCvtGrayIntToDouble_C(int n1, int n2, int** arr);
bool checkOutput(int n1, int n2, double** asm, double** c);

int main() {
	int n1, n2;
	int i, j;
	printf("Input 2 integers: ");
	if (scanf_s("%d %d", &n1, &n2) != 2 || n1 <= 0 || n2 <= 0) {
		printf("Invalid input.\n");
		return 1;
	}

	int** image = (int**)malloc(n1 * sizeof(int*));
	for (i = 0; i < n1; i++)
		image[i] = (int*)malloc(n2 * sizeof(int));

	srand(time(NULL));

	for (i = 0; i < n1; i++) {
		for (j = 0; j < n2; j++) {
			image[i][j] = rand() % 256;
		}
	}
	double** result = (double**)malloc(n1 * sizeof(double*));

	for (i = 0; i < n1; i++) {
		result[i] = (double*)malloc(n2 * sizeof(double));
	}

	clock_t begin_asm = clock();
	result = imgCvtGrayIntToDouble(n1, n2, image, result);
	clock_t end_asm = clock();
	double time_spent_asm = (double)(end_asm - begin_asm) / CLOCKS_PER_SEC;

	clock_t begin_c = clock();
	double** sample = imgCvtGrayIntToDouble_C(n1, n2, image);
	clock_t end_c = clock();
	double time_spent_c = (double)(end_c - begin_c) / CLOCKS_PER_SEC;

	printf("Correct Output: ");
	if (checkOutput(n1, n2, result, sample)) {
		printf("Yes\n");
	}
	else {
		printf("No\n");
	}

	printf("ASM execution time: %.12lf seconds\n", time_spent_asm);
	printf("C execution time: %.12lf seconds\n", time_spent_c);

	for (i = 0; i < n1; i++) {
		free(image[i]);
		free(result[i]);
		free(sample[i]);
	}
	free(image);
	free(result);
	free(sample);

	return 0;
}

bool checkOutput(int n1, int n2, double** asm, double** c) {
	int i, j;

	bool flag = 1;

	for (i = 0; i < n1; i++) {
		for (j = 0; j < n2; j++) {
			if (fabs(asm[i][j] - c[i][j]) > 0.00001) {
				return false;
			}
		}
	}

	return true;
}

double** imgCvtGrayIntToDouble_C(int n1, int n2, int** arr) {
	int i, j;

	double** image = (double**)malloc(n1 * sizeof(double*));

	for (i = 0; i < n1; i++) {
		image[i] = (double*)malloc(n2 * sizeof(double));
	}
	for (i = 0; i < n1; i++) {
		for (j = 0; j < n2; j++) {
			image[i][j] = arr[i][j] / 255.0;
		}
	}

	return image;
}