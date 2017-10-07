#include <stdio.h>

#define summ 1000

int main()
{
	int a = 0;
	int b = 0;
	int c = 0;
	int proverka = 0;

	for (int i = 499; i > 1; i--) {
		for (int j = summ - i; j > 1; j--) {
			if (i * i == j * j + (summ - i - j) * (summ - i - j)) {
				proverka = 1;
				c = i;
				b = j;
				a = summ - i - j;
				break;
			}
		}
		if (proverka) {
			break;
		}
	}

	printf("%d", a * b * c);

}
