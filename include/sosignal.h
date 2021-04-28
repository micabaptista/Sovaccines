
#ifndef SOVACCINES_SOSIGNAL_H
#define SOVACCINES_SOSIGNAL_H

/*
* Funçao que marca o tempo atual.
* Retorna -1 em caso de erro.
*/
void acionaAlarme( struct main_data* data, struct semaphores *sems );

/*
* Funçao que escrve o status das operaçoes.
*/
void write_status();


void capturaSinal( struct communication_buffers* buffers, struct semaphores* sems);
 
void ctrlC ();
#endif //SOVACCINES_SOSIGNAL_H
