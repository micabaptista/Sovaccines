
#ifndef SOVACCINES_SOSIGNAL_H
#define SOVACCINES_SOSIGNAL_H

/**
 * Funçao que marca o tempo atual.
 * @param data data main
 * @param sems semáforos
 */
void acionaAlarme( struct main_data* data, struct semaphores *sems );

/**
 * Funçao que escreve o status das operaçoes.
 */
void write_status();

/**
 * Captura o sinal do ctrl C e chama a função ctrlC
 *
 * @param buffers buffers
 * @param sems semaforos
 * @param fp file
 */
void capturaSinal( struct communication_buffers* buffers, struct semaphores* sems);

/**
 * Executa o stop_execution e termina.
 */
void ctrlC ();

/**
 * Captura o sinal ctrlC e ignora
 */
void ignore();
#endif //SOVACCINES_SOSIGNAL_H
