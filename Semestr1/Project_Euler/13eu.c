#include<stdio.h>

int main()
{
	int symbol = 0;
	int Sum[55] = {0};
	int desyt_part = 0;
	int prov_nach_chisla = 0;

	for (int j = 0; j <= 100; j++) {
		symbol = getchar();
		while ((symbol < '0') || (symbol > '9')){
			printf ("Information is not correct");
			symbol = getchar();
		}
		int i = 4;
		while (symbol != '\n') {   // Считываем сумму цифр всех ста чисел
			if ((symbol < '0') || (symbol > '9')){
			printf ("Information id not correct");
			}else{
				Sum[i] += symbol - '0';
				symbol = getchar();
				i++;
			}
		}
	}

	for (int i = 54; i > 0; i--) {
		desyt_part = Sum[i] / 10;
		Sum[i] = Sum[i] % 10;   // Редактируем наш массив 
		Sum[i - 1] += desyt_part;
	}

	for (int l = 0; l < 55; l++) { // Выводим итоговое число и смотрим на первые 10 чисел
		if (prov_nach_chisla == 1) {
			printf("%d ", Sum[l]);
		}
		if ((Sum[l] > 0) && (prov_nach_chisla == 0)) {
			printf("%d ", Sum[l]);
			prov_nach_chisla++;
		}
	}

}