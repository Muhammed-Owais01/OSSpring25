#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

void print_user_id() {
	uid_t uid = getuid();
	printf("User ID: %d\n", uid);
}

int main() {
	pid_t currentPid = getpid();
	pid_t parentPid = getppid();
	printf("Current PID: %d\nParent PID: %d\n", currentPid, parentPid);
	print_user_id();
	return 0;
}
