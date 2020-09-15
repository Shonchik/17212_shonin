#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define NOTERROR 0

void * thread_body(void * param) {
     int i = 0;
     for (i = 0; i < 10; i++) {
     	printf("Child\n");
     }
}

int main(int argc, char *argv[]) {
    pthread_t thread;
    int code;
    
    code=pthread_create(&thread, NULL, thread_body, NULL);
    if (code!=NOTERROR) {
        char buf[256];
        strerror_r(code, buf, sizeof buf);
        fprintf(stderr, "%s: creating thread: %s\n", argv[0], buf);
        exit(1);
    }
    int i = 0;
    for (i = 0; i < 10; i++) {
    	printf("Parent\n");
    }
sleep(5);
    
    return (EXIT_SUCCESS);
}
