#include<stdio.h>

int main()
{
	
	int sum = 0;

	for (int i = 3; i < 1000; i++) {
		if ((i % 3 == 0) && (i % 5 == 0)) {
			sum += i;
		} else {
			if (i % 3 == 0) {
				sum += i;
			}
			if (i % 5 == 0) {
				sum += i;
			}
		}
	}

	printf("%d", sum);

}