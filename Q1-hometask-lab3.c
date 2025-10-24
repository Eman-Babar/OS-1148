#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        execlp("top", "top", NULL);
    } else {
        wait(NULL);
        printf("Child finished\n");
    }
    return 0;
}
