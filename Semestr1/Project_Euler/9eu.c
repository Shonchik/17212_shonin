#include <stdio.h>

#define SUMM 1000

int main()
{
	int a = 0;
	int b = 0;
	int c = 0;
	int proverka = 0;

	for (int i = SUMM / 2; i > 1; i--) {
		for (int j = SUMM - i; j > 1; j--) {
			if (i * i == j * j + (SUMM - i - j) * (SUMM - i - j)) {
				proverka = 1;
				c = i;
				b = j;
				a = SUMM - i - j;
				break;
			}
		}
		if (proverka) {
			break;
		}
	}

	printf("%d", a * b * c);

}
