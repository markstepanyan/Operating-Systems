#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid = fork();

    if (pid == 0) {
        execl("/bin/grep", "grep", "main", "test.txt", NULL);
    } else {
        wait(NULL);
        printf("Parent process completed\n");
    }

    return 0;
}
