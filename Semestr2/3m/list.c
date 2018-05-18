#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>

#define NUM 5
#define N 10

struct list{
	int data;
	struct list * next;
};

void List_push (struct list ** l, int num){
	struct list ** p = l;
	if(*p == 0){
		*p = (struct list *)calloc(1, sizeof(struct list));
		(*p)->data = num;
		(*p)->next = 0;
	} else {
		while((*p)->next != 0){
			p = &(*p)->next;
		}
		(*p)->next = (struct list *)calloc(1, sizeof(struct list));
		(*p)->next->data = num;
		(*p)->next->next = 0;
	}
}

void List_print (struct list * l){
	while(l != 0){
		printf("%d-", l->data);
		l=l->next;
	}
	printf("\n");
}

struct list * List_merge (struct list * l1, struct list * l2){
	struct list * r = 0;
	while(l1 != 0){
		List_push (&r, l1 -> data);
		l1 = l1->next;
	}
	while(l2 != 0){
		List_push (&r, l2 -> data);
		l2 = l2 -> next;
	}
	return r;
}

int min2 (int a, int b){
	if(a <= b){
		return a;
	} else{
		return b;
	}
}

int main (){
	int *** mas = (int ***)malloc(N * sizeof(int **));
	for (int i = 0; i < N; i++){
		mas[i] = (int **)malloc(N * sizeof(int *));
		for (int j = 0; j < N; j++){
			mas[i][j] = (int *)malloc(N * sizeof(int));
			for (int k = 0; k < N; k++){
				mas[i][j][k] = 1000;
			}
		}
	}
	
	struct list *** ways = (struct list ***)malloc(N * sizeof(struct list **));
	for (int i = 0; i < N; i++){
		ways[i] = (struct list **)calloc(N, sizeof(struct list *));
		for (int j = 0; j < N; j++){
			List_push(&ways[i][j], i);
		}
	}

	char input[90] = "db2.txt";
	//printf("Write name file: ");
	//scanf("%s \n", input);
	int as = 0;
	int sa = 0;
	scanf("%d %d \n", &as, &sa);

	FILE * f = fopen(input, "r");
	if(f == 0){
		printf("Error File\n");
		return -1;
	}

	int d1 = 0, d2 = 0, d3 = 0;
	while(fscanf(f, "%d %d %d", &d1, &d2, &d3) == 3){
		mas[d1][d2][0] = d3;
	}
	fclose(f);

	for (int k = 1; k <= NUM; k++){
		for (int i = 0; i < N; i++){
			for (int j = 0; j < N; j++){
				mas[i][j][k] = min2(mas[i][j][k-1], mas[i][k][k-1] + mas[k][j][k-1]);
				if(mas[i][j][k] != mas[i][j][k-1]){
					ways[i][j] = List_merge(ways[i][k], ways[k][j]);
				}
			}
		}
	}

	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; ++j){
			List_push(&ways[i][j], j);
		}
	}

	printf("Way : "); List_print(ways[as][sa]);
	printf("Ansver : %d\n", mas[as][sa][5]);

	return 0;
}