 #include <stdio.h>
 #include <pthread.h>
 #include <unistd.h>
 void* worker(void* arg) {
    int thread_num = *(int*)arg;
    printf("Thread %d: Starting task...\n", thread_num);
    sleep(1); // Simulate some work
    printf("Thread %d: Task completed!\n", thread_num);
    return NULL;
 }
 int main() {
    pthread_t threads[3];
    int thread_ids[3];
    for (int i = 0; i < 3; i++) {
        thread_ids[i] = i + 1;
        pthread_create(&threads[i], NULL, worker, &thread_ids[i]);
 }
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
 }
    printf("Main thread: All threads have finished.\n");
    return 0;
 }