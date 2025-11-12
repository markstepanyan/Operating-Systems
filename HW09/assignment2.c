#include <stdio.h>
#include <pthread.h>

int arr[] = {1, 2, 3, 4, 5, 6};
int size = 6;

void* sum_half(void* arg) {
    int part = *(int*)arg;
    int start, end, sum = 0;

    if (part == 1) {
        start = 0;
        end = size / 2;
    } else {
        start = size / 2;
        end = size;
    }

    for (int i = start; i < end; i++) {
        sum += arr[i];
    }

    printf("Thread %d sum = %d\n", part, sum);
    pthread_exit(NULL);
}

int main() {
    pthread_t t1, t2;
    int first = 1, second = 2;

    pthread_create(&t1, NULL, sum_half, &first);
    pthread_create(&t2, NULL, sum_half, &second);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}
