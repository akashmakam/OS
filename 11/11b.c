#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0, out = 0, producer_produced = 0, consumer_consumed = 0;
sem_t empty, full;
pthread_mutex_t mutex;

void* producer(void *arg) {
        int item;
        while(1) {
                item = rand()%100;
                sem_wait(&empty);
                pthread_mutex_lock(&mutex);

                if (producer_produced <= 10) {
                        buffer[in] = item;
                        in = (in + 1)%BUFFER_SIZE;
                        printf("Produced produced %d\n", item);
                        producer_produced++;
                }

                pthread_mutex_unlock(&mutex);
                sem_post(&full);

                if (producer_produced >= 10) {
                        break;
                }

                sleep(1);
        }
        return NULL;
}

void* consumer(void *arg) {
        int item;
        while(1) {
                sem_wait(&full);
                pthread_mutex_lock(&mutex);

                if (consumer_consumed <= 10) {
                        item = buffer[out];
                        out = (out + 1)%BUFFER_SIZE;
                        printf("Consumer consumed %d\n", item);
                        consumer_consumed++;
                }

                pthread_mutex_unlock(&mutex);
                sem_post(&empty);

                if (consumer_consumed >= 10) {
                        break;
                }

                sleep(1);
        }
        return NULL;
}

int main() {
        pthread_t t1, t2;
        pthread_mutex_init(&mutex, NULL);
        sem_init(&empty, 0, BUFFER_SIZE);
        sem_init(&full, 0, 0);

        pthread_create(&t1, NULL, producer, NULL);
        pthread_create(&t2, NULL, consumer, NULL);

        pthread_join(t1, NULL);
        pthread_join(t2, NULL);

        sem_destroy(&empty);
        sem_destroy(&full);
        pthread_mutex_destroy(&mutex);

        printf("Production and consumption of %d items completed.\n", 10);
        return 0;
}