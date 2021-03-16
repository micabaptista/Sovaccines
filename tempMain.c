#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>


int main(int argc, char *argv[]) {
    char id = getuid();
    char name[] = "name";


    strncat(name, &id, 1);
    printf("%s", name);
    return 0;
}