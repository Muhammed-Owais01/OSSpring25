#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

FILE *temp_file = NULL;
char temp_filename[] = "/tmp/my_tempfileXXXXXX";  

void handle_sigint(int sig) {
    if (temp_file != NULL) {
        fclose(temp_file);
        temp_file = NULL;
    }

    unlink(temp_filename);

    printf("\nSIGINT received. Temporary file cleaned up and program exiting.\n");
    exit(0);
}

int main() {
    signal(SIGINT, handle_sigint);

    int fd = mkstemp(temp_filename);
    if (fd == -1) {
        perror("mkstemp");
        exit(EXIT_FAILURE);
    }

    temp_file = fdopen(fd, "w");
    if (temp_file == NULL) {
        perror("fdopen");
        close(fd);
        unlink(temp_filename);
        exit(EXIT_FAILURE);
    }

    printf("Temporary file created: %s\n", temp_filename);
    printf("Writing data every second. Press Ctrl+C to stop.\n");

    int counter = 0;
    while (1) {
        fprintf(temp_file, "Data entry #%d\n", counter++);
        fflush(temp_file);  
        sleep(1);
    }

    return 0;
}
