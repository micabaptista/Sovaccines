
#ifndef SOVACCINES_SOSIGNAL_H
#define SOVACCINES_SOSIGNAL_H

/*
* Funçao que marca o tempo atual.
* Retorna -1 em caso de erro.
*/
int acionaAlarme( struct main_data* data, struct operation* op);

/*
* Funçao que escrve o status das operaçoes.
*/
void write_status();

#endif //SOVACCINES_SOSIGNAL_H
