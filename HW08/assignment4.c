#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int main() {
    const char *filename = "log.txt";
    char input[256];
    char log_line[300];
    ssize_t n_read;
    int file_descriptor;
    off_t offset;

    file_descriptor = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (file_descriptor < 0) {
        perror("open");
        return 1;
    }

    n_read = read(0, input, sizeof(input) - 1);
    if (n_read < 0) {
        perror("read");
        close(file_descriptor);
        return 1;
    }
    input[n_read] = '\0';

    if (input[n_read - 1] == '\n') input[n_read - 1] = '\0';

    snprintf(log_line, sizeof(log_line), "PID=%d: %s\n", getpid(), input);

    if (write(file_descriptor, log_line, strlen(log_line)) != (ssize_t)strlen(log_line)) {
        perror("write");
        close(file_descriptor);
        return 1;
    }

    offset = lseek(file_descriptor, 0, SEEK_CUR);
    if (offset == (off_t)-1) {
        perror("lseek");
        close(file_descriptor);
        return 1;
    }

    printf("New file offset: %ld\n", (long)offset);
    close(file_descriptor);
    return 0;
}
