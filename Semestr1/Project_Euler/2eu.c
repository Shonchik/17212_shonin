#include<stdio.h>

int main()
{
	
	int fib_1 = 1;
	int fib_2 = 2;
	int fib_3 = 0;
	int sum = 0;

	while (fib_2 < 4000000) {
		if (fib_2 % 2 == 0) {
			sum += fib_2;
		}
		fib_3 = fib_2 + fib_1;
		fib_1 = fib_2;
		fib_2 = fib_3;
	}

	printf("%d", sum);

}