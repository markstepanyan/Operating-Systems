#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main() {
    char filepath[256];
    int file_descriptor;
    off_t file_size;
    char ch;

    printf("Enter the path to the text file: ");
    if (scanf("%255s", filepath) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }

    file_descriptor = open(filepath, O_RDONLY);
    if (file_descriptor < 0) {
        perror("open");
        return 1;
    }

    file_size = lseek(file_descriptor, 0, SEEK_END);
    if (file_size == (off_t)-1) {
        perror("lseek");
        close(file_descriptor);
        return 1;
    }

    if (file_size == 0) {
        printf("\n");
        close(file_descriptor);
        return 0;
    }

    for (off_t pos = file_size - 1; pos >= 0; pos--) {
        if (lseek(file_descriptor, pos, SEEK_SET) == (off_t)-1) {
            perror("lseek");
            close(file_descriptor);
            return 1;
        }

        if (read(file_descriptor, &ch, 1) != 1) {
            perror("read");
            close(file_descriptor);
            return 1;
        }

        write(STDOUT_FILENO, &ch, 1);
    }

    printf("\n");
    close(file_descriptor);
    return 0;
}
