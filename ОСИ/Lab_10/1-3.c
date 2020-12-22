#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define SUCCESS 0
#define PRINT_COUNT 10
#define ERRNO_SET 0
#define EXIT_ERROR 1

pthread_mutex_t mutex[3];

int a[3] = {0,0,0};

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

void my_pthread_mutex_lock(int q) {
    
    while (a[q] != 0) {
        sleep(0.0001);
    }
    a[q]++;
	//printf("%d\n",a);
}

void my_pthread_mutex_unlock(int q) {
    a[q]--;
}

void* thread_body(void *arg) {
    my_pthread_mutex_lock(2);

    for (int i = 0; i < 10; i++) {
        my_pthread_mutex_lock(0);
        my_pthread_mutex_unlock(2);
        my_pthread_mutex_lock(1);
        printf("Child\n");
        my_pthread_mutex_unlock(0);
        my_pthread_mutex_lock(2);
        my_pthread_mutex_unlock(1);
    }

    my_pthread_mutex_unlock(2);
    pthread_exit(NULL);
}


int main(int argc, char *argv[]) {

    //mutex_init();

    my_pthread_mutex_lock(0);
    my_pthread_mutex_lock(1);
    printf("%d %d\n",a[0],a[1]);
    pthread_t thread;

    int error = pthread_create(&thread, NULL, thread_body, "Child\n");
    if (error != SUCCESS) {
        printError("pthread_mutex_unlock() failed", error);
    }

	sleep(1);

    for (int i = 0; i < 10; i++) {
        printf("parent\n");
        my_pthread_mutex_unlock(0);
        my_pthread_mutex_lock(2);
        my_pthread_mutex_unlock(1);

        my_pthread_mutex_lock(0);
        my_pthread_mutex_unlock(2);
        my_pthread_mutex_lock(1);
    }

    my_pthread_mutex_unlock(0);
    my_pthread_mutex_unlock(1);

    error = pthread_join(thread, NULL);
    if (error != SUCCESS) {
        printError("pthread_join() failed", error);
    }

    //mutex_destroy();

    pthread_exit(NULL);
}
