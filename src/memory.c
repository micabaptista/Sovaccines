#include "../include/main.h"
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include <string.h>

//SO-036
// Michael Baptista, 54478
// Afonso Rosa, 54395
// Duarte Pinheiro, 54475

void *create_shared_memory(char *name, int size) {
    
    uid_t id = getuid();
    // sempre que altero a variavel (a) ja consigo criar um pedido no entanto como o semaforo nao fecha
    // não consigo depois voltar a usar o memso e tenho de alterar o valor do int
    char idValue [strlen(name) + sizeof id]; // declarar uma string do msm tamanho do name
    sprintf(idValue, "%s%d", name, id);  // concatenar o id gerado com o nome passado por argumento.

    int *ptr;
    int ret;
    int fd = shm_open(idValue, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
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
    for (int i = 0; i <size ; ++i) {
        ptr[i] = 0;
    }
    return ptr;
}


void *create_dynamic_memory(int size) {
    void *ptr = malloc(size);
    return memset(ptr, 0, size);
}


void destroy_shared_memory(char *name, void *ptr, int size) {
    uid_t id = getuid();
    char idValue [strlen(name) + sizeof id]; // declarar uma string do msm tamanho do name
    sprintf(idValue, "%s%d", name, id);  // concatenar o id gerado com o nome passado por argumento.

    int ret = munmap(ptr, size);
    if (ret == -1) {
        perror("munmap");
        exit(7);
    }

    ret = shm_unlink(idValue);

    if (ret == -1) {
        perror(idValue);
        exit(8);
    }
}


void destroy_dynamic_memory(void *ptr) {
    free(ptr);
}


void write_rnd_access_buffer(struct rnd_access_buffer *buffer, int buffer_size, struct operation *op) {
    int n;
    for (n = 0; n < buffer_size; n++) {
        if (buffer->ptr[n] == 0) {
            buffer->buffer[n] = *op;
            buffer->ptr[n] = 1;
            break;
        }
    }
}


void write_circular_buffer(struct circular_buffer *buffer, int buffer_size, struct operation *op) {
    for (int i = 0; i < buffer_size; ++i) {
        if ((((buffer->in + 1) % buffer_size) != buffer->out)) {
            buffer->buffer[buffer->in] = *op;
            buffer->in = (buffer->in + 1) % buffer_size;
            return;
        }
    }
}


void read_rnd_access_buffer(struct rnd_access_buffer *buffer, int buffer_size, struct operation *op) {
    int n;
    for (n = 0; n < buffer_size; n++) {
        if (buffer->ptr[n] == 1) {
            *op = buffer->buffer[n];
            buffer->ptr[n] = 0;
            return;
        }
    }
    op->id = -1;
}


void read_circular_buffer(struct circular_buffer *buffer, int buffer_size, struct operation *op) {
    if (buffer->in == buffer->out) {
        op->id = -1;
    }
    *op = buffer->buffer[buffer->out];
    buffer->out = (buffer->out + 1) % buffer_size;
}

