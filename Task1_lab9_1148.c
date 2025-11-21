 #include <stdio.h>
 #include <pthread.h>
 #include <semaphore.h>
 #include <unistd.h>
 sem_t mutex; // Binary semaphore
 int counter = 0;
 void* thread_function(void* arg) {
 int id = *(int*)arg;
 for (int i = 0; i < 5; i++) {
 printf("Thread %d: Waiting...\n", id);
 //sem_wait(&mutex); // Acquire
// Critical section
 counter++;
 printf("Thread %d: In critical section | Counter = %d\n", id,
 counter);
 sleep(1);
 sem_post(&mutex); // Release
 sleep(1);
 }
 return NULL;
 }
 int main() {
 sem_init(&mutex, 0, 1); // Binary semaphore initialized to 1
 pthread_t t1, t2;
 int id1 = 1, id2 = 2;
 pthread_create(&t1, NULL, thread_function, &id1);
 pthread_create(&t2, NULL, thread_function, &id2);
 pthread_join(t1, NULL);
 pthread_join(t2, NULL);
 printf("Final Counter Value: %d\n", counter);
 sem_destroy(&mutex);
 return 0;
 }