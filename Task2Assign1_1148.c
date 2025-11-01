/*
 * Name: Eman Babar
 * Reg No: 23-NTU-CS-1148
 * Task 2 - Personalized Greeting Thread
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
void *greet(void *arg) {
    char *name = (char *)arg;
    printf("Thread says: Hello, %s! Welcome to the world of threads.\n", name);
    return NULL;
}
int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <YourName>\n", argv[0]);
        return 1;
    }
    pthread_t tid;
    printf("Main thread: Waiting for greeting...\n");
    /* pass the provided name to thread */
    if (pthread_create(&tid, NULL, greet, argv[1]) != 0) {
        perror("pthread_create");
        return 1;
    }
    pthread_join(tid, NULL);
    printf("Main thread: Greeting completed.\n");
    return 0;
}
