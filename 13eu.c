#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

int main()
{
	int n = 0, Sum[55], ch = 0, k = 0;

	for (int i = 0; i < 55; i++) { // Обнуляем массив хранения сумм цифр всез позиций
		Sum[i] = 0;
	}



	for (int j = 0; j <= 100; j++) {
		n = getchar();
		int i = 4;
		while (n != '\n') {   // Считываем сумму цифр всех ста чисел
			Sum[i] += n - '0';
			i++;
			n = getchar();
		}
	}

	for (int i = 54; i > 0; i--) {
		ch = Sum[i] / 10;
		Sum[i] = Sum[i] % 10;   // Редактируем наш массив 
		Sum[i - 1] += ch;
	}

	for (int l = 0; l < 55; l++) { // Выводим итоговое число и смотрим на первые 10 чисел
		if (k == 1) {
			printf("%d ", Sum[l]);
		}
		if ((Sum[l] > 0) && (k == 0)) {
			printf("%d ", Sum[l]);
			k++;
		}
	}

	//scanf("%d", &n);

}