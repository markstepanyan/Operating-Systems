#include <stdio.h>
#include <pthread.h>
#include <math.h>

void* calc_square(void* arg) {
    int num = *(int*)arg;
    double square = pow(num, 2);
    printf("Square of %d is %.0f\n", num, square);
    pthread_exit(NULL);
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5};
    int n = 5;
    pthread_t threads[n];

    for (int i = 0; i < n; i++) {
        pthread_create(&threads[i], NULL, calc_square, &numbers[i]);
    }

    for (int i = 0; i < n; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("All threads finished.\n");
    return 0;
}
