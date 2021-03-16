#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include <string.h>


/* Função que reserva uma zona de memória partilhada com tamanho indicado
* por size e nome name, preenche essa zona de memória com o valor 0, e
* retorna um apontador para a mesma. Pode concatenar o resultado da função
* getuid() a name, para tornar o nome único para o processo.
*/
void *create_shared_memory(char *name, int size) {

    char id = getuid();
    char copy[strlen(name)]; // declarar uma string do msm tamanho do name
    strcpy(copy, name);      // copiar a string que vem do pointer name para a variavel copy
    strcat(copy, &id);   // concatenar o id gerado com o nome passado por argumento.
    int *ptr;
    int ret;
    int fd = shm_open(copy, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("shm");
        exit(1);
    }

    ret = ftruncate(fd, size);
    if (ret == -1) {
        perror("shm");
        exit(2);
    }
    ptr = mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED) {
        perror("shm-mmap");
        exit(3);
    }
    return ptr;
}


/* Função que reserva uma zona de memória dinâmica com tamanho indicado
* por size, preenche essa zona de memória com o valor 0, e retorna um
* apontador para a mesma.
*/
void *create_dynamic_memory(int size) {
    void *ptr = malloc(size);
    return memset(ptr, 0, size);
}


/* Função que liberta uma zona de memória dinâmica previamente reservada.
*/
void destroy_shared_memory(char *name, void *ptr, int size) {

    int ret = munmap(&ptr, size);
    if (ret == -1) {
        perror(name);
        exit(7);
    }
    ret = shm_unlink(name);
    if (ret == -1) {
        perror(name);
        exit(8);
    }
    exit(0);
}


/* Função que liberta uma zona de memória partilhada previamente reservada.
*/
void destroy_dynamic_memory(void *ptr) {
    free(ptr);
}


/* Função que escreve uma operação num buffer de acesso aleatório. A
* operação deve ser escrita numa posição livre do buffer, segundo as
* regras de escrita em buffers de acesso aleatório. Se não houver nenhuma
* posição livre, não escreve nada.
*/
void write_rnd_access_buffer(struct rnd_access_buffer *buffer, int buffer_size, struct operation *op) {
    int n;
    while (true) {
        for (n = 0; n < buffer_size; n++) {
            if (buffer->ptr[n] == 0) {
                buffer->buffer[n] = op;
                buffer->ptr[n] = 1;
                break;
            }
        }
    }
}

/* Função que escreve uma operação num buffer circular. A operação deve
* ser escrita numa posição livre do buffer, segundo as regras de escrita
* em buffers circulares. Se não houver nenhuma posição livre, não escreve
* nada.
*/
void write_circular_buffer(struct circular_buffer *buffer, int buffer_size, struct operation *op) {
    while (true) {
        while (((buffer->in + 1) % buffer_size) == buffer->out)
            buffer->buffer[in] = op;
        buffer->in = (buffer->in + 1) % buffer_size;
    }
}


/* Função que lê uma operação de um buffer de acesso aleatório, se houver
* alguma disponível para ler. A leitura deve ser feita segundo as regras
* de leitura em buffers acesso aleatório. Se não houver nenhuma operação
* disponível, afeta op com o valor -1.
*/
void read_rnd_access_buffer(struct rnd_access_buffer *buffer, int buffer_size, struct operation *op) {
    int n;
    while (true) {
        for (n = 0; n < buffer_size; n++) {
            if (buffer->ptr[n] == 1) {
                op = buffer->buffer[n];
                buffer->ptr[n] = 0;
                break;
            }
        }
    }
}

/* Função que lê uma operação de um buffer circular, se houver alguma
* disponível para ler. A leitura deve ser feita segundo as regras de
* leitura em buffers circular. Se não houver nenhuma operação disponível,
* afeta op->id com o valor -1.
*/
void read_circular_buffer(struct circular_buffer *buffer, int buffer_size, struct operation *op) {
    while (true) {
        while (buffer->in == buffer->out);
        op = buffer->buffer[buffer->out];
        buffer->out = (buffer->out + 1) % buffer_size;
    }
}

