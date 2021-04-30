#ifndef SOVACCINES_SOTIME_H
#define SOVACCINES_SOTIME_H
#include <time.h>
/**
* SO-036
* Michael Baptista, 54478
* Afonso Rosa, 54395
* Duarte Pinheiro, 54475
 */

/*
* Funçao que marca o tempo atual.
*/
void marcaTempo(struct timespec* tempo);

/**
 * Formata o tempo
 *
 * @param tempo tempo struct
 * @param timeFormat time format
 */
void formataTempo(struct timespec * tempo, char * timeFormat);

#endif