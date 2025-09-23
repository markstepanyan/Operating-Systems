#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid = fork();

    if (pid == 0) {
        // Child process runs "echo" with an argument
        execl("/bin/echo", "echo", "Hello from the child process", NULL);
    } else {
        wait(NULL);
        printf("Parent process done\n");
    }

    return 0;
}
