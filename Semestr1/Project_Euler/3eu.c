#include<stdio.h>

int main()
{
	
	long long int n = 600851475143;
	long long int index = 2;
	long long int prime_factor = 0;

	while (n > 1) {
		if (n % index == 0) {
			n /= index;
			if (index > prime_factor) {
				prime_factor = index;
			}
			index = 2;
		} else {
			index++;
		}
	}

	printf("%lld", prime_factor);

}