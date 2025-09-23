#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


int main(void) {
    pid_t pid = fork();

    if (pid == 0) {
        // Child process runs "ls"
        execl("/bin/ls", "ls", NULL);
    } else {
        // Parent process prints message
	wait(NULL);
        printf("Parent process done\n");
    }

    return 0;
}
