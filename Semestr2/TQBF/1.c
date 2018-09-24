#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define V_COUNT 5
#define Q_COUNT 5

typedef struct quantor {
	int quantor;
	int var_id;
} quantor;
//(a || c) && b
//(a || b) && (b || !c)
/*
int formula(int vars_vals[V_COUNT])
{
	return (vars_vals[0] || vars_vals[2]) && vars_vals[1];
}

int formula2(int vars_vals[V_COUNT])
{
	return (vars_vals[0] || vars_vals[1]) && (vars_vals[1] || !vars_vals[2]);
}
*/

int formula (int* formul, int vars_vals[V_COUNT], int m) {
	int res1 = 0;
	int res2 = 1;
	for (int i = 0; i < m; i++) {
		res1 = 0;
		for (int j = 0; j < V_COUNT - 1; j++) {
			res1 = (res1 || vars_vals[j]*formul[i * V_COUNT + j]/(j + 1) || vars_vals[j+1]*formul[i * V_COUNT + j + 1]/(j+2));
		}
		printf("%d ", res1);
		res2 = (res2 && res1);
	}
	return res2;
}

int sat(quantor* quantors, int quantors_count, int vars_vals[V_COUNT], int *formul, int m)
{
	if (quantors_count == 0)
		return formula(formul, vars_vals, m);
	else
	{
		int cur_quantor = quantors->quantor;
		int cur_var_id = quantors->var_id;

		vars_vals[cur_var_id] = 1;
		int option1 = sat(quantors + 1, quantors_count - 1, vars_vals, formul, m);
		vars_vals[cur_var_id] = 0;
		int option2 = sat(quantors + 1, quantors_count - 1, vars_vals, formul, m);
		printf("-%d-", option1);
		printf("-%d-\n", option2);
		switch (cur_quantor)
		{
			case 1: return (option1 || option2);
			case 2: return (option1 && option2);
			default: return 0;
		}
	}
}


int main()
{
	int n = 0;
	int m = 0;

	char input[90] = "db2.txt";
    FILE * file = fopen(input, "r");
    if (!file) {
        printf("Error");
        return -1;
    }
	fscanf(file, "%d %d", &n, &m);

	int *formul = (int*)calloc(n*m, sizeof(int));

	for(int i = 0; i < m; i++){
		for(int j = 0; j < V_COUNT; j++){
			fscanf(file, "%d", &formul[i*V_COUNT + j]);
		}
	}

	quantor quantors[Q_COUNT] = { { 1, 0 }, { 1, 1 }, { 2, 2 }, { 2, 3 }, { 2, 4 } };
	int vars_vals[V_COUNT] = { 0 };
	int res = sat(quantors, Q_COUNT, vars_vals, formul, m);
	if (res) {
		printf("True\n");
	} else {
		printf("False\n");
	}
}