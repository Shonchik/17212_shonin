#include<stdio.h>

int main()
{
	
	int sum_kv = 0;
	int kv_sum = 0;
	int otv = 0;

	for (int i = 1; i <= 100; i++) {
		sum_kv += i * i;
		kv_sum += i;
	}

	kv_sum *= kv_sum;
	otv = kv_sum - sum_kv;

	printf("%d", otv);

}