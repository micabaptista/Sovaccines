#ifndef SERVER_H_GUARD
#define SERVER_H_GUARD

#include "main.h"
#include "memory.h"



/*
* Funçao que marca o tempo atual.
* Retorna -1 em caso de erro.
*/
int acionaAlarme( struct main_data* data, struct operation* op);


/*
* Funçao que escrve o status das operaçoes.
*/
void write_status();

#endif