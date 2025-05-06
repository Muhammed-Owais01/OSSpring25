#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int main() {
    pid_t child = fork();

    if (child < 0) {
        perror("Fork Failed\n");
        exit(1);
    }

    if (child == 0) {
        execlp("ps", "ps", NULL);
    } else {
        wait(NULL);
        printf("Child process has finished\n");
    }

    exit(0);
}