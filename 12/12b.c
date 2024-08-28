#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// Semaphore and mutex
sem_t wrt;
pthread_mutex_t mutex;

// Shared variables
int read_count = 0;
int data = 0; // Shared resource

void *writer(void *arg) {
    int writer_id = *(int *)arg;

    // Writer tries to enter critical section
    sem_wait(&wrt);

    // Writing to the shared resource
    data++;
    printf("Writer %d is writing data %d\n", writer_id, data);

    // Writer exits critical section
    sem_post(&wrt);
    pthread_exit(0);
}

void *reader(void *arg) {
    int reader_id = *(int *)arg;

    // Reader tries to enter critical section
    pthread_mutex_lock(&mutex);
    read_count++;
    if (read_count == 1) {
        sem_wait(&wrt); // First reader locks the semaphore
    }
    pthread_mutex_unlock(&mutex);

    // Reading the shared resource
    printf("Reader %d is reading data %d\n", reader_id, data);

    // Reader exits critical section
    pthread_mutex_lock(&mutex);
    read_count--;
    if (read_count == 0) {
        sem_post(&wrt); // Last reader unlocks the semaphore
    }
    pthread_mutex_unlock(&mutex);
    pthread_exit(0);
}

int main() {
    pthread_t read[10], write[5];
    int reader_ids[10], writer_ids[5];

    // Initialize semaphores and mutex
    sem_init(&wrt, 0, 1);
    pthread_mutex_init(&mutex, NULL);

    // Creating writer threads
    for (int i = 0; i < 5; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&write[i], NULL, writer, &writer_ids[i]);
    }

    // Creating reader threads
    for (int i = 0; i < 10; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&read[i], NULL, reader, &reader_ids[i]);
    }

    // Joining writer threads
    for (int i = 0; i < 5; i++) {
        pthread_join(write[i], NULL);
    }

    // Joining reader threads
    for (int i = 0; i < 10; i++) {
        pthread_join(read[i], NULL);
    }

    // Destroy semaphores and mutex
    sem_destroy(&wrt);
    pthread_mutex_destroy(&mutex);

    return 0;
}