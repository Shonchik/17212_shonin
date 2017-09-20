#include<stdio.h>

int main()
{
	
	long long int otv = 0;
	long long int product = 0;
	int chislo[15] = {0};
	int proverka = 0;

	for (int i = 0; i < 1000; i++) {
		proverka = getchar();
		if (proverka == '\n') {
			proverka = getchar();
		}
		while ((proverka < '0') || (proverka > '9')){
			printf ("Information is not correct");
			proverka = getchar();
			if (proverka == '\n') {
				proverka = getchar();
			}
		}
		chislo[i % 13] = proverka - '0';
		product = 1;
		for (int j = 0; j < 13; j++) {
			product *= chislo[j];
		}
		if (product > otv) {
			otv = product;
		}
	}

	printf("%lld", otv);

}