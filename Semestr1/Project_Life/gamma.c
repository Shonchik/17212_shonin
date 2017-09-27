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

int count_neighbours(int *matr, int i, int j, int *height, int *width) {

	int count = 0;

	int up = (i - 1) * *height + j;
	int up_left = (i - 1) * *height + j - 1;
	int left = i * *height + j - 1;
	int left_down = (i + 1) * *height + j - 1;
	int down = (i + 1) * *height + j;
	int down_right = (i + 1) * *height + j + 1;
	int right = i * *height + j + 1;
	int right_up = (i - 1) * *height + j + 1;

	if ((j == *width - 1) && (i == 0))  {
		down_right = (i + 1) * *height; 
		right = i * *height;
		right_up = (*height - 1) * *height;
		up_left = (*height - 1) * *height + j - 1;
		up = (*height - 1) * *height + j;
	} else if ((j == *width - 1) && (i == *height - 1))  {
		down_right = 0; 
		right = i * *height;
		right_up = (i - 1) * *height;
		down = j;
		left_down = j - 1;
	} else if ((j == 0) && (i == *height - 1))  {
		down = j;
		left_down = *width - 1;
		down_right = j + 1; 
		left = i * *height + *width - 1;
		up_left = (i - 1) * *height + *width - 1;
	} else if ((j == 0) && (i == 0))  {
		left = i * *height + *width - 1;
		up_left = (*height - 1) * *height + *width;
		left_down = (i + 1) * *height + *width - 1;
		up = (*height - 1) * *height + j;
		right_up = (*height - 1) * *height + j + 1;
	} else if ( i == *height - 1) {
		down = j;
		left_down = j - 1;
		down_right = j + 1;
	} else if ( i == 0) {
		up = (*height - 1) * *height + j;
		up_left = (*height - 1) * *height + j - 1;
		right_up = (*height - 1) * *height + j + 1;
	} else if ( j == *width - 1) {
		right = i * *height ;
		right_up = (i - 1) * *height;
		down_right = (i + 1) * *height;
	} else if ( j == 0) {
		left_down = (i - 1) * *height + *width - 1;
		left = i * *height + *width - 1;
		up_left = (i + 1) * *height + *width - 1;
	}

	if (*(matr + up) == 1) {
		count++;
	}
	if (*(matr + up_left) == 1) {
		count++;
	}
	if (*(matr + left) == 1) {
		count++;
	}
	if (*(matr + left_down) == 1) {
		count++;
	}
	if (*(matr + down) == 1) {
		count++;
	}
	if (*(matr + down_right) == 1) {
		count++;
	}
	if (*(matr + right) == 1) {
		count++;
	}
	if (*(matr + right_up) == 1) {
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
	int rules = 0;
	int count_sosedi = 0;
	int height = 0;
	int proverka = 0;
	int count_live = 0;
	char name_infile[256];

	printf ("Write please name input file!\n");

	scanf ("%s", name_infile);

	matr = create_matr(&height, &width, &rule_burn, &rule_survive, name_infile);
	matr2 = create_matr(&height, &width, &rule_burn, &rule_survive, name_infile);

	if (NULL == matr) {
		printf ("Could not create malloc!");
		return 0;
	}

	while (proverka == 0) {

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				count_sosedi = count_neighbours(matr, i, j, &height, &width);
				if (*(matr2 + i * height + j) == 1) {
					rules = rule_survive;
					while (rules > 0) {
						int rule = rules % 10;
						rules /= 10;
						if (count_sosedi == rule) {
							*(matr2 + i * height + j) = 2;
						}
					}
				} else {
					rules = rule_burn;
					while (rules > 0) {
						int rule = rules % 10;
						rules /= 10;
						if (count_sosedi == rule) {
							*(matr2 + i * height + j) = 1;
						}
					}
				}
			}
		}

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (*(matr2 + i * height + j) == 1) {
					if (*(matr + i * height + j) == 1) {
						*(matr2 + i * height + j) = 0;
					}
				}
				if (*(matr2 + i * height + j) == 2) {
					*(matr2 + i * height + j) = 1;
				}
			}
		}

		for (int j = 0; j < width * height; j++) {
			*(matr + j) = *(matr2 + j);
		}

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				printf("%d ", *(matr + i * height + j));
				if (*(matr + i * height + j) == 1) {
					count_live++;
				}
			}
			printf ("\n");
		}

		if (count_live == 0) {
			printf ("Live is dead!\n");
			proverka = 1;
		} else {
			printf ("To continue type 0!\nTo end type 1!\n");
			scanf ("%d", &proverka);
			count_live = 0;
		}
	}

	printf ("Thanks\n");

}