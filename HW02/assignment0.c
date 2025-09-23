#include <stdio.h>
#include <unistd.h>

int main () {
    printf("START pid=%d ppid=%d\n", getpid(), getppid());

    pid_t p1 = fork();
    printf("after fork1: pid=%d ppid=%d (p1=%d)\n", getpid(), getppid(), p1);

    pid_t p2 = fork();
    printf("after fork2: pid=%d ppid=%d (p2=%d)\n", getpid(), getppid(), p2);

    pid_t p3 = fork();
    printf("after fork3: pid=%d ppid=%d (p3=%d)\n", getpid(), getppid(), p3);

    return 0;
}
