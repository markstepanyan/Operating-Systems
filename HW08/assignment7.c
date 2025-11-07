#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int main() {
    char file_path1[256], file_path2[256];
    int file_descriptor1, file_descriptor2;
    char buffer1[1024], buffer2[1024];
    ssize_t bytes_read1, bytes_read2;
    off_t byte_index = 0;

    printf("Enter first file path: ");
    scanf("%255s", file_path1);
    printf("Enter second file path: ");
    scanf("%255s", file_path2);

    file_descriptor1 = open(file_path1, O_RDONLY);
    if (file_descriptor1 < 0) {
        perror("open first file");
        return 1;
    }

    file_descriptor2 = open(file_path2, O_RDONLY);
    if (file_descriptor2 < 0) {
        perror("open second file");
        close(file_descriptor1);
        return 1;
    }

    while (1) {
        bytes_read1 = read(file_descriptor1, buffer1, sizeof(buffer1));
        bytes_read2 = read(file_descriptor2, buffer2, sizeof(buffer2));

        if (bytes_read1 < 0 || bytes_read2 < 0) {
            perror("read");
            close(file_descriptor1);
            close(file_descriptor2);
            return 1;
        }

        ssize_t min_bytes = bytes_read1 < bytes_read2 ? bytes_read1 : bytes_read2;

        for (ssize_t i = 0; i < min_bytes; i++) {
            if (buffer1[i] != buffer2[i]) {
                printf("Files differ at byte %ld\n", (long)(byte_index + i));
                close(file_descriptor1);
                close(file_descriptor2);
                return 1;
            }
        }

        byte_index += min_bytes;

        if (bytes_read1 == 0 && bytes_read2 == 0) {
            printf("Files are identical\n");
            break;
        }

        if (bytes_read1 == 0 || bytes_read2 == 0) {
            printf("Files differ at byte %ld\n", (long)byte_index);
            break;
        }
    }

    close(file_descriptor1);
    close(file_descriptor2);
    return 0;
}
