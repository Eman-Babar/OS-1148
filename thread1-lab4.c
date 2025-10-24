 #include <stdio.h>
 #include <pthread.h>
 #include <unistd.h>
 // Thread function - this will run in the new thread
 void* thread_function(void* arg) {
    printf("Hello from the new thread!\n");
    printf("Thread ID: %lu\n", pthread_self());
    return NULL;
 }
 int main() {
    pthread_t thread_id;
    printf("Main thread starting...\n");
    printf("Main Thread ID: %lu\n", pthread_self());
 // Create a new thread
    pthread_create(&thread_id, NULL, thread_function, NULL);
// Wait for the thread to finish
    pthread_join(thread_id, NULL);
    printf("Main thread exiting...\n");
    return 0;
 }