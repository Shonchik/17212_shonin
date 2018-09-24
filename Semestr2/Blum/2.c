#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

unsigned int h1(char * str, int lim, int j){
	unsigned int hashAddress = 17;
	for (int counter = 0; str[counter] != '\0'; counter++){
		hashAddress = str[counter] + (hashAddress << 6) + (hashAddress << 16) - hashAddress;
	}
	srand(j * hashAddress);
    hashAddress = rand();
    hashAddress = hashAddress % lim;
	return hashAddress;
}
void push(int hash, void *arr){
	int bit_pos = hash & 7;
	int byte_pos = hash >> 3;
	unsigned char *bin_arr = (unsigned char *)arr;
	bin_arr[byte_pos] |= (1 << bit_pos);
};

unsigned int *add_hash(int lim, int size, int *count){
    int words = 0;
    scanf("%d", &words);
    int hash = 0.7 * ((size * 8 * sizeof(int))/words) + 1; 
    unsigned int *arr = (unsigned int*)calloc(size, sizeof(int));
    char word[20];
    for(int i = 0; i < words; i++){
        scanf("%19s",word);
        printf("\n");
        for(int j = 0; j < hash; j++){
            push(h1(word, lim, j), arr);
        }
    }
    *count = hash;
    return arr;
}

void print(void *arr, int size){
    int count_byte = size * sizeof(int);
    unsigned char *byte_arr = (unsigned char *)arr;
    unsigned char bin = 1;
    bin = bin << 7;
    int control = 0;
    for(int i = 0; i < count_byte; i++){
        while((control | bin) != 0){
            if(0 == (*byte_arr & bin)){
                printf("0");
            }
            else{
                printf("1");
            }
            bin = bin >> 1;
        }
        bin = 1;
        bin = bin << 7;
        byte_arr++;
    }
}

int check(void *arr, int hash){
	int bit_pos = hash & 7;
	int byte_pos = hash >> 3;
	unsigned char *bin_arr = (unsigned char *)arr;
	if (bin_arr[byte_pos] & (1<<bit_pos))
		return 1;
	else return -1;
}

void find (void *arr, int size, int lim, int hash){
    char word[10];
    int control = 0;
    while(0 != strcmp("-1", word)){
        printf("\nprint word for check \n");
        scanf("%9s", word);
        print(arr, size);
        printf("\n");
        for(int i = 0; i < hash; i++){
            control = check(arr, h1(word, lim, i));
            if(control == -1){
                break;
            }
        }
        if(control == 1){
            printf("ok\n");
        }
        else{
            printf("not ok\n");
        }
    }
}

int main(){
    char input[10];
    printf("print size\n");
    scanf("%9s", input);

    int size = atoi(input);
 
    int lim = size * 8 * sizeof(int);
    int hash = 0;
    unsigned int *arr = add_hash(lim, size, &hash);

    print(arr, size);
    printf("\n\n");
    find(arr, size, lim, hash);
    free(arr);
}