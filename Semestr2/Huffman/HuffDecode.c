#define _CRT_SECURE_NO_WARNINGS
#include <math.h> 
#include <stdio.h>
#include <stdlib.h>
#include "HUffHeader.h"

void Decode(char* fileNameRead, char* fileNameWrite)
{
	FILE *output = NULL;
	FILE *input = NULL; 
	long long int kolvo2[256] = { 0 };

	input = fopen(fileNameRead, "rb");
	output = fopen(fileNameWrite, "wb");

	if (input == NULL) {
		printf("Failed to open file '%s'", fileNameRead);
		exit(0);
	}
	if (output == NULL) {
		printf("Failed to open file '%s'", fileNameWrite);
		exit(0);
	}
	unsigned long long int k = 0;
	unsigned long long int Textdlin;
	int lastbyteost;

	fscanf(input, "%lld %d ", &Textdlin, &lastbyteost);
	for (int j = 0; j <= 255; j++)
		fscanf(input, "%lld ", &kolvo2[j]);

	tree *headlist2 = NULL;

	for (int i = 0; i <= 255; i++)
		if (kolvo2[i] != 0)
			PutS(kolvo2[i], i, &headlist2);

	while (headlist2->nextlist != NULL)
		PutSum(&headlist2);


	tree *tek = headlist2;
	unsigned char symb;

	unsigned char prevsymb = 0;
	int posled = 0;

	unsigned char mask = 128;
	while (fscanf(input, "%c", &symb) != EOF)
	{
		k++;
		while (mask > 0)
		{
			if (k == Textdlin + 1)
			{
				if (mask == (128 >> (lastbyteost)))
					break;
			}
			if ((mask & symb) != 0)
				tek = tek->rightTree;
			else
				tek = tek->leftTree;

			mask = mask >> 1;

			if (tek->symbFlag != 0)
			{
				fputc(tek->sim, output);
				tek = headlist2;
			}
		}
		mask = 128;
	}

	FreeTree(headlist2);
	free(headlist2);

	fclose(output);
	fclose(input);
}
