#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int main() {
	pid_t child = fork();
	if (child == 0) {
		execlp("ls", "ls", NULL);
		perror("execlp failed\n");
	} else if (child > 0) {
		wait(NULL);
	}
	return 0;
}
