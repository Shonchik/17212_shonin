#include <stdio.h>

#define NUMB 112          // Сделаем 112 9 значных чисел
#define SIZE 1000000000   // 9 значное число

int main() {
 	int i = 0;
	int bigNum1[NUMB] = {0};  //Разбиваем наше 1000 значное число на 111 9 значных чисел
 	int bigNum2[NUMB] = {0};
	int bigNum3[NUMB] = {0};
	int index = 0;

	bigNum1[0] = 1;
	bigNum2[0] = 1;
	index = 2;

 	while (i == 0) {
    	index++;
	    for (int j = 0; j < NUMB; j++) {
	      	bigNum3[j] = bigNum2[j] + bigNum1[j]; //Считаем числа фибоначчи для каждого разбиения
	    }
	    for (int j = 0; j < NUMB-1; j++) {
	      	while (bigNum3[j] >= SIZE) {  //Разбиваем слишком большие числа
		bigNum3[j] -= SIZE;
		bigNum3[j+1]++;
	     	}
	    }
	    if (bigNum3[111] >= 1) {//Выходим из цикла и возвращаем индекс
	      	break;
	  	}
	    for (int j = 0; j < NUMB; j++) { // Подготавливаем числа фибоначчи для счёта
	      	bigNum1[j] = bigNum2[j];
	      	bigNum2[j] = bigNum3[j];
	    }
	}
  	printf("%d", index);  
}