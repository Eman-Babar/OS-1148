/*
 * Name: Your Name
 * Reg No: YourRegNo
 * Task 5 - Struct-Based Thread Communication (Student DB)
 * This program creates 3 threads; each receives a Student struct and prints info.
 * Main thread counts how many made Dean's list (GPA >= 3.5).
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
typedef struct {
    int student_id;
    char name[50];
    float gpa;
} Student;
typedef struct {
    Student s;
    int index;
} ThreadArg;
void *student_thread(void *arg) {
    ThreadArg *t = (ThreadArg *)arg;
    Student st = t->s;
    printf("Thread %d: ID=%d, Name=%s, GPA=%.2f\n", t->index, st.student_id, st.name, st.gpa);
    if (st.gpa >= 3.5f) {
        printf("Thread %d: %s made the Dean's List.\n", t->index, st.name);
    } else {
        printf("Thread %d: %s did NOT make the Dean's List.\n", t->index, st.name);
    }
    free(t);
    return NULL;
}
int main() {
    pthread_t threads[3];
    Student students[3];
    /* Example students -- replace or gather via input as needed */
    students[0].student_id = 182001;
    strcpy(students[0].name, "Aymen");
    students[0].gpa = 3.7f;
    students[1].student_id = 182002;
    strcpy(students[1].name, "Abeera");
    students[1].gpa = 3.2f;
    students[2].student_id = 182003;
    strcpy(students[2].name, "Samavia");
    students[2].gpa = 3.9f;
    for (int i = 0; i < 3; ++i) {
        ThreadArg *arg = malloc(sizeof(ThreadArg));
        arg->s = students[i];
        arg->index = i + 1;
        if (pthread_create(&threads[i], NULL, student_thread, arg) != 0) {
            perror("pthread_create");
            free(arg);
            return 1;
        }
    }
    /* join and count Dean's List */
    int deans_count = 0;
    for (int i = 0; i < 3; ++i) {
        pthread_join(threads[i], NULL);
    }
    /* simple recount */
    for (int i = 0; i < 3; ++i) if (students[i].gpa >= 3.5f) deans_count++;
    printf("Main thread: Total students on Dean's List = %d\n", deans_count);
    return 0;
}