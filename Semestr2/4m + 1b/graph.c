#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "graphlib.h"

int main(){
	char input[90] = "db2.txt";
	//printf("Write name file: ");
	//scanf("%s \n", input);
	int x = 0;
	scanf("%d", &x);
	FILE * f = fopen(input, "r");
	struct graph_base * gr = read_graph(f);
	fclose(f);
	if(gr->ht->buf_size == 0){
		printf("error read\n");
		return -1;
	}
	printGraphToWidth(gr);
	printf("\n");
	printGraphWayFrom(gr, x);
	free_graph(gr);
	return 0;
}