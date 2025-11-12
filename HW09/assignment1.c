#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void* thread_function(void* arg) {
    int thread_num = *(int*)arg;
    printf("Thread %d is running (Thread ID: %lu)\n", thread_num, pthread_self());
    pthread_exit(NULL);
}

int main() {
    pthread_t t1, t2, t3;
    int a = 1, b = 2, c = 3;

    if (pthread_create(&t1, NULL, thread_function, &a) != 0) {
        perror("Failed to create Thread 1");
        exit(1);
    }

    if (pthread_create(&t2, NULL, thread_function, &b) != 0) {
        perror("Failed to create Thread 2");
        exit(1);
    }

    if (pthread_create(&t3, NULL, thread_function, &c) != 0) {
        perror("Failed to create Thread 3");
        exit(1);
    }

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    printf("All threads have completed.\n");
    return 0;
}
