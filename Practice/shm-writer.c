#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main() {
    const int SIZE = 4096;
    const char* name = "OS";
    const char* message01 = "Hello ";    
    const char* message02 = "World!";
    int fd;
    char* ptr;

    fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    if (fd == -1) {
        perror("SHM OPEN ERROR\n");
        exit(1);
    }

    if (ftruncate(fd, SIZE) == -1) {
        perror("FTRUNCATE ERROR\n");
        exit(1);
    }   

    ptr = (char *)mmap(0, SIZE, PROT_WRITE, MAP_SHARED, fd, 0);
    sprintf(ptr, "%s", message01);
    ptr += strlen(message01);
    sprintf(ptr, "%s", message02);
    ptr += strlen(message02);

    return 0;
}