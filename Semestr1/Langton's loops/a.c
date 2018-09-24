#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

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

int *read_rle(int *width, int *height){
    FILE *fileRLE;
    fileRLE = fopen("data.rle", "r");
    if(NULL == fileRLE){
        return 0;
    }

    int x = 0;
    int y = 0;
    int i = 0;
    int j = 0;
    int count = 0;
    int x_flag = 0;
    char c = ' ';
    int *map;
    char pointer;
    do{
        if(-1 == fscanf(fileRLE,"%c",&pointer)){
            break;
        }
        if(pointer == 'x' && x_flag == 0){
            x_flag = 1;
            fscanf(fileRLE," = %d, y = %d", width, height);
            while (c != '\n'){
                fscanf(fileRLE, "%c", &c);
            }
            map = (int *)calloc(*width * *height, sizeof(int));
            fscanf(fileRLE, "%c", &pointer);
        }
        if(pointer == '\n' || pointer == '!'){
            continue;
        }
        if(pointer == '#'){
            while(pointer != '\n'){
                fscanf(fileRLE, "%c", &pointer);
            }
        }
        if(isdigit(pointer)){
            count *= 10;
            count += pointer - '0';
        }
        else if(pointer == '.'){
            if(0 == count){
                x++;
                count = 0;
            }
            else{
                x += count;
                count = 0;
            }
        }
        else if(pointer == '$'){
            y++;
            x = 0;
        }
        else if(0 == count && (pointer >= 'A' && pointer <= 'G')){
            if(x+(y * *width) < *width * *height){
                map[x+(y * *width)] = pointer - 'A' + 1;
                x++;
            }
            else{
                return (int*)1;
            }
        }
        else if(0 != count && (pointer >= 'A' && pointer <= 'G')){
            for (j = 0; j < count; ++j){
                if(x+(y * *width) < *width * *height){
                    map[x+(y * *width)] = pointer-'A'+1;
                    x++;
                }
                else{
                    return (int*)1;
                }
            }
            count = 0;
        }
    } while(pointer != '!');
    fclose(fileRLE);
    return map;
}

int check(int y, int x, int width, int height){
    if(x < 0){
        x = width - 1;
    }
    if(x > width - 1){
        x = 0;
    }
    if(y < 0){
        y = height - 1;
    }
    if(y > height - 1){
        y = 0;
    }
    return x + (y * width);
}

char *count_rule(int *matr, int i, int j, char *rule , int width, int height) {
	rule[0] = *(matr + check(i,j,width,height)) + '0';
	rule[1] = *(matr + check(i-1,j,width,height)) + '0';
	rule[2] = *(matr + check(i,j+1,width,height)) + '0';
	rule[3] = *(matr + check(i+1,j,width,height)) + '0';
	rule[4] = *(matr + check(i,j-1,width,height)) + '0';

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

	for (int i = 0; i < 219; i++) {
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

int conversion (int *matr, int *matr2, int height, int width) {

	char *rule = malloc (5*sizeof(char));
	char new_sign;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			rule = count_rule (matr, i, j, rule, width, height);
			new_sign = check_rules (rule);
			*(matr2 + i * width + j) = new_sign - '0';
			//printf ("%c ", new_sign);
		}
		//printf ("\n");
	}

	free (rule);	

	return 0;

}

int main () {
	int width = 0;
    int height = 0;
	int *matr = read_rle(&width, &height);
	int *matr2 = read_rle(&width, &height);
	char d;
	int r = 0;
	if ((NULL == matr) || (NULL == matr2)) {
		printf ("Failed to create calloc");
	}

	if (NULL == matr) {
		printf ("Failed to open file");
	}

	while (r == 0) {
		conversion(matr, matr2, height, width);

		for (int i = 0; i < height*width; i++) {
			*(matr + i) = *(matr2 + i);
		}
		
		system ("cls");
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (*(matr + i * width + j) == 0) {
					printf (" ");
				} else {
					printf ("%d", *(matr + i * width + j));
				}
			}
			printf ("\n");
		}
		//scanf ("%c", &d);
	}

	free (matr);
	free (matr2);

} 