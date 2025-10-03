 #include <stdio.h>
 #include <unistd.h>
 int main() {
 printf("My PID: %d\n", getpid());
 printf("My Parent PID: %d\n", getppid());
 return 0;
 }