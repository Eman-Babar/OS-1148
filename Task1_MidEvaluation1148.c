/* Name: Eman Babar , Registration Number: 23-NTU-CS-1148
Write a C program that creates 4 threads. Each thread should:
1.  Receive a unique number N as an argument (use values: 10, 20, 30, 40)
2.  Calculate the sum of numbers from 1 to N
3.  Print the thread number and calculated sum
4.  Return the sum through thread's return value
Main thread should:
Create all 4 threads and pass arguments Wait for all threads to complete
 Collect all return values
 Calculate and print the total of all sums*/
#include <stdio.h>
# include <pthread.h>
#include <stdlib.h>
//Function to calculate sum from 1 to N
void* calculate_sum(void* arg){
    int N = *(int*)arg;
    //allocate memory for sum
    int* sum = malloc(sizeof(int));
    *sum = 0;
    //Calculate sum from 1 to N
    for(int i=1;i<=N;i++){
        *sum +=i;
    }
    //Print the thread number and calculated sum
    printf("Thread for N=%d ,Sum = %d\n", N, *sum);
    pthread_exit(sum);
}
int main(){
    pthread_t threads[4];
    int nums[4]= {10,20,30,40};
    int* result[4];
    int total_sum = 0;
    //Create 4 threads
    for (int i=0;i<4;i++){
        if (pthread_create(&threads[i],NULL,calculate_sum, &nums[i]) !=0){
            perror("Failed to create thread");
            return 1;
        }
    }
    //Thread Completion and collect Return Values
    for(int i=0;i<4;i++){
        pthread_join(threads[i], (void**)&result[i]);
        total_sum += *result[i];
        free(result[i]);
    }
    printf("Total Sum = %d\n", total_sum);
    return 0;
}
