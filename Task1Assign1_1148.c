/*
 * Name: Eman Babar
 * Reg No: 23-NTU-CS-1148
 * Task 1 - Thread Information Display
 * Create 5 threads. Each prints pthread_self(), its thread number,
 * sleeps for random 1-3 seconds, then prints completion message.
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#define NTHREADS 5
void *thread_func(void *arg) {
    int thread_num = *(int *)arg;
    pthread_t tid = pthread_self();
    printf("Thread %d: pthread_self() = %lu\n", thread_num, (unsigned long)tid);
    /* sleep random between 1-3 seconds */
    int sleep_time = (rand() % 3) + 1;
    printf("Thread %d: sleeping for %d seconds...\n", thread_num, sleep_time);
    sleep(sleep_time);
    printf("Thread %d: completed work and exiting.\n", thread_num);
    return NULL;
}
int main() {
    srand(time(NULL) ^ (unsigned)getpid());
    pthread_t threads[NTHREADS];
    int thread_args[NTHREADS];
    for (int i = 0; i < NTHREADS; ++i) {
        thread_args[i] = i + 1;
        if (pthread_create(&threads[i], NULL, thread_func, &thread_args[i]) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }
    /* join all threads */
    for (int i = 0; i < NTHREADS; ++i) {
        pthread_join(threads[i], NULL);
    }
    printf("Main thread: All threads joined. Exiting.\n");
    return 0;
}
