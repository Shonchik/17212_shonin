#include<stdio.h>

int main()
{
	
	int chislo = 2;
	int index = 0;
	int proverka = 0;

	while (index < 10001) {
		proverka = 0;
		for (int i = 2; i < chislo; i++) {
			if (chislo % i == 0) {
				proverka = 1;
			}
		}
		if (proverka == 0) {
			index++;
		}
		chislo++;
	}

	printf("%d", chislo - 1);

}