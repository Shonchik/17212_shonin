#include<stdio.h>

int main()
{
	
	int a = 0;
	int b = 0;
	int c = 0;
	int proverka = 0;

	for (int i = 499; i > 1; i--) {
		for (int j = 1000 - i; j > 1; j--) {
			if (i * i == j * j + (1000 - i - j) * (1000 - i - j)) {
				proverka = 1;
				c = i;
				b = j;
				a = 1000 - i - j;
				break;
			}
		}
		if (proverka == 1) {
			break;
		}
	}

	printf("%d", a * b * c);

}