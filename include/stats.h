#ifndef SOVACCINES_STATS_H
#define SOVACCINES_STATS_H

#include "../include/main.h"
#include <stdio.h>
/**
* SO-036
* Michael Baptista, 54478
* Afonso Rosa, 54395
* Duarte Pinheiro, 54475
 */

/**
 * Escreve todas as estatísticas num ficheiro que foram feitas durante a execução do programa
 *
 * @param data data main
 * @param sems semaforos
 */
void write_stats(struct main_data *data, struct semaphores *sems);

#endif //SOVACCINES_STATS_H
