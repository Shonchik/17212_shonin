#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include <string.h>

#define NAMESIZE 50
#define BUFSIZE 3000000

struct database{
	struct data ** Htable;
	long long bufsize;
	int size;
};

struct data{
	char name[NAMESIZE];
	int height;
	int weight;
};

unsigned int h1(char * str){
	unsigned int hashAddress = 17;
	for (int counter = 0; str[counter] != '\0'; counter++){
		hashAddress = str[counter] + (hashAddress << 6) + (hashAddress << 16) - hashAddress;
	}
	return hashAddress;
}

unsigned int h2(char * str){
	unsigned int hashAddress = 5381;
	for (int counter = 0; str[counter] != '\0'; counter++){
		hashAddress = ((hashAddress << 5) + hashAddress) + str[counter];
	}
	return hashAddress;
}

void insertresize(struct database * db, struct data * person){
	int k = 0;
	int key = 0;

	while(1){
		key = (h2(person -> name) + k * h1(person -> name)) % db -> bufsize;
		if(db -> Htable[key] == 0){
			db -> Htable[key] = person;
			db -> size++;
			break;
		} else {
			k++;
		}
	}
}

void resize(struct database ** db){
	struct database * newdb = (struct database *)calloc(1, sizeof(struct database));
	long long newsize = (*db) -> bufsize * 2;

	newdb -> Htable = (struct data **)calloc(newsize, sizeof(struct data *));
	newdb -> bufsize = newsize;

	for (long long i = 0; i < (*db) -> bufsize; i++){
		if((*db) -> Htable[i] != 0){
			insertresize(newdb, (*db) -> Htable[i]);
		}
	}

	(*db) -> Htable = newdb -> Htable;
	(*db) -> bufsize = newdb -> bufsize;

	free(newdb);
}

void inperson(struct database * db, struct data person){
	int k = 0;
	int key = 0;

	if (db -> size >= db -> bufsize / 2){
		resize(&db);
	}

	while(1){
		key = (h2(person.name) + k * h1(person.name)) % db -> bufsize;
		if(db -> Htable[key] == 0){
			db -> Htable[key] = (struct data *)malloc(sizeof(struct data));
			db -> Htable[key] -> height = person.height;
			db -> Htable[key] -> weight = person.weight;
			memcpy(db -> Htable[key] -> name, person.name, NAMESIZE);
			db -> size++;
			break;
		} else {
			k++;
		}
	}
}

int search(struct database * db, char name[NAMESIZE]){
	int k = 0;
	int key = 0;

	while(1){
		key = (h2(name) + k * h1(name)) % db -> bufsize;
		if(db -> Htable[key] != 0 && 0 == strcmp(name, db -> Htable[key] -> name)){
			return key;
		} else{
			k++;
			if(k == db -> bufsize){
				break;
			}
		}
	}

	return 0;
}

struct database * read(FILE * f){
	struct database * db = (struct database *)calloc(1, sizeof(struct database));

	if(NULL == f){
		db -> bufsize = 0;
		return db;
	}

	struct data person;

	db -> bufsize = BUFSIZE;
	db -> size = 0;
	db -> Htable = (struct data **)calloc(db -> bufsize, sizeof(struct data *));

	while(1){
		memset(person.name, 0, NAMESIZE);
		int er = fscanf(f, "%s %d %d", person.name, &person.height, &person.weight);
		if(er != 3){
			break;
		}
		inperson(db, person);
	}

	return db;
}

int main () {
	char input[90];
	printf("Write name file: ");
	scanf("%s", input);

	FILE * f = fopen(input, "r");

	struct database * db = read(f);
	fclose(f);

	if(db -> bufsize == 0){
		printf("505 Not Found\n");
		return -1;
	}

	char name[NAMESIZE];

	while(1){
		memset(name, 0, NAMESIZE);
		scanf("%s", name);
		int key = search(db, name);
		if(key){
			printf("height: %d weight: %d\n", db->Htable[key] -> height, db -> Htable[key] -> weight);
		} else{
			printf("Not found\n");
		}
	}

	return 0;

}