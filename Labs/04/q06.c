#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int main() {
	alarm(5);

	printf("Alarm set for 5 seconds, entering loop...\n");

	int count = 1;
	while (1) {
		printf("Sleeping...%d seconds elapsed\n", count++);
		sleep(1);
	}
	return 0;
}
