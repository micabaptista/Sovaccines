#ifndef MEMORY_PRIVATE_H_GUARD
#define MEMORY_PRIVATE_H_GUARD
/**
* SO-036
* Michael Baptista, 54478
* Afonso Rosa, 54395
* Duarte Pinheiro, 54475
 */

//estrutura que representa um buffer circular, completar pelos alunos
struct circular_buffer {
    struct operation *buffer;
    int in; // apontador de escrita
    int out; // apontador de leitura
};

//estrutura que representa um buffer de acesso aleatório, completar pelos alunos
struct rnd_access_buffer {
    struct operation *buffer;
    int *ptr;
};

#endif
