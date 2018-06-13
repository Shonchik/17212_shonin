#pragma once

typedef struct tree {
	long long int count;
	unsigned char sim;
	int symbFlag;
	long long int kode;

	struct tree *leftTree;
	struct tree *rightTree;
	struct tree *nextlist;
} tree;


void PutS(long long int h, unsigned char s, tree **headlist);

void PutSum(tree **headlist);

void FreeTree(tree* l1);

void Decode(char* fileNameRead, char* fileNameWrite);