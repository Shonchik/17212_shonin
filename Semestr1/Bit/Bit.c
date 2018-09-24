#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<math.h>
#include <stdio.h>

#include"Bit_function.h"

int main() {
	double b=0.15625;
	double a=7.8;
	int sign = 0;
	scanf("%lf", &a);

	if (signbit(a) != 0){
		sign = 1;
		a *= -1;
	}

	if (1 == isinf(a)){
		printf("Very big number!");
		return -1;
	}

	int e = gepx(&a);

	double m = a;

	printf("Double: ");
	for (int i=63; i>=0;i--)
		printf("%d", getBit(&a, i));
	printf("\n");
	printf("sign: %d\n", sign);
	printf("exponent: ");
	for (int i=62; i>51;i--)
		printf("%d", getBit(&a, i));
	printf("     %d", e);
	printf("\n");
	printf("mantisa: ");
	for (int i=51; i>=0;i--)
		printf("%d", getBit(&a, i));
	printf("     %lf", m);
	
}