#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
sem_t parking_spaces;
void *car(void *arg)
{
    int id = *(int *)arg;
    printf("Car %d is trying to park...\n", id);
    sem_wait(&parking_spaces); // Try to get a space
    printf("Car %d parked successfully!\n", id);
    sleep(2); // Stay parked for 2 seconds
    printf("Car %d is leaving.\n", id);
    sem_post(&parking_spaces); // Free the space
    return NULL;
}
int main()
{
    pthread_t cars[10];
    int ids[10];
    // Initialize: 3 parking spaces available
    sem_init(&parking_spaces, 0, 3);
    // Create 10 cars (more than spaces!)
    for (int i = 0; i < 10; i++)
    {
        ids[i] = i + 1;
        pthread_create(&cars[i], NULL, car, &ids[i]);
    }
    // Wait for all cars
    for (int i = 0; i < 10; i++)
    {
        pthread_join(cars[i], NULL);
    }
    sem_destroy(&parking_spaces);
    return 0;
}
