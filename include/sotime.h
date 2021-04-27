#ifndef SOVACCINES_SOTIME_H
#define SOVACCINES_SOTIME_H
#include <time.h>

/*
* Funçao que marca o tempo atual.
* Retorna -1 em caso de erro.
*/
void marcaTempo(struct timespec* tempo);

char * formataTempo(struct timespec * tempo);

#endif