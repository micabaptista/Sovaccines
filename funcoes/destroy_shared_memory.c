
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fcntl.h>




/* Função que liberta uma zona de memória dinâmica previamente reservada.
*/
void destroy_shared_memory(char* name, void* ptr, int size){
    int ret = munmap(ptr,size);
    if (ret == -1){
        perror("/shm");
        exit(1);
    }

    //ver se falta getuid()
    ret = shm_unlink(name);
    if (ret == -1){
        perror("/shm");
        exit(2);
    }


}