#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

void sigint_handler(int signum) {
    fprintf(stdout, "Caught SIGINT signal (%d)\n", signum);
    
    exit(signum);
}

int main() {  
    struct sigaction sa;
    sa.sa_handler = sigint_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        printf("sigaction\n");
        return EXIT_FAILURE;
    }

    printf("Press CTRL+C to send a SIGINT signal\n");

    while (1) {
        sleep(1);
    }

    return EXIT_SUCCESS;
}