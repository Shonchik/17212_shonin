#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Htable.h"
#include "lists.h"

struct LRU{
	struct Hash_table * ht;
	struct Ht_data * head;
	struct Ht_data * tail;
	int size;
	int max_size;
};

struct LRU * cache_init(int size){
	struct LRU * p = (struct LRU *)calloc(1,sizeof(struct LRU));
	p->ht = Ht_init();
	p->max_size = size;
	return p;
}

int Get(struct LRU * cache, int key){
	struct Ht_data * d = Ht_get(cache->ht, key);
	if(d == 0){
		return -1;
	}
	if(d == cache->tail){
		if(d->pref != 0){
			cache->tail = d->pref;	
		} else{
			cache->tail = 0;
		}	
	}
	if(d->pref != 0){
		d->pref->next = d->next;	
	}
	if(d->next != 0){
		d->next->pref = d->pref;
	}
	d->next = cache->head;
	d->pref = 0;
	cache->head->pref = d;
	cache->head = d;
	return d->data;
}

void Put(struct LRU * cache, int key, int num){
	struct Ht_data * data = (struct Ht_data *)calloc(1, sizeof(struct Ht_data));
	_itoa(key, data->name, 10);
	data->data = num;
	Ht_set(cache->ht, data);
	if(cache->head != 0){
		cache->head->pref = data;
		data->next = cache->head;
	} else{
		cache->tail = data;
	}
	cache->head = data;
	if(cache->size == cache->max_size){
		cache->tail->pref->next = 0;
		struct Ht_data * del = cache->tail;
		cache->tail = cache->tail->pref;
		free(del);
		
	} else{
		cache->size++;
	}
}

void cache_remove_el(struct LRU * cache, int key){
	struct Ht_data * el = Ht_get(cache->ht, key);
	if(el == 0){
		return;
	}
	cache->size--;
	if(el->next == 0){
		cache->tail = el->pref;
	} else{
		el->next->pref = el->pref;
	}
	if(el->pref == 0){
		cache->head = el->next;
	} else{
		el->pref->next = el->next;
	}
	free(el);
}

void cache_remove(struct LRU * cache){
	Ht_free(cache->ht);
	free(cache);
}

void print(struct LRU * lru){
	struct Ht_data * p = lru->head;
	while(p != 0){
		printf("Name %d next element %d  pref element %d\n", p->data == 0 ? 0 : p->data, p->next == 0 ? 0 : p->next->data, p->pref == 0 ? 0 : p->pref->data);
		p = p->next;
	}
	printf("\n");
}

int main(){
	struct LRU * lru = cache_init(3);
	print(lru);
	Put(lru,1,5);
	print(lru);
	Put(lru,2,6);
	print(lru);
	Get(lru,1);
	print(lru);
	Put(lru,3,7);
	print(lru);
	Put(lru,4,8);
	print(lru);
	Put(lru,5,9);
	print(lru);
	Get(lru, 3);
	print(lru);
	Get(lru, 4);
	print(lru);
	cache_remove(lru);
	return 0;
}