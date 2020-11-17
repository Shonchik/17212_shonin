#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>

#define THREAD_CREATION_SUCCESS 0
#define PRINT_COUNT 10
#define BUFFER_SIZE 256
#define EXIT_ERROR 1

void printLines(const char *str) {
    int i;
    for(i = 0; i < PRINT_COUNT; i++)
        printf(str);
}

void* thread_body(void *param) {
    printLines(param);
    return NULL;
}


int main(int argc, char *argv[]) {
    pthread_t thread;
    int code;

    code = pthread_create(&thread, NULL, thread_body, "Child\n");
    if (code != THREAD_CREATION_SUCCESS) {
        errno = code;
        perror("Error in creating thread\n");
        exit(EXIT_ERROR);
    }

    printLines("Parent\n");
    pthread_exit(NULL);
}
