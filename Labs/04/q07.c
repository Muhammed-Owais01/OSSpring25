#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int main() {
	pid_t child = fork();
	if (child == 0) {
		execlp("ls", "ls", "-l", NULL);
		perror("execlp failed\n");
		exit(1);
	} else if (child > 0) {
		wait(NULL);
	} else {
		perror("Fork failed\n");
		return 1;
	}
	return 0;
}
