 #include <stdio.h>
 #include <unistd.h>
 int main() {
 pid_t pid = fork();
 if (pid == 0) {
 // This block runs in the child process
 printf("Child: PID=%d, Parent=%d\n", getpid(), getppid());
 } else {
 // This block runs in the parent process
 printf("Parent: PID=%d, Child=%d\n", getpid(), pid);
}
 return 0;
 }