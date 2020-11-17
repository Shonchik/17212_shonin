#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define THREAD_CANCELING_SUCCESS 0
#define THREAD_CREATION_SUCCESS 0
#define EXIT_ERROR 1
#define NOT_CANCELLED 1

void printError(int code) {
    errno = code;
    perror("Error in creating thread\n");
}

void* thread_body(void * param) {
    while (NOT_CANCELLED){
        pthread_testcancel();
        printf("Child\n");
    }

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    pthread_t thread;
    int code;

    code = pthread_create(&thread, NULL, thread_body, NULL);
    if (code != THREAD_CREATION_SUCCESS) {
        printError(code);
        exit(EXIT_ERROR);
    }

    sleep(2);

    code = pthread_cancel(thread);
    if (code != THREAD_CANCELING_SUCCESS) {
        printError(code);
        exit(EXIT_ERROR);
    }

    printf("Canceled.\n");

    pthread_exit(NULL);
}
