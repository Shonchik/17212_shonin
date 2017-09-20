#include<stdio.h>

int main()
{
	
	int num_A = 999;
	int num_B = 999;
	int polin_1 = 0;
	int polin_2 = 0;
	int otv = 0;

	for (num_A = 999; num_A > 100; num_A--) {
		for (num_B = num_A; num_B > 100; num_B--) {
			polin_1 = num_A * num_B;
			int polin_3 = polin_1;
			while (polin_3 > 0) {
				polin_2 *= 10;
				polin_2 += polin_3 % 10;
				polin_3 /= 10;
			}
			if (polin_1 == polin_2) {
				if 	(polin_1 > otv) {
					otv = polin_1;
				}
			}
			polin_2 = 0;
		}
	}

	printf("%d", otv);

}