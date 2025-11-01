/*
 * Name: Eman Babar
 * Reg No: 23-NTU-CS-1148
 * Task 3 - Number Info Thread
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
void *number_info(void *arg) {
    int n = *(int *)arg;
    long sq = (long)n * n;
    long cube = (long)n * n * n;
    printf("Thread: Number = %d, Square = %ld, Cube = %ld\n", n, sq, cube);
    return NULL;
}
int main() {
    int n;
    printf("Enter an integer: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    pthread_t tid;
    int *arg = malloc(sizeof(int));
    *arg = n;
    if (pthread_create(&tid, NULL, number_info, arg) != 0) {
        perror("pthread_create");
        free(arg);
        return 1;
    }
    pthread_join(tid, NULL);
    free(arg);
    printf("Main thread: Work completed.\n");
    return 0;
}
