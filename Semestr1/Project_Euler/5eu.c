#include<stdio.h>

int main()
{
	
	int numb_1[20] = {0}; //массив для хранения кол-ва простых чисел
	int numb_2[20] = {0};
	int otv = 1;

	for (int i = 2; i <=20; i++) {
		int chislo = i;
		int index = 2;
		while (chislo > 1) {
			if (chislo % index == 0) {
				numb_1[index]++;
				chislo /= index;
				index = 2;
			} else {
				index++;
			}
		}
		for (int j = 0; j < 20; j++) {
			if (numb_1[j] > numb_2[j]) {
				numb_2[j] = numb_1[j];
			}
			numb_1[j] = 0;
		}
	}

	for (int  i = 0; i < 20; i++) {
		if (numb_2[i] > 0) {
			for (int j = 0; j < numb_2[i]; j++) {
				otv *= i;
			}
		}
	}

	printf("%d", otv);

}