#include<stdio.h>

int prime[5000000];

int main()
{
	
	long long int sum = 0;
	int proverka = 0;

	int n = 2000000;

	for (int i = 0; i < 5000000; i++) {
		prime[i] = 1;
	}

	prime[0] = 0;
	prime[1] = 0;
	for (int i = 2; i < n; i++) {
		if (prime[i] == 1) {
			for (int j = i + i; j < n; j += i) {
				prime[j] = 0;
			}
		}
	}

	for (int i = 0; i < n; i++) {
		if (prime[i] == 1) {
			sum += i;
		}
	}

	printf("%lld", sum);

}