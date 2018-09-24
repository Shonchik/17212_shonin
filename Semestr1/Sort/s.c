#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_SORT 6
#define SIZE_TYPE sizeof(double)

struct file_list{
	char name[12];
	struct file_list * next;
};

int cmp(const void * aa, const void * bb){
	double * a = (double *)aa;
	double * b = (double *)bb;
	if(*a > *b)
		return 1;
	else if(*a < *b)
		return -1;
	else
		return 0;
}

void sort(FILE * f, int (*cmp)(const void * aa, const void * bb)){
	struct file_list * head = (struct file_list *)malloc(sizeof(struct file_list));
	head -> next = NULL;
	void * arr = malloc(SIZE_SORT * SIZE_TYPE);
	int err_r = 1;
	int last = 0;
	for (int i = 0; i < SIZE_SORT; i++){
		err_r = fscanf(f, "%lf", ((double *)arr + i));
		last = i;
		if(-1 == err_r){
			break;
		}
	}

	//last = i;

	qsort(arr, last, SIZE_TYPE, cmp);
	for (int i = 0; i < last; i++){
		printf("%lf\n", *((double *)arr + i));
	}

}

int main()
{
	FILE * f = fopen("s.txt", "r");
	if(NULL == f){
		printf("Error read\n");
		return -1;
	}

	sort(f, cmp);
	
	return 0;
}