#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main () {
    pid_t c1 = fork();
    if (c1 == 0) {
        execl("/bin/ls", "ls", NULL);
    }
    waitpid(c1, NULL, 0);

    pid_t c2 = fork();
    if (c2 == 0) {
        execl("/bin/date", "date", NULL);
    }
    waitpid(c2, NULL, 0);

    printf("Parent process done\n");
    return 0;
}
