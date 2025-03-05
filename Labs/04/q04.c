#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>

int main() {
	int input_fd = open("input.txt", O_RDONLY);
	if (input_fd == -1) {
		perror("Could not open input.txt\n");
		return 1;
	}

	int output_fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (output_fd == -1) {
		perror("Could not open output.txt\n");
		return 1;
	}

	char buffer[1024];
	ssize_t bytesRead, bytesWritten;
	while ((bytesRead = read(input_fd, buffer, 1024)) > 0) {
		bytesWritten = write(output_fd, buffer, bytesRead);
		if (bytesWritten != bytesRead) {
			perror("Error writing bytes\n");
			close(input_fd);
			close(output_fd);
			return 1;
		}
	}

	if (bytesRead == -1) {
		perror("Error reading file\n");
	}

	close(input_fd);
	close(output_fd);
	printf("Sucessfully copied data of input.txt to output.txt\n");
	return 0;
}
