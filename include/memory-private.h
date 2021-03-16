#ifndef MEMORY_PRIVATE_H_GUARD
#define MEMORY_PRIVATE_H_GUARD
#include "memory.h"

//estrutura que representa um buffer circular, completar pelos alunos
struct circular_buffer {
    operation buffer[BUFFER_SIZE];
    int in = 0; // apontador de escrita
    int out = 0; // apontador de leitura
};

//estrutura que representa um buffer de acesso aleatório, completar pelos alunos
struct rnd_access_buffer {
    operation buffer[BUFFER_SIZE];
    int ptr[BUFFER_SIZE];
};

#endif
