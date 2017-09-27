#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

int *create_matr (int *height, int *width, int *rule_burn, int *rule_survive, char name_infile[256]) {

	FILE *myfile;
	myfile = fopen (name_infile, "r");

	if (NULL == myfile) {
		return NULL;
	}

	int *mat = NULL;
	int i = 0;
	int j = 0;

	fscanf (myfile, "#R B%d/S%d\n", rule_burn, rule_survive);
	fscanf (myfile, "#Size %d %d", height, width);
 
	mat = (int*) calloc (*width * *height, sizeof(int));

	while (feof(myfile) == 0) {
		fscanf (myfile, "%d %d\n", &i, &j);
		*(mat + i * *height + j) = 1; 
	}

	fclose (myfile);

	return (mat);

}

int count_neighbours(int *matr, int i, int j, int *height) {

	int count = 0;

	if (*(matr + i * *height + j + 1) == 1) {
		count++;
	}
	if (*(matr + i * *height + j - 1) == 1) {
		count++;
	}
	if (*(matr + (i + 1) * *height + j) == 1) {
		count++;
	}
	if (*(matr + (i - 1) * *height + j) == 1) {
		count++;
	}
	if (*(matr + (i + 1) * *height + j + 1) == 1) {
		count++;
	}
	if (*(matr + (i - 1) * *height + j + 1) == 1) {
		count++;
	}
	if (*(matr + (i + 1) * *height + j - 1) == 1) {
		count++;
	}
	if (*(matr + (i - 1) * *height + j - 1) == 1) {
		count++;
	}

	return count;

}

int main() {

	int *matr = NULL;
	int *matr2 = NULL;
	int width = 0;
	int rule_burn = 0;
	int rule_survive = 0;
	int count_sosedi = 0;
	int height = 0;
	char name_infile[256];

	printf ("Write please name input file!\n");

	scanf ("%s", name_infile);

	matr = create_matr(&height, &width, &rule_burn, &rule_survive, name_infile);
	matr2 = create_matr(&height, &width, &rule_burn, &rule_survive, name_infile);

	if (NULL == matr) {
		printf ("Could not create malloc!");
		return 0;
	}

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			count_sosedi = count_neighbours(matr, i, j, &height);
			if (*(matr2 + i * height + j) == 1) {
				if (count_sosedi == 2) {
					*(matr2 + i * height + j) = 1;
				} else if (count_sosedi == 3) {
					*(matr2 + i * height + j) = 1;
				} else {
					*(matr2 + i * height + j) = 0;
				}
			} else {
				if (count_sosedi == 3) {
					*(matr2 + i * height + j) = 1;
				}
			}
		}
	}

	for (int j = 0; j < width * height; j++) {
		*(matr + j) = *(matr2 + j);
	}

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			printf("%d ", *(matr + i * height + j));
		}
		printf ("\n");
	}

}