#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "lists.h"
#include "Htable.h"

struct graph_base{
	struct Hash_table * ht;
	struct intList * list;
};

struct graph_base * read_graph(FILE * f){
	struct graph_base * gb = (struct graph_base *)calloc(1, sizeof(struct graph_base));
	struct Ht_data * d;
	if(NULL == f){
		gb->ht->buf_size = 0;
		return gb;
	}

	gb->ht = Ht_init();
	
	while(1){
		int node1, node2;
		int er = fscanf(f, "%d %d", &node1, &node2);
		if(er != 2){
			break;
		}

		IntList_push(&gb->list, node1);
		IntList_push(&gb->list, node2);

		d = Ht_get(gb->ht, node1);
		if(d == 0){
			d = (struct Ht_data *)calloc(1, sizeof(struct Ht_data));
			_itoa(node1, d->name, 10);
			d->data = node1;
			IntList_push(&(d->list), node2);
			Ht_set(gb->ht, d);
		} else{
			IntList_push(&(d->list), node2);
			Ht_set(gb->ht, d);
		}

		d = Ht_get(gb->ht, node2);
		if(d == 0){
			d = (struct Ht_data *)calloc(1, sizeof(struct Ht_data));
			_itoa(node2, d->name, 10);
			d->data = node2;
			IntList_push(&(d->list), node1);
			Ht_set(gb->ht, d);
		} else{
			IntList_push(&(d->list), node1);
			Ht_set(gb->ht, d);
		}

	}
	return gb;
}

void free_graph(struct graph_base * gb){
	Ht_free(gb->ht);	
	IntList_free(gb->list);
	free(gb);
}

void printWidth (struct graph_base * gb, int num) {
	struct intList *queue = 0;
	IntList_push(&queue, num);
	Ht_get(gb->ht, queue->data)->qu = 2;
	while(queue != 0){
		int id = IntList_pop_first(&queue);
		printf("%d ", id);
		struct Ht_data * h = Ht_get(gb->ht, id);
		struct intList * p = h->list;
		while(p != 0){
			struct Ht_data * h2 = Ht_get(gb->ht, p->data);
			if(h2->qu != 2){
				//printf(" -%d- ", p->data);
				IntList_push(&queue, p->data);
				h2->qu = 2;
			}
			p = p->next;
		}
	}

}

int find_neighboor(struct graph_base * gb, struct intList * way){
	struct intList * p = way;
	struct Ht_data * dt;
	while(p != 0){
		dt = Ht_get(gb->ht, p->data);
		if(dt != 0 && dt->list != 0){
			return p->data;
		}
		p = p->next;
	}
	return -1;
}

void printGraphWayFrom(struct graph_base * gb, int num){
	struct intList * ring = 0;
	IntList_push(&ring, num);
	struct intList * p = ring;
	struct Ht_data * dt;
	int neighboor = -1;
	int t = 0;
	int t2 = 0;
	while(1){
		t = find_neighboor(gb, p);
		neighboor = -1;
		t2 = t;
		if(t == -1){
			break;
		}
		p = IntList_get_ondata(p, t);
		dt = Ht_get(gb->ht, t);
		int c = 0;
		while(neighboor != t){
			neighboor = IntList_pop_first(&(dt->list));
			IntList_pop_ondata(&(Ht_get(gb->ht, neighboor)->list), t2);
			t2 = neighboor;
			IntList_push_from(&p, neighboor, c);
			c++;
			dt = Ht_get(gb->ht, neighboor);
		}
	} 
	IntList_print(ring);
}

int main(){

	char name[50] = "db2.txt";
	FILE * f = fopen(name, "r");
	struct graph_base * gr = read_graph(f);
	fclose(f);

	if(gr->ht->buf_size == 0){
		printf("error read\n");
		return -1;
	}

	int x = 0;
	scanf("%d", &x);

	printWidth(gr, x);
	printf("\n");
	//IntList_print(gr->list);
	printGraphWayFrom(gr, x);
	free_graph(gr);
	return 0;	

}