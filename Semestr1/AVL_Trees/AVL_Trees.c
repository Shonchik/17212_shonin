#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAMESIZE 60

struct student{
	int age;
	int height;
};

struct tree{
	struct student person;
	char key[NAMESIZE];
	int height;
	struct tree * left;
	struct tree * right;
};

void fixheight(struct tree * tr){
	int hl = tr -> left ? tr -> left -> height : 0;
	int hr = tr -> right ? tr -> right -> height : 0;

	tr -> height = ((hl > hr) ? hl : hr) + 1;
}

int bfactor(struct tree * tr){
	return (tr -> right ? tr -> right->height : 0) - (tr -> left ? tr -> left -> height : 0);
}

struct tree * rotateright(struct tree * tr){
	struct tree * q = tr -> left;

	tr -> left = q -> right;
	q -> right = tr;

	fixheight(tr);
	fixheight(q);

	return q;
}

struct tree * rotateleft(struct tree * tr){
	struct tree * q = tr -> right;

	tr -> right = q -> left;
	q -> left = tr;

	fixheight(tr);
	fixheight(q);

	return q;
}

struct tree * balance(struct tree * tr){
	fixheight(tr);

	if(2 == bfactor(tr)){
		if(bfactor(tr -> right) < 0){
			tr -> right = rotateright(tr -> right);
		}
		return rotateleft(tr);
	}
	if(-2 == bfactor(tr)){
		if(bfactor(tr -> left) > 0){
			tr -> left = rotateleft(tr -> left);
		}
		return rotateright(tr);
	}

	return tr;
}

struct tree * insert(struct tree * tr, const char * k, struct student st){
	if(!tr){
		struct tree *r = (struct tree *)malloc(1 * sizeof(struct tree));
		r -> left = 0;
		r -> right = 0;
		memcpy(r -> key, k, NAMESIZE);
		r -> height = 1;
		r -> person.age = st.age;
		r -> person.height = st.height;
		return r;
	}
	if(strcmp(tr -> key, k) > 0){
		tr -> left = insert(tr -> left, k, st);
	} else{
		tr -> right = insert(tr -> right, k, st);
	}

	return balance(tr);
}

struct tree * find(struct tree * tr, const char * key){
	if(tr == 0){
		return 0;
	}

	int t = strcmp(tr -> key, key);

	if(t == 0){
		return tr;
	} else if(t > 0){
		return find(tr -> left, key);
	} else{
		return find(tr -> right, key);
	}

	return 0;
}

struct tree * read(FILE * f, struct tree * tr){
	if(NULL == f){
		return 0;
	}

	int data1 = 0;
	int data2 = 0;
	char key[NAMESIZE];
	struct student st;

	while(1){
		memset(key, 0, NAMESIZE);
		if(-1 == fscanf(f,"%s %d %d", key, &st.age, &st.height)){
			break;
		}
		if(!find(tr, key)){
			tr = insert(tr, key, st);
		}
	}

	return tr;
}

int main(){
	struct tree * head = 0;

	FILE * f = fopen("db.txt", "r");
	head = read(f, head);
	fclose(f);

	if(head == 0){
		printf("error read\n");
		return -1;
	}

	char name[NAMESIZE];

	while(1){
		memset(name, 0, NAMESIZE);
		scanf("%s", name);
		struct tree * result = find(head, name);
		if(result){
			printf("\nname: %s\nage: %d\nheight: %d\n", result -> key, result -> person.age, result -> person.height);
		} else{
			printf("Not found\n");
		}
	}

	return 0;
}