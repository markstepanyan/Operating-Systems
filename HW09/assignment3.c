#include <stdio.h>
#include <pthread.h>

void* print_numbers(void* arg) {
    int thread_num = *(int*)arg;
    for (int i = 1; i <= 5; i++) {
        printf("Thread %d: %d\n", thread_num, i);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t t1, t2, t3;
    int n1 = 1, n2 = 2, n3 = 3;

    pthread_create(&t1, NULL, print_numbers, &n1);
    pthread_create(&t2, NULL, print_numbers, &n2);
    pthread_create(&t3, NULL, print_numbers, &n3);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    printf("All threads finished.\n");
    return 0;
}
