#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main() {
    const char *filename = "sparse.bin";
    int file_descriptor;
    off_t file_size;

    file_descriptor = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (file_descriptor < 0) {
        perror("open");
        return 1;
    }

    if (write(file_descriptor, "START", 5) != 5) {
        perror("write START");
        close(file_descriptor);
        return 1;
    }

    if (lseek(file_descriptor, 1024 * 1024, SEEK_CUR) == (off_t)-1) {
        perror("lseek");
        close(file_descriptor);
        return 1;
    }

    if (write(file_descriptor, "END", 3) != 3) {
        perror("write END");
        close(file_descriptor);
        return 1;
    }

    close(file_descriptor);

    file_descriptor = open(filename, O_RDONLY);
    if (file_descriptor < 0) {
        perror("open for read");
        return 1;
    }

    file_size = lseek(file_descriptor, 0, SEEK_END);
    if (file_size == (off_t)-1) {
        perror("lseek SEEK_END");
        close(file_descriptor);
        return 1;
    }

    printf("Apparent file size: %ld bytes\n", (long)file_size);

    close(file_descriptor);
    return 0;
}
