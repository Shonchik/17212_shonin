#include <stdio.h>

#define WIDTH 9

int null_stolb (int matr[WIDTH][WIDTH]) {

	for (int i = 0; i < WIDTH; i++) {
		int count = 0;
		for (int j = 0; j < WIDTH; j++) {
			if (matr[j][i] == 1){
				count ++;
			}
			if (matr[j][i] == -1){
				count ++;
				break;
			}
		}
		if (count == 0) {
			return i;
		}
	}
	return -1;
}

int main(){
	int matr[WIDTH][WIDTH] = {0};
	matr[0][3] = 1;
	matr[1][2] = 1;
	matr[3][2] = 1;
	matr[3][7] = 1;
	matr[4][0] = 1;
	matr[4][3] = 1;
	matr[5][1] = 1;
	matr[6][2] = 1;
	matr[7][5] = 1;
	matr[8][3] = 1;
	matr[8][6] = 1;
	//matr[7][0] = 1;

	int otv[WIDTH] = {0};
	int i = 0;

	while (i < WIDTH){
		int point = null_stolb(matr);

		while(point != -1){
			otv[i] = point;
			printf("%d ", otv[i]);
			i++;
			for (int j = 0; j < WIDTH; j++) {
				matr[j][point] = -1;
			}
			point = null_stolb(matr);
		}
		for (int j = 0; j < i; j++) {
			for (int k = 0; k < WIDTH; k++) {
				if (matr[otv[j]][k] == 1){
					matr[otv[j]][k] = 0;
				}
			}
		}
		if (i != 9){
			if (null_stolb(matr) == -1) {
				printf("\nloop in the graph");
				return 0;
			}
		}

	}


}
