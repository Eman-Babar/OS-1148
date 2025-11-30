#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define BUFFER_SIZE 5
int buffer[BUFFER_SIZE];
int in = 0;   // Producer index
int out = 0;  // Consumer index
sem_t empty;  // Counts empty slots
sem_t full;   // Counts full slots
pthread_mutex_t mutex;
// ---------------- PRODUCER ----------------
void* producer(void* arg) {
    int id = *(int*)arg;
    for(int i = 0; i < 3; i++) {  // Each producer produces 3 items
        int item = id * 100 + i;
        sem_wait(&empty);                  // Wait if buffer is full
        pthread_mutex_lock(&mutex);        // Lock shared buffer
        buffer[in] = item;
        printf("Producer %d produced item %d at position %d\n",id, item, in);
        in = (in + 1) % BUFFER_SIZE;
        pthread_mutex_unlock(&mutex);      // Unlock buffer
        sem_post(&full);                   // Signal item added
        sleep(1);
    }
    return NULL;
}
// ---------------- CONSUMER ----------------
void* consumer(void* arg) {
    int id = *(int*)arg;
    for(int i = 0; i < 3; i++) {
        sem_wait(&full);                   // Wait if buffer empty
        pthread_mutex_lock(&mutex);        // Lock buffer
        int item = buffer[out];
        printf("Consumer %d consumed item %d from position %d\n", id, item, out);
        out = (out + 1) % BUFFER_SIZE;
        pthread_mutex_unlock(&mutex);      // Unlock buffer
        sem_post(&empty);                  // Signal empty slot
        sleep(2);  // Consumers are slower
    }
    return NULL;
}
// ---------------- MAIN ----------------
int main() {
    pthread_t prod[2], cons[2];
    int ids[2] = {1, 2};
    // Initialize semaphores
    sem_init(&empty, 0, BUFFER_SIZE);  // All slots empty
    sem_init(&full, 0, 0);             // No slots full
    pthread_mutex_init(&mutex, NULL);
    // Create producer & consumer threads
    for(int i = 0; i < 2; i++) {
        pthread_create(&prod[i], NULL, producer, &ids[i]);
        pthread_create(&cons[i], NULL, consumer, &ids[i]);
    }
    // Wait for Completion
    for(int i = 0; i < 2; i++) {
        pthread_join(prod[i], NULL);
        pthread_join(cons[i], NULL);
    }
    // Cleanup
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);
    return 0;
}