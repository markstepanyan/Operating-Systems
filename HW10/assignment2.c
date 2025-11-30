#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define N_DEPOSIT_THREADS 4
#define N_WITHDRAW_THREADS 4
#define N_OPS_PER_THREAD 100000

long long balance = 0;

pthread_mutex_t balance_mutex;
pthread_spinlock_t balance_spin;

int use_mutex = 1;
int long_cs = 0;

void *deposit_thread(void *arg) {
    for (long long i = 0; i < N_OPS_PER_THREAD; i++) {
        if (use_mutex) {
            pthread_mutex_lock(&balance_mutex);
        } else {
            pthread_spin_lock(&balance_spin);
        }

        if (long_cs) {
            usleep(100);
        }
        balance++;

        if (use_mutex) {
            pthread_mutex_unlock(&balance_mutex);
        } else {
            pthread_spin_unlock(&balance_spin);
        }
    }
    return NULL;
}

void *withdraw_thread(void *arg) {
    for (long long i = 0; i < N_OPS_PER_THREAD; i++) {
        if (use_mutex) {
            pthread_mutex_lock(&balance_mutex);
        } else {
            pthread_spin_lock(&balance_spin);
        }

        if (long_cs) {
            usleep(100);
        }
        balance--;

        if (use_mutex) {
            pthread_mutex_unlock(&balance_mutex);
        } else {
            pthread_spin_unlock(&balance_spin);
        }
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s [mutex|spin] [short|long]\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "mutex") == 0) {
        use_mutex = 1;
    } else if (strcmp(argv[1], "spin") == 0) {
        use_mutex = 0;
    } else {
        fprintf(stderr, "First argument must be mutex or spin\n");
        return 1;
    }

    if (strcmp(argv[2], "short") == 0) {
        long_cs = 0;
    } else if (strcmp(argv[2], "long") == 0) {
        long_cs = 1;
    } else {
        fprintf(stderr, "Second argument must be short or long\n");
        return 1;
    }

    if (use_mutex) {
        pthread_mutex_init(&balance_mutex, NULL);
    } else {
        pthread_spin_init(&balance_spin, PTHREAD_PROCESS_PRIVATE);
    }

    pthread_t deposit_threads[N_DEPOSIT_THREADS];
    pthread_t withdraw_threads[N_WITHDRAW_THREADS];

    time_t start = time(NULL);

    for (int i = 0; i < N_DEPOSIT_THREADS; i++) {
        pthread_create(&deposit_threads[i], NULL, deposit_thread, NULL);
    }

    for (int i = 0; i < N_WITHDRAW_THREADS; i++) {
        pthread_create(&withdraw_threads[i], NULL, withdraw_thread, NULL);
    }

    for (int i = 0; i < N_DEPOSIT_THREADS; i++) {
        pthread_join(deposit_threads[i], NULL);
    }

    for (int i = 0; i < N_WITHDRAW_THREADS; i++) {
        pthread_join(withdraw_threads[i], NULL);
    }

    time_t end = time(NULL);

    if (use_mutex) {
        pthread_mutex_destroy(&balance_mutex);
    } else {
        pthread_spin_destroy(&balance_spin);
    }

    double elapsed = difftime(end, start);

    printf("Lock type: %s\n", use_mutex ? "mutex" : "spin");
    printf("Critical section: %s\n", long_cs ? "long" : "short");
    printf("Final balance: %lld\n", balance);
    printf("Elapsed time: %.2f seconds\n", elapsed);

    return 0;
}
