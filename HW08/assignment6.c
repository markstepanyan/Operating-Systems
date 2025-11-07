#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int main(void) {
    const char *filename = "numbers.txt";
    int file_descriptor;
    char buffer[1024];
    ssize_t n_read;
    off_t position = 0;
    int line_count = 0;

    file_descriptor = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (file_descriptor < 0) {
        perror("open");
        return 1;
    }

    for (int i = 1; i <= 10; i++) {
        char line[10];
        int len = snprintf(line, sizeof(line), "%d\n", i);
        if (write(file_descriptor, line, len) != len) {
            perror("write");
            close(file_descriptor);
            return 1;
        }
    }
    close(file_descriptor);

    file_descriptor = open(filename, O_RDWR);
    if (file_descriptor < 0) {
        perror("open for read/write");
        return 1;
    }

    while ((n_read = read(file_descriptor, buffer, sizeof(buffer))) > 0) {
        for (ssize_t i = 0; i < n_read; i++) {
            if (buffer[i] == '\n') line_count++;
            if (line_count == 3) {
                position += i + 1;
                break;
            }
        }
        if (line_count >= 3) break;
        position += n_read;
    }

    if (lseek(file_descriptor, position, SEEK_SET) == (off_t)-1) {
        perror("lseek");
        close(file_descriptor);
        return 1;
    }

    n_read = read(file_descriptor, buffer, sizeof(buffer));
    if (n_read < 0) {
        perror("read");
        close(file_descriptor);
        return 1;
    }

    int remaining_size = n_read - 2;
    char *remaining = malloc(remaining_size);
    if (!remaining) {
        perror("malloc");
        close(file_descriptor);
        return 1;
    }
    memcpy(remaining, buffer + 2, remaining_size);

    char new_line[] = "100\n";
    if (write(file_descriptor, new_line, strlen(new_line)) != (ssize_t)strlen(new_line)) {
        perror("write new line");
        free(remaining);
        close(file_descriptor);
        return 1;
    }

    if (write(file_descriptor, remaining, remaining_size) != remaining_size) {
        perror("write remainder");
        free(remaining);
        close(file_descriptor);
        return 1;
    }

    free(remaining);
    lseek(file_descriptor, 0, SEEK_SET);

    while ((n_read = read(file_descriptor, buffer, sizeof(buffer))) > 0) {
        write(STDOUT_FILENO, buffer, n_read);
    }

    close(file_descriptor);
    return 0;
}
