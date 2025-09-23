#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    pid_t child1, child2;
    int status;


    child1 = fork();
    if (child1 == 0) {
        printf("Child1 PID=%d\n", getpid());
        exit(0);
    } else if (child1 < 0) {
        perror("fork Child1");
        return 1;
    }


    child2 = fork();
    if (child2 == 0) {
        printf("Child2 PID=%d\n", getpid());
        exit(5);
    } else if (child2 < 0) {
        perror("fork child2");
        return 1;
    }


    waitpid(child1, &status, 0);
    if (WIFEXITED(status)) {
        printf("Parent child1 exit=%d\n", WEXITSTATUS(status));
    } else {
        printf("Parent child1 not OK\n");
    }

    waitpid(child2, &status, 0);
    if (WIFEXITED(status)) {
        printf("Parent child2 exit=%d\n", WEXITSTATUS(status));
    } else {
        printf("Pparent child2 not OK\n");
    }

    return 0;
}
