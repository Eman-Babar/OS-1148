#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#define NUM_ITERATIONS 1000000
int count=10;
pthread_mutex_t mutex; // mutex object
// Critical section function
void critical_section(int process) {
    //printf("Process %d is in the critical section\n", process);
    //sleep(1); // Simulate some work in the critical section
    if(process==0){

        for (int i = 0; i < NUM_ITERATIONS; i++)
        count--;
    }
    else
    {
        for (int i = 0; i < NUM_ITERATIONS; i++)
        count++;
    }
    //printf("Process %d has updated count to %d\n", process, count);
    //printf("Process %d is leaving the critical section\n", process);
}
// Peterson's Algorithm function for process 0
void *process0(void *arg) {
        pthread_mutex_lock(&mutex); // lock
        // Critical section
        critical_section(0);
        // Exit section
        pthread_mutex_unlock(&mutex); // unlock   
    return NULL;
}
// Peterson's Algorithm function for process 1
void *process1(void *arg) {
        pthread_mutex_lock(&mutex); // lock
        // Critical section
        critical_section(1);
        // Exit section
        pthread_mutex_unlock(&mutex); // unlock   
    return NULL;
}
int main() {
    pthread_t thread0, thread1, thread2, thread3;
    pthread_mutex_init(&mutex,NULL); // initialize mutex
    // Create threads
    pthread_create(&thread0, NULL, process0, NULL);
    pthread_create(&thread1, NULL, process1, NULL);
    pthread_create(&thread2, NULL, process0, NULL);
    pthread_create(&thread3, NULL, process1, NULL);
    // Wait for threads to finish
    pthread_join(thread0, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    pthread_mutex_destroy(&mutex); // destroy mutex
    printf("Final count: %d\n", count);
    return 0;
}