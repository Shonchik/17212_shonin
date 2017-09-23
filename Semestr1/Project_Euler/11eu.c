#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

int main()
{
	
	int max_product = 0;
	int matr[20][20] = {0};
	int product = 0;

	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			scanf ("%d", &matr[i][j]);
		}
	}

	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			if (i <= 16) {
				product = matr[i][j] * matr[i + 1][j] * matr[i + 2][j] * matr[i + 3][j];
				if (product > max_product) {
					max_product = product;
				}
			}
			if (i >= 3) {
				product = matr[i][j] * matr[i - 1][j] * matr[i - 2][j] * matr[i - 3][j];
				if (product > max_product) {
					max_product = product;
				}
			}
			if (j <= 16) {
				product = matr[i][j] * matr[i][j + 1] * matr[i][j + 2] * matr[i][j + 3];
				if (product > max_product) {
					max_product = product;
				}
			}
			if (j >= 3) {
				product = matr[i][j] * matr[i][j - 1] * matr[i][j - 2] * matr[i][j - 3];
				if (product > max_product) {
					max_product = product;
				}
			}
			if ((i <= 16) && (j <= 16)) {
				product = matr[i][j] * matr[i + 1][j + 1] * matr[i + 2][j + 2] * matr[i + 3][j + 3];
				if (product > max_product) {
					max_product = product;
				}
			}
			if ((i >= 3) && (j <= 16)) {
				product = matr[i][j] * matr[i - 1][j + 1] * matr[i - 2][j + 2] * matr[i - 3][j + 3];
				if (product > max_product) {
					max_product = product;
				}
			}
		}
	}

	printf("%d", max_product);

}