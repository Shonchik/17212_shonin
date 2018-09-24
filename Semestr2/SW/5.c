#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct myType{
	float x;
	int k_h;
	int k_w;
}node;

const int matrix[4][4] = {  {3,  -3, -3, -3}, 
							{-3,  3, -3, -3}, 
							{-3, -3,  3, -3}, 
							{-3, -3, -3,  3}};

const float WFirst = 2;
const float Wk = 0.5;

int getCost(char ch1, char ch2);

float getGap(node **Table, int Findex, int Sindex, char key){
	if('h' == key){
		if(0 == Table[Findex-1][Sindex].k_h){
			return Table[Findex-1][Sindex].x - WFirst;
		}

		return Table[Findex-1][Sindex].x - Wk;
	}
	if('w' == key){
		if(0 == Table[Findex][Sindex-1].k_w){
			return Table[Findex][Sindex-1].x - WFirst;
		}

		return Table[Findex][Sindex-1].x - Wk;
	}
}

float calc(node **Table, int Findex, int Sindex, char *str1, char *str2){
	float max = 0.0;

	float cost = getCost(str2[Findex-1], str1[Sindex-1]);

	if(max < Table[Findex-1][Sindex-1].x + cost){
		max = Table[Findex-1][Sindex-1].x + cost;
	}
	float gap = getGap(Table, Findex, Sindex, 'h');

	if(max < gap){
		max = gap;
		Table[Findex][Sindex].k_h = Table[Findex-1][Sindex].k_h + 1;
	}
	gap = getGap(Table, Findex, Sindex, 'w');

	if(max < gap){
		max = gap;
		Table[Findex][Sindex].k_h = 0;
		Table[Findex][Sindex].k_w = Table[Findex][Sindex-1].k_w + 1;
	}
	return max;
}

void function(FILE *file){
	
	char *str1 = (char *)calloc(1, sizeof(char));
	char *str2 = (char *)calloc(1, sizeof(char));

	int len1 = 0;
	int len2 = 0;

	char ch = fgetc(file);
	while('\n' != ch){
		*(str1 + len1) = ch;
		++len1;
		str1 = realloc(str1, len1 + 1);
		ch = fgetc(file);
	}

	ch = fgetc(file);
	while('\n' != ch && EOF != ch){
		*(str2 + len2) = ch;
		++len2;
		str2 = realloc(str2, len2 + 1);
		ch = fgetc(file);
	}


	node **Table = (node **)calloc(len2+1, sizeof(node *));
	for(int i = 0; i < len2+1; ++i){
		*(Table+i) = (node *)calloc(len1+1, sizeof(node));
	}

	float MaxValue = 0.0;
	int MaxFindex = -1;
	int MaxSindex = -1;
	for(int i = 1; i < len2+1; ++i){
		for(int j = 1; j < len1+1; ++j){
			Table[i][j].x = calc(Table, i, j, str1, str2);
			if(MaxValue < Table[i][j].x){
				MaxValue = Table[i][j].x;
				MaxFindex = i;
				MaxSindex = j;
			}
		}
	}

	float Score = MaxValue;

	printf("     ");
	for(int i = 0; i < len1; ++i){
		printf(" %c ", str1[i]);
	}
	printf("\n");
	for(int i = 0; i < len2+1; ++i){
		if(0 != i){
			printf("%c ", str2[i-1]);
		}else{
			printf("  ");
		}
		for(int j = 0; j < len1+1; ++j){
			printf("%2.0f ", Table[i][j].x);
		}
		printf("\n");
	}

	char *sym1 = (char *)calloc(len1+1, sizeof(char));
	char *sym2 = (char *)calloc(len2+1, sizeof(char));

	int i = 0 ;
	int j = 0;
	float max = Table[MaxFindex][MaxSindex].x;
	while(MaxFindex != 0 && MaxSindex != 0){
		int x = MaxSindex;
		int y = MaxFindex;

		if(max == Table[MaxFindex-1][MaxSindex-1].x + getCost(str2[MaxFindex-1], str1[MaxSindex-1])){
			sym1[i] = str1[x-1];
			sym2[j] = str2[y-1];
			max = Table[MaxFindex-1][MaxSindex-1].x;
			MaxFindex = y-1;
			MaxSindex = x-1;
		}
		else if(max == getGap(Table, MaxFindex, MaxSindex, 'h')){
			sym1[i] = '-';
			sym2[j] = str2[y-1];
			MaxFindex = y-1;
			MaxSindex = x;
			max = Table[MaxFindex][MaxSindex].x;
		}
		else if(max == getGap(Table, MaxFindex, MaxSindex, 'w')){
			sym1[i] = str1[x-1];
			sym2[j] = '-';
			MaxFindex = y;
			MaxSindex = x-1;
			max = Table[MaxFindex][MaxSindex].x;
		}
		else{
			printf("exit\n");
			break;
			
		}

		++i;
		++j;
	}

	int cnt = 0;
	for(; 0 != sym1[cnt]; ++cnt){
		;
	}
	char *res1 = (char *)calloc(cnt, sizeof(char));
	char *res2 = (char *)calloc(cnt, sizeof(char));
	char *res_med = (char *)calloc(cnt, sizeof(char));
	int count_gaps = 0;
	int count_sticks = 0;
	int lenght = cnt;
	for(int i = 0; i < cnt; ++i){
		res1[i] = sym1[cnt-i-1];
		res2[i] = sym2[cnt-i-1];
		if(res1[i] == res2[i] && '-' != res1[i]){
			res_med[i] = '|';
			++count_sticks;
		}else if('-' == res1[i] || '-' == res2[i]){
			res_med[i] = ' ';
			++count_gaps;
		}else if(res1[i] != res2[i]){
			res_med[i] = '.';
		}
	}

	printf("\n");
	printf("Length = %d\n", lenght);
	printf("Identity = %d/%d (%2.1f%%)\n", count_sticks, lenght, (float)(count_sticks*100)/(float)lenght );
	printf("Similarity = %d/%d (%2.1f%%)\n", count_sticks, lenght, (float)(count_sticks*100)/(float)lenght );
	printf("Gaps = %d/%d (%2.1f%%)\n", count_gaps, lenght, (float)(count_gaps*100)/(float)lenght );
	printf("Score = %2.1f\n", Score);

	printf("\n");
	printf("%s\n", res1);
	printf("%s\n", res_med);
	printf("%s\n", res2);


	return;
}

int main(){
	char input[90] = "db2.txt";
	FILE * file = fopen(input, "r");
	if (NULL == file){
		return -1;
	}


	function(file);

	return 0;
}

int getCost(char ch1, char ch2){
	int i = -1;
	switch(ch1){
		case 'A': i = 0;
			break;
		case 'T': i = 1;
			break;
		case 'G': i = 2;
			break;
		case 'C': i = 3;
			break;
	}
	int j = -1;
	switch(ch2){
		case 'A': j = 0;
			break;
		case 'T': j = 1;
			break;
		case 'G': j = 2;
			break;
		case 'C': j = 3;
			break;
	}
	if(-1 == i || -1 == j){
		printf("Invalid character\n");
	}

	return matrix[i][j];
}