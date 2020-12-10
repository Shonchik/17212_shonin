#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define SUCCESS 0
#define PRINT_COUNT 10
#define BUFFER_SIZE 256
#define EXIT_ERROR 1
#define ERRNO_SET 0


int a = 0;

void printError(const char *const msg, int error) {
    if (error != ERRNO_SET) {
        fprintf(stderr, "%s: %s", msg, strerror(error));
    } else {
        if (errno == 0) {
            fprintf(stderr, "%s\n", msg);
        } else {
            perror(msg);
        }
    }
    exit(EXIT_ERROR);
}

void* thread_body(void *param) {
    printf("Child\n" );

    while (1) {
        if (a == 0) {
            a = 1;
            printf("Child\n" );
            a = 0;
        }
    }

    pthread_exit(NULL);
}


int main(int argc, char *argv[]) {
    pthread_t thread;
    int error;

    error = pthread_create(&thread, NULL, thread_body, "Child\n");
    if (error != SUCCESS) {
        printError("Error in creating thread", error);
    }

    while (1) {
        if (a == 0) {
            a = 1;
            printf("Parrent\n" );
            a = 0;
        }
    }

    error = pthread_join(thread, NULL);
    if (error != SUCCESS) {
        printError("pthread_join() failed", error);
    }

    pthread_exit(NULL);
}
