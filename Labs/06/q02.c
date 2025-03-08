#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

#define FIFO_FILE "/tmp/myfifo"

int main() {
	int fd;
	char buffer[1024];
	ssize_t num_bytes;

	mkfifo(FIFO_FILE, 0666);
	fd = open(FIFO_FILE, O_WRONLY);
	if (fd == -1) {
		perror("Open");
		exit(1);
	}

	while (1) {
		printf("Producer: Enter a message (or 'exit' to quit): ");
		fgets(buffer, 1024, stdin);
		num_bytes = write(fd, buffer, strlen(buffer) - 1);
		if (num_bytes == -1) {
			perror("Write");
			exit(1);
		}
		if (strncmp(buffer, "exit", 4) == 0) break;
	}
	close(fd);
	unlink(FIFO_FILE);
	return 0;
}
