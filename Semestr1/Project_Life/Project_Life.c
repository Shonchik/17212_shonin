#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

int main() {

	FILE *myfile;
	myfile = fopen ("input.txt", "r");

	int size = 400;
	int a = 0;
	int count = 0;
	int *matr;
	int *matr2;

	matr = (int*) malloc (size * sizeof(int));
	matr2 = (int*) malloc (size * sizeof(int));

	for (int i = 0; i < size; i++) {
		fscanf (myfile, "%d", &matr[i]);
		matr2[i] = matr[i];
	}

	while (a == 0) {

		for (int i = 0; i < size / 20; i++) {
			for (int j = 0; j < size / 20; j++) {
				count = 0;
				if (matr[i * 20 + j] == 1) {
					if (matr[i * 20 + j - 1] == 1) {
						count++;
					}
					if (matr[i * 20 + j + 1] == 1) {
						count++;
					}
					if (matr[(i - 1) * 20 + j] == 1) {
						count++;
					}
					if (matr[(i + 1) * 20 + j - 1] == 1) {
						count++;
					}	
					if (matr[(i + 1) * 20 + j - 1] == 1) {
						count++;
					}
					if (matr[(i + 1) * 20 + j + 1] == 1) {
						count++;
					}
					if (matr[(i - 1) * 20 + j + 1] == 1) {
						count++;
					}
					if (matr[(i - 1) * 20 + j - 1] == 1) {
						count++;
					}
					if ((count == 2) || (count == 3)) {
						matr2[i * 20 + j] = 1;
					} else {
						matr2[i * 20 + j] = 0;
					}
				} else {
					if (matr[i * 20 + j - 1] == 1) {
						count++;
					}
					if (matr[i * 20 + j + 1] == 1) {
						count++;
					}
					if (matr[(i - 1) * 20 + j] == 1) {
						count++;
					}
					if (matr[(i + 1) * 20 + j - 1] == 1) {
						count++;
					}	
					if (matr[(i + 1) * 20 + j - 1] == 1) {
						count++;
					}
					if (matr[(i + 1) * 20 + j + 1] == 1) {
						count++;
					}
					if (matr[(i - 1) * 20 + j + 1] == 1) {
						count++;
					}
					if (matr[(i - 1) * 20 + j - 1] == 1) {
						count++;
					}
					if (count == 3) {
						matr2[i * 20 + j] = 1;
					} else {
						matr2[i * 20 + j] = 0;
					}
				}
			}
		}

		for (int j = 0; j < size; j++) {
			matr[j] = matr2[j];
		}

		for (int i = 0; i < size / 20; i++) {
			for (int j = 0; j < size / 20; j++) {
				printf ("%d ", matr[i * 20 + j]);
			}
			printf ("\n");
		}

		scanf ("%d", &count);
	}

	

	fclose (myfile);

}