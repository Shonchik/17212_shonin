#define _CRT_SECURE_NO_WARNINGS
#include <math.h> 
#include <stdio.h>
#include <stdlib.h>
#include "HUffHeader.h"


void create_code_227(tree *headlist, unsigned long long int kodB[256][256], int kodDL[256],  int cur_sec[256], int cur_len)
{
	if (headlist->symbFlag)
	{
		kodDL[headlist->sim] = cur_len;
		for (int i=0;i<cur_len;i++)
		{
			kodB[headlist->sim][i] = cur_sec[i];
		}

	}
	else
	{
		cur_sec[cur_len] = 0;
		create_code_227(headlist->leftTree, kodB, kodDL, cur_sec, cur_len+1);
		cur_sec[cur_len] = 1;
		create_code_227(headlist->rightTree, kodB, kodDL, cur_sec, cur_len+1);
	}
}
void PutS(long long int h, unsigned char s, tree **headlist)
{
	tree *tmp = (tree*)malloc(sizeof(tree));
	tmp->count = h;
	tmp->sim = s;
	tmp->kode = 0;
	tmp->symbFlag = 1;
	tmp->leftTree = NULL;
	tmp->rightTree = NULL;
	tmp->nextlist = NULL;
	tree *pi = *headlist;
	tree *pj = NULL;

	while (pi != NULL) 
	{
		if (pi->count >= h)
			break;
		pj = pi;
		pi = pi->nextlist;
	} 

	if (pi == *headlist)						
	{
		*headlist = tmp;
		(*headlist)->nextlist = pi;
	}
	else
	{
		if (pi == NULL)					
		{
			pj->nextlist = tmp;
			tmp->nextlist = NULL;
		}
		else
		{
			pj->nextlist = tmp;
			tmp->nextlist = pi;				
		}
	}
}

void PutSum(tree **headlist)
{
	
	tree *min1 = *headlist;
	tree *min2 = (*headlist)->nextlist;

	tree *tmp = (tree*)malloc(sizeof(tree));
	tmp->count = min1->count + min2->count;
	tmp->sim = 0;
	tmp->kode = 0;
	tmp->symbFlag = 0;
	tmp->leftTree = min1;
	tmp->rightTree = min2;
	tmp->nextlist = NULL;

	(*headlist) = min2->nextlist;

	min1->nextlist = NULL;
	min2->nextlist = NULL;

	tree *pi = *headlist;
	tree *pj = NULL;

	while (pi != NULL)
	{
		if (pi->count >= tmp->count)
			break;
		pj = pi;
		pi = pi->nextlist;
	}

	if (pi == *headlist)				
	{
		*headlist = tmp;
		(*headlist)->nextlist = pi;
	}
	else
	{
		if (pi == NULL)	
		{
			pj->nextlist = tmp;
			tmp->nextlist = NULL;
		}
		else
		{
			pj->nextlist = tmp;
			tmp->nextlist = pi;	
		}
	}
}


void BitWrite(char* fileNameRead, char* fileNameWrite, unsigned long long int Textdlin, int lastbyteost, unsigned long long int kolvoSym[256], unsigned long long int kodB[256][256], int kodDL[256])
{
	
	FILE *inp = fopen(fileNameRead, "rb");
	FILE *output = fopen(fileNameWrite, "wb");

	fprintf(output, "%lld %d ", Textdlin, lastbyteost);
	for(int j=0; j<=255; j++)
		fprintf(output, "%lld ", kolvoSym[j]);

	unsigned char p;
	unsigned long long int x = 0;
	unsigned char y = 0;
	int kolvo = 0;
	
	while (fscanf(inp, "%c", &p) != EOF)
	{
		for (int i=0;i<kodDL[p];i++)
		{
			x <<= 1;
			x |= kodB[p][i];
			kolvo++;
			if (kolvo==8)
			{
				fwrite(&x, 1, 1, output);
				x = 0;
				kolvo = 0;
			}
		}
	}
	if (kolvo != 0)
	{
		x = x << (8 - kolvo);
		fwrite(&x, 1, 1, output);
	}

	fclose(output);
	fclose(inp);
}

void FreeTree (tree* l1)
{
	if (l1 == NULL)
		return;

	if (l1->leftTree)
	{
		FreeTree(l1->leftTree);
		free (l1->leftTree);
	}
	
	if (l1->rightTree)
	{
		FreeTree(l1->rightTree);
		free(l1->rightTree);
	}

}

int main()
{

	unsigned long long int kolvoSym[256] = { 0 };
	unsigned long long int kodB[256][256] = { 0 };
	int kodDL[256] = { 0 };

	int x = 0;
	char inputt[20];
	char outputt[20];

	tree* headlist1 = NULL;

	scanf("%d %s %s", &x, inputt, outputt);

	int archiveMode = -1;

	if (x == 0)
		archiveMode = 0;
	else 
		archiveMode = 1;


	if (archiveMode == 0)
	{
		Decode(inputt, outputt);
	}

	if (archiveMode == 1)
	{
		
		char* inp = inputt;
		char* outp = outputt;

		FILE *mfin = fopen(inp, "rb");

		if (mfin == NULL) {
			printf("Failed to open file '%s'\n", inp);
		}

		unsigned char p;
		while (fscanf(mfin, "%c", &p) != EOF){
			kolvoSym[p]++;
		}

		fclose(mfin);

		for (int i = 0; i <= 255; i++){
			if (kolvoSym[i] != 0){
				PutS(kolvoSym[i], i, &headlist1);
			}
		}

		while (headlist1->nextlist != NULL)
		{
			PutSum(&headlist1);
		}
		int cur_sec[256];
		if(headlist1->symbFlag){
			cur_sec[0] = 1;
			create_code_227(headlist1, kodB, kodDL, cur_sec, 1);
		} else {
			create_code_227(headlist1, kodB, kodDL, cur_sec, 0);
		}
		

		unsigned long long int Textdlin = 0;
		for (int i = 0; i <= 255; i++)
		{
			Textdlin = Textdlin + kodDL[i] * kolvoSym[i];
		}
		int lastbyteost = Textdlin % 8;
		Textdlin = Textdlin / 8;

		BitWrite(inp, outp, Textdlin, lastbyteost, kolvoSym, kodB, kodDL);

		FreeTree(headlist1);
		free(headlist1);


	}

	return 0;
}