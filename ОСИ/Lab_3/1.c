#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>

#define THREAD_COUNT 4
#define THREAD_CREATION_SUCCESS 0
#define BUFFER_SIZE 4

void *thread_func(void *strings) {
    char ** lines = (char **) strings;

    for (int i = 0; i < BUFFER_SIZE; i++){
        if(lines[i] != NULL) {
            printf("%s\n", lines[i]);
        }
    }
    return NULL;
}


int main(){
    pthread_t threads[THREAD_COUNT];
    int code;
    static char* strings[THREAD_COUNT][BUFFER_SIZE] = {
        {"111_1", "111_2"}, {"222_1", "222_2", "222_3","222_4"},
        {"333_1", "333_2", "333_3"}, {"444_1"}
    };

    for (int i = 0; i < THREAD_COUNT; i++) {
        code = pthread_create(&threads[i], NULL, thread_func, strings[i]);
        if (code != THREAD_CREATION_SUCCESS) {
            errno = code;
            perror("Error in creating thread\n");
            exit(EXIT_FAILURE);
        }
    }

    pthread_exit(NULL);
}
