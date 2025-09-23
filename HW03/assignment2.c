#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {

    pid_t child1, child2;
    int status;

    child1 = fork();
    if (child1 == 0) {
        printf("child1 PID=%d, PPID=%d\n", getpid(), getppid());
        exit(42);
    } else if (child1 < 0) {
        perror("fork child1");
        return 1;
    }


    child2 = fork();
    if (child2 == 0) {
        printf("child2 PID=%d, PPID=%d\n", getpid(), getppid());
        exit(7);
    } else if (child2 < 0) {
        perror("fork child2");
        return 1;
    }

    waitpid(child2, &status, 0);
    printf("Parent child2 exit=%d\n", WEXITSTATUS(status));

    wait(&status);
    printf("Parent other child exit=%d\n", WEXITSTATUS(status));

    return 0;
}
