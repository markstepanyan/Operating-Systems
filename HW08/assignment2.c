#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int main() {
    const char *filename = "data.txt";
    const char *text = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char buffer[100];
    ssize_t bytes_read;
    off_t size_before, size_after;

    int file_descriptor = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (file_descriptor < 0) {
        perror("open for write");
        return 1;
    }

    if (write(file_descriptor, text, strlen(text)) != (ssize_t)strlen(text)) {
        perror("write");
        close(file_descriptor);
        return 1;
    }
    close(file_descriptor);

    file_descriptor = open(filename, O_RDWR);
    if (file_descriptor < 0) {
        perror("open for read/write");
        return 1;
    }

    size_before = lseek(file_descriptor, 0, SEEK_END);
    if (size_before == (off_t)-1) {
        perror("lseek SEEK_END (before)");
        close(file_descriptor);
        return 1;
    }
    printf("Original size: %ld bytes\n", (long)size_before);

    if (ftruncate(file_descriptor, 10) < 0) {
        perror("ftruncate");
        close(file_descriptor);
        return 1;
    }

    size_after = lseek(file_descriptor, 0, SEEK_END);
    if (size_after == (off_t)-1) {
        perror("lseek SEEK_END (after)");
        close(file_descriptor);
        return 1;
    }
    printf("New size after truncation: %ld bytes\n", (long)size_after);

    if (lseek(file_descriptor, 0, SEEK_SET) == (off_t)-1) {
        perror("lseek SEEK_SET");
        close(file_descriptor);
        return 1;
    }

    bytes_read = read(file_descriptor, buffer, sizeof(buffer) - 1);
    if (bytes_read < 0) {
        perror("read");
        close(file_descriptor);
        return 1;
    }
    buffer[bytes_read] = '\0';

    printf("Remaining content: '%s'\n", buffer);

    close(file_descriptor);
    return 0;
}
