#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int main() {
	pid_t child1, child2;
	child1 = fork();
	if (child1 == 0) {
		printf("Child 1 pid is: %d\n", getpid());
		return 0;
	} else if (child1 > 0) {
		child2 = fork();
		if (child2 == 0) {
			printf("Parent pid by Child2: %d\n", getppid());
			return 0;
		} else if (child2 > 0) {
			wait(NULL);
			wait(NULL);
			printf("Both children are done\n");
		} else printf("Failed to create child 2\n");
	} else printf("Failed to create child 1\n");
	return 0;
}
