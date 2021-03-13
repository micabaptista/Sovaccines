#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fcntl.h>

//-lrt
/* Função que reserva uma zona de memória partilhada com tamanho indicado
* por size e nome name, preenche essa zona de memória com o valor 0, e 
* retorna um apontador para a mesma. Pode concatenar o resultado da função
* getuid() a name, para tornar o nome único para o processo.
*/
void* create_shared_memory(char* name, int size){
    char *id =  getuid(); 
    int shm_fd ;
    void *ptr;


    strcat(name, id);

    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1){
        perror("shm");
        exit(1);
    }


    ftruncate(shm_fd, size);
    if (ret == -1){
        perror("shm");
        exit(2);
    }


    ptr= mmap(0, size, PROT_READ|PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED){
        perror("shm-mmap");
        exit(3);
    }

    for (int i = 0; i < size; i++)
    {
        sprintf(ptr + i, "%c", '0');
    }
    
    return ptr;
    


}
