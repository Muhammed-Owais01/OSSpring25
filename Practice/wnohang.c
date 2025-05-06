#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/resource.h>

void proc_exit() {
    int wstat;
    pid_t pid;

    while (1) {
        pid = wait3(&wstat, WNOHANG, NULL);
        if (pid == 0 || pid == -1) {
            fprintf(stdout, "return value of wait3() is %d\n", pid);
            return;
        }
        fprintf(stdout, "Return code: %d\n", wstat);
    }
}

int main() {
    signal(SIGCHLD, proc_exit);  // Line #23 stays intact

    for (int i = 0; i < 3; ++i) {
        pid_t pid = fork();
        if (pid == -1) {
            perror("main: fork");
            exit(1);
        } else if (pid == 0) {
            // Child process
            printf("Child %d (pid=%d) is alive (temporarily)\n", i, getpid());
            int ret_code = rand() % 256; // exit code must be in 0-255
            printf("Child %d exiting with return code %d\n", i, ret_code);
            exit(ret_code);
        }
        // Parent continues loop to create next child
    }

    // Parent sleeps long enough for all children to exit
    sleep(5);

    // Optional: pause to keep the process alive if needed
    pause();

    return 0;
}