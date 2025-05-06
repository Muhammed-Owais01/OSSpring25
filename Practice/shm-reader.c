#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>

int main() {
    const int SIZE = 4096;
    const char* name = "OS";
    int fd;
    char* ptr;

    fd = shm_open(name, O_RDONLY, 0666);
    if (fd == -1) {
        perror("OPEN ERROR\n");
        exit(1);
    }

    ptr = (char *)mmap(0, SIZE, PROT_READ, MAP_SHARED, fd, 0);
    printf("%s\n", (char *)ptr);
    shm_unlink(name);
    return 0;
}