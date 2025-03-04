#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

#define BUFFER_SIZE 1024
#define FILE_NAME "input.txt"

int main() {
	int fd;
	char buffer[BUFFER_SIZE];
	ssize_t bytesRead;

	fd = open(FILE_NAME, O_RDONLY);
	if (fd == -1) {
		perror("Error opening file for reading");
		exit(1);
	}

	bytesRead = read(fd, buffer, sizeof(buffer) - 1);
	if (bytesRead == -1) {
		perror("Error reading file");
		close(fd);
		exit(1);
	}
	buffer[bytesRead] = '\0';
	close(fd);

	printf("Original file contents:\n%s\n", buffer);

	pid_t pid = fork();
	if (pid < 0) {
		perror("Fork failed");
		exit(1);
	}

	if (pid == 0) {
		fd = open(FILE_NAME, O_WRONLY | O_TRUNC);
		if (fd == -1) {
			perror("Could not open file");
			exit(1);
		}
		const char* newContent = "Written by child process\n";
		if (write(fd, newContent, strlen(newContent)) == -1) {
			perror("Could not write to file");
			close(fd);
			exit(1);
		}
		close(fd);
		execlp("cat", "cat", FILE_NAME, NULL);
		perror("execlp failed");
		exit(1);
	} else {
		wait(NULL);
		printf("Parent process exiting");
	}
	return 0;
}
