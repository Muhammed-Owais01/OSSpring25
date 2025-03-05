#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int main() {
	pid_t child = fork();
	if (child == 0) {
		for (int i = 0; i < 100; ++i)
			printf("I am a child process\n");
	} else if (child > 0) {
		for (int i = 0; i < 100; ++i)
			printf("I am a parent process\n");
	} else printf("Could not create child\n");
	return 0;
}
