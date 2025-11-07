#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 4096

int main() {
    char source[256];
    char destination[256];
    int source_file, dest_file;
    ssize_t bytes_read, bytes_written;
    char buffer[BUFFER_SIZE];
    size_t total = 0;

    printf("Enter source file path: ");
    if (fgets(source, sizeof(source), stdin) == NULL) {
        fprintf(stderr, "Error reading source path\n");
        return 1;
    }
    source[strcspn(source, "\n")] = '\0';

    printf("Enter destination file path: ");
    if (fgets(destination, sizeof(destination), stdin) == NULL) {
        fprintf(stderr, "Error reading destination path\n");
        return 1;
    }
    destination[strcspn(destination, "\n")] = '\0';

    source_file = open(source, O_RDONLY);
    if (source_file == -1) {
        fprintf(stderr, "Error opening source: %s\n", strerror(errno));
        return 1;
    }

    dest_file = open(destination, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_file == -1) {
        fprintf(stderr, "Error opening destination: %s\n", strerror(errno));
        close(source_file);
        return 1;
    }

    while ((bytes_read = read(source_file, buffer, BUFFER_SIZE)) > 0) {
        bytes_written = write(dest_file, buffer, bytes_read);

        if (bytes_written == -1) {
            fprintf(stderr, "Error writing: %s\n", strerror(errno));
            close(source_file);
            close(dest_file);
            return 1;
        }

        if (bytes_written != bytes_read) {
            fprintf(stderr, "Incomplete write\n");
            close(source_file);
            close(dest_file);
            return 1;
        }

        total += bytes_written;
    }

    if (bytes_read == -1) {
        fprintf(stderr, "Error reading: %s\n", strerror(errno));
        close(source_file);
        close(dest_file);
        return 1;
    }

    close(source_file);
    close(dest_file);

    printf("Successfully copied %zu bytes from '%s' to '%s'\n", 
           total, source, destination);

    return 0;
}
