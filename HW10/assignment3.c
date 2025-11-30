#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 8
#define P_PRODUCERS 4
#define C_CONSUMERS 4
#define ITEMS_PER_PRODUCER 1000

int buffer[BUFFER_SIZE];
int in_pos = 0;
int out_pos = 0;

sem_t empty_slots;
sem_t full_slots;
pthread_mutex_t buffer_mutex;

void *producer(void *arg) {
    int id = (int)(long)arg;
    for (int i = 0; i < ITEMS_PER_PRODUCER; i++) {
        int item = id * 100000 + i;

        sem_wait(&empty_slots);
        pthread_mutex_lock(&buffer_mutex);

        buffer[in_pos] = item;
        in_pos = (in_pos + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&buffer_mutex);
        sem_post(&full_slots);
    }
    return NULL;
}

void *consumer(void *arg) {
    int items_per_consumer = (P_PRODUCERS * ITEMS_PER_PRODUCER) / C_CONSUMERS;
    for (int i = 0; i < items_per_consumer; i++) {
        int item;

        sem_wait(&full_slots);
        pthread_mutex_lock(&buffer_mutex);

        item = buffer[out_pos];
        out_pos = (out_pos + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&buffer_mutex);
        sem_post(&empty_slots);

        (void)item;
    }
    return NULL;
}

int main() {
    pthread_t prod_threads[P_PRODUCERS];
    pthread_t cons_threads[C_CONSUMERS];

    sem_init(&empty_slots, 0, BUFFER_SIZE);
    sem_init(&full_slots, 0, 0);
    pthread_mutex_init(&buffer_mutex, NULL);

    for (int i = 0; i < P_PRODUCERS; i++) {
        pthread_create(&prod_threads[i], NULL, producer, (void*)(long)i);
    }

    for (int i = 0; i < C_CONSUMERS; i++) {
        pthread_create(&cons_threads[i], NULL, consumer, NULL);
    }

    for (int i = 0; i < P_PRODUCERS; i++) {
        pthread_join(prod_threads[i], NULL);
    }

    for (int i = 0; i < C_CONSUMERS; i++) {
        pthread_join(cons_threads[i], NULL);
    }

    sem_destroy(&empty_slots);
    sem_destroy(&full_slots);
    pthread_mutex_destroy(&buffer_mutex);

    printf("Finished producer–consumer with %d producers, %d consumers.\n",
           P_PRODUCERS, C_CONSUMERS);

    return 0;
}
