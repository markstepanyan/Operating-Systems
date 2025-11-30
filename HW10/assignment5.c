#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define K_PRINTERS 3
#define N_THREADS 10

sem_t printers;
pthread_mutex_t count_mutex;
int current_printing = 0;

void *print_job(void *arg) {
    int id = (int)(long)arg;

    sem_wait(&printers);

    pthread_mutex_lock(&count_mutex);
    current_printing++;
    printf("Thread %d is printing... currently printing: %d\n", id, current_printing);
    pthread_mutex_unlock(&count_mutex);

    usleep(200000);

    pthread_mutex_lock(&count_mutex);
    current_printing--;
    printf("Thread %d finished printing. currently printing: %d\n", id, current_printing);
    pthread_mutex_unlock(&count_mutex);

    sem_post(&printers);

    return NULL;
}

int main() {
    pthread_t threads[N_THREADS];

    sem_init(&printers, 0, K_PRINTERS);
    pthread_mutex_init(&count_mutex, NULL);

    for (int i = 0; i < N_THREADS; i++) {
        pthread_create(&threads[i], NULL, print_job, (void*)(long)i);
    }

    for (int i = 0; i < N_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&printers);
    pthread_mutex_destroy(&count_mutex);

    return 0;
}
