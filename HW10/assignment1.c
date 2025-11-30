#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define N_THREADS 4
#define M_ITERS   1000000LL

long long counter = 0;

pthread_mutex_t counter_mutex;
pthread_spinlock_t counter_spin;

int mode = 0;

void *worker(void *arg) {
    for (long long i = 0; i < M_ITERS; i++) {
        if (mode == 0) {
            counter++;
        } else if (mode == 1) {
            pthread_mutex_lock(&counter_mutex);
            counter++;
            pthread_mutex_unlock(&counter_mutex);
        } else if (mode == 2) {
            pthread_spin_lock(&counter_spin);
            counter++;
            pthread_spin_unlock(&counter_spin);
        }
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s [nosync|mutex|spin]\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "nosync") == 0) {
        mode = 0;
    } else if (strcmp(argv[1], "mutex") == 0) {
        mode = 1;
    } else if (strcmp(argv[1], "spin") == 0) {
        mode = 2;
    } else {
        fprintf(stderr, "Unknown mode: %s (use nosync|mutex|spin)\n", argv[1]);
        return 1;
    }

    if (mode == 1) {
        pthread_mutex_init(&counter_mutex, NULL);
    } else if (mode == 2) {
        pthread_spin_init(&counter_spin, PTHREAD_PROCESS_PRIVATE);
    }

    pthread_t threads[N_THREADS];

    for (int i = 0; i < N_THREADS; i++) {
        if (pthread_create(&threads[i], NULL, worker, NULL) != 0) {
            perror("pthread_create");
            return 1;
        }
    }

    for (int i = 0; i < N_THREADS; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("pthread_join");
            return 1;
        }
    }

    if (mode == 1) {
        pthread_mutex_destroy(&counter_mutex);
    } else if (mode == 2) {
        pthread_spin_destroy(&counter_spin);
    }

    long long expected = N_THREADS * M_ITERS;
    printf("Mode: %s\n", argv[1]);
    printf("Expected value: %lld\n", expected);
    printf("Actual value:   %lld\n", counter);

    return 0;
}
