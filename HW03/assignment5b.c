#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {

    pid_t pid = fork();

    if (pid == 0) {
        printf("Child PID=%d exiting \n", getpid());
        exit(0);
    } else if (pid > 0) {
        wait(NULL);
    } else {
        perror("fork");
        return 1;
    }

    return 0;
}

