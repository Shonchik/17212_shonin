#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int create_matr (int *matr) {

	FILE *myfile;
	myfile = fopen ("input.txt", "r");
	char sign;

	if (NULL == myfile) {
		matr = NULL;
	}

	for (int i = 24; i < 34; i++) {
		for (int j = 21; j < 35; j++) {
			fscanf (myfile, "%c", &sign);
			if ('\n' == sign) {
				fscanf (myfile, "%c", &sign);
			}
			*(matr + i * 55 + j) = sign - '0';
		}
	}

	fclose (myfile);

	return 0;

}

char *count_rule(int *matr, int i, int j, char *rule) {

	rule[0] = *(matr + i * 55 + j) + '0';
	rule[1] = *(matr + (i - 1) * 55 + j) + '0';
	rule[2] = *(matr + i * 55 + j + 1) + '0';
	rule[3] = *(matr + (i + 1) * 55 + j) + '0';
	rule[4] = *(matr + i * 55 + j - 1) + '0';

	return rule;

}

void swap1 (char *a, char *b) {
	char c = *a;
	*a = *b;
	*b = c;
}

char check_rules (char *rul) {

	FILE *myfile2;
	myfile2 = fopen ("rules.txt", "r");
	int pr = 0;
	char rule2[5];
	char new_sign;

	char rule[5];

	for (int i = 0; i < 5; i++) {
		rule[i] = *(rul +i);
	}

	for (int i = 0; i < 876; i++) {
		fscanf (myfile2, "%5s%c\n", rule2, &new_sign);	
		for (int j = 0; j < 5; j++) {
			if (rule[j] == rule2[j]) {
				pr++;
			}
		}
		if (5 == pr){
			break;
		}
		pr = 0;
		swap1 (&rule2[3], &rule2[4]);
		swap1 (&rule2[3], &rule2[2]);
		swap1 (&rule2[2], &rule2[1]);
		for (int j = 0; j < 5; j++) {
			if (rule[j] == rule2[j]) {
				pr++;
			}
		}
		if (5 == pr){
			break;
		}
		pr = 0;
		swap1 (&rule2[3], &rule2[4]);
		swap1 (&rule2[3], &rule2[2]);
		swap1 (&rule2[2], &rule2[1]);
		for (int j = 0; j < 5; j++) {
			if (rule[j] == rule2[j]) {
				pr++;
			}
		}
		if (5 == pr){
			break;
		}
		pr = 0;
		swap1 (&rule2[3], &rule2[4]);
		swap1 (&rule2[3], &rule2[2]);
		swap1 (&rule2[2], &rule2[1]);
		for (int j = 0; j < 5; j++) {
			if (rule[j] == rule2[j]) {
				pr++;
			}
		}
		if (5 == pr){
			break;
		}
		pr = 0;
		
	}

	//printf ("%s%c %s\n", rule2, new_sign, rule);		

	fclose (myfile2);

		return new_sign;

}

int conversion (int *matr, int *matr2) {

	char *rule = malloc (5*sizeof(char));
	char new_sign;

	for (int i = 1; i < 34; i++) {
		for (int j = 1; j < 54; j++) {
			rule = count_rule (matr, i, j, rule);
			new_sign = check_rules (rule);
			*(matr2 + i * 55 + j) = new_sign - '0';
			//printf ("%c ", new_sign);
		}
		//printf ("\n");
	}

	free (rule);

	return 0;

}

int main () {

	int *matr = calloc (1925, sizeof(int));
	int *matr2 = calloc (1925, sizeof(int));
	char d;
	int r = 0;
	if ((NULL == matr) || (NULL == matr2)) {
		printf ("Failed to create calloc");
	}

	create_matr(matr);
	create_matr(matr2);
	if (NULL == matr) {
		printf ("Failed to open file");
	}

	while (r == 0) {
		conversion(matr, matr2);

		for (int i = 0; i < 1925; i++) {
			*(matr + i) = *(matr2 + i);
		}
		
		system ("cls");
		for (int i = 0; i < 35; i++) {
			for (int j = 0; j < 55; j++) {
				if (*(matr + i * 55 + j) == 0) {
					printf ("  ");
				} else {
					printf ("%d ", *(matr + i * 55 + j));
				}
			}
			printf ("\n");
		}
		//scanf ("%c", &d);
	}

	free (matr);
	free (matr2);

} 