#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>

#define NUM 9
#define N 10

struct list{
	int x;
	struct list * next;
};

void List_push (struct list ** l, int num){
	struct list ** p = l;
	if(*p == NULL){
		*p = (struct list *)calloc(1, sizeof(struct list));
		(*p)->x = num;
		(*p)->next = NULL;
	} else {
		while((*p)->next != NULL){
			p = &(*p)->next;
		}
		(*p)->next = (struct list *)calloc(1, sizeof(struct list));
		p = &(*p)->next;
		(*p)->x = num;
		(*p)->next = NULL;
	}
}

void List_print (struct list * l){
	while(l != NULL){
		printf("%d ", l->x);
		l=l->next;
	}
	printf("\n");
}

struct list * List_plus (struct list * l1, struct list * l2){
	struct list * r = 0;
	while(l1 != NULL){
		List_push (&r, l1 -> x);
		l1 = l1->next;
	}
	while(l2 != NULL){
		List_push (&r, l2 -> x);
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
			//printf("-");
			//List_print(ways[i][j]);
			//	printf("-");
		}
		//printf("\n");
	}

	char input[90] = "db2.txt";
	int as = 0;
	int sa = 0;
	scanf("%d %d", &as, &sa);

	FILE * f = fopen(input, "r");
	if(f == 0){
		printf("Error File\n");
		return -1;
	}

	int d1 = 0;
	int d2 = 0;
	int d3 = 0;
	while(fscanf(f, "%d %d %d", &d1, &d2, &d3) == 3){
		mas[d1][d2][0] = d3;
	}
	fclose(f);

	for (int k = 1; k <= NUM; k++){
		for (int i = 0; i < N; i++){
			for (int j = 0; j < N; j++){
				mas[i][j][k] = min2(mas[i][j][k-1], mas[i][k][k-1] + mas[k][j][k-1]);
				printf("%4d ", mas[i][j][k]);
			}
			printf("\n");
		}
		printf("\n");
	}

	for (int k = 1; k <= NUM; k++){
		for (int i = 0; i < N; i++){
			for (int j = 0; j < N; j++){
				if(mas[i][j][k] != mas[i][j][k-1]){
					ways[i][j] = List_plus(ways[i][k], ways[k][j]);
				}
				//printf("-");
				//List_print(ways[i][j]);
				//printf("-");
			}
			//printf("\n");
		}
		//printf("\n");
	}

	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; ++j){
			List_push(&ways[i][j], j);
			//printf("-");
			//List_print(ways[i][j]);
			//printf("-");
		}
		//printf("\n");
	}
	printf("Way : "); 
	List_print(ways[as][sa]);
	printf("Answer : %d\n", mas[as][sa][NUM]);

	return 0;
}