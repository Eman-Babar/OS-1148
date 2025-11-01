/*
 * Name: Eman Babar
 * Reg No: 23-NTU-CS-1148
 * Task 4 - Thread Return Values (Factorial)
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
void *compute_factorial(void *arg) {
    int n = *(int *)arg;
    unsigned long long *result = malloc(sizeof(unsigned long long));
    *result = 1;
    for (int i = 2; i <= n; ++i) *result *= i;
    return (void *)result;
}
int main() {
    int n;
    printf("Enter a non-negative integer: ");
    if (scanf("%d", &n) != 1 || n < 0) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    pthread_t tid;
    int *arg = malloc(sizeof(int));
    *arg = n;
    if (pthread_create(&tid, NULL, compute_factorial, arg) != 0) {
        perror("pthread_create");
        free(arg);
        return 1;
    }
    unsigned long long *res;
    pthread_join(tid, (void **)&res);
    printf("Main thread: Factorial of %d = %llu\n", n, *res);
    free(res);
    free(arg);
    return 0;
}