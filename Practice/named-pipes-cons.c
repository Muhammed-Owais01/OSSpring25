#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

#define FIFO_FILE "/tmp/myfifo"

int main() {
    int fd;
    char buffer[BUFSIZ];
    ssize_t bytes_read;
    
    fd = open(FIFO_FILE, O_RDONLY);
    if (fd == -1) {
        perror("Open failure\n");
        exit(1);
    }

    while (1) {
        bytes_read = read(fd, buffer, sizeof(buffer) - 1);
        if (bytes_read == -1) {
            perror("Child: read\n");
            close(fd);
            exit(EXIT_FAILURE);
        } else {
            buffer[bytes_read] = '\0';
            printf("Read: %s\n", buffer); 
        }
    }

    close(fd);
}