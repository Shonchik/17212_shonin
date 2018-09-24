
#include"Bit_function.h"

int getBit(double * d, int bit){
 
        unsigned mask=1<<bit;
        int res = 0;
        if (bit >32) {
        	if (0 != ((*((unsigned *)d+1))&mask)){
            	res = 1;
        	}
        }
        else if (0 != ((*((unsigned *)d))&mask)){
            res = 1;
        }
        return res;
    }

int gepx(double * d){
	int e = 0;
	if (*d == 0){
		return 0;
	}
	while (*d < 1){
		*d *= 10;
		e--;
	}
	while (*d > 10){
		*d /= 10;
		e++;
	}
	return e;
}