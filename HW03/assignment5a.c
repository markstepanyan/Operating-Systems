#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {

    pid_t pid = fork();

    if (pid == 0) {
        printf("Child PID=%d exiting \n", getpid());
        exit(0);
    } else if (pid > 0) {
       printf("Parent PID=%d created child PID=%d; sleeping \n", getpid(), pid);
        sleep(15);
        printf("Parent exiting without wait()\n");
    } else {
        perror("fork");
        return 1;
    }

    return 0;
}

