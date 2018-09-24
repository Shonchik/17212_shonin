#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

int satisty(int *formula, int *values, int n, int m){
	int values_2[n];
	int count = 0;
	int c2 = 0;
	int c = 0;

	while(count < m){
		c2 = 0;
		for(int i = 0; i < n; i++){
			values_2[i] = -1;
		}
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				if ((formula[i + count*n] == (j+1)) || (formula[i + count*n] == -(j+1))){
					values_2[j] = values[j] * (formula[i + count*n] / (j+1));
				}
			}
		}
		for(int k = 0; k < n; k++){
			if (values_2[k] == -1){
				c2++;
			}
		}
		if (c2 == n){
			c++;
		}
		count++;
	}
	if (c == 0){
		return 1;
	}
	else{
		return 0;
	}
}

int check(int *formula, int *values, int cur_var, int n, int m){
		if ((cur_var == n)&&(satisty(formula, values, n, m) == 1)){
			return 0;
		}
		for (int i = 0; i < n; i++){
			printf("%d", values[i]);
		}
		values[cur_var] = -1;
		int ok = satisty(formula, values, n, m);
		values[cur_var] = 1;
		int ok2 = satisty(formula, values, n, m);
			if (ok){
				values[cur_var] = -1;
				int t = check(formula, values, cur_var+1, n, m);
				if (!(t == 1)){
					return 0;
				}
			}
			if (ok2){
				values[cur_var] = 1;
				int t = check(formula, values, cur_var+1, n, m);
				if (!(t == 1)){}
						return 0;
			}
		values[cur_var] = 0;
	return 1;
}

int main(){
	int n = 0;
	int m = 0;

	char input[90] = "db2.txt";
    FILE * file = fopen(input, "r");
    if (!file) {
        printf("Error");
        return -1;
    }
	fscanf(file, "%d %d", &n, &m);

	int *formula = (int*)calloc(n*m * sizeof(int), sizeof(int));
	int *values = (int*)calloc(n * sizeof(int), sizeof(int));

	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			fscanf(file, "%d", &formula[j + i*m]);
		}
	}

	check(formula, values, 0, n, m);

	for(int i = 0; i < n; i++){
		printf("%2d ", values[i]);
	}
}