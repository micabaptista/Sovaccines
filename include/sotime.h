#ifndef SOVACCINES_SOTIME_H
#define SOVACCINES_SOTIME_H

/*
* Funçao que marca o tempo atual.
* Retorna -1 em caso de erro.
*/
struct timespec marcaTempo();

char * formataTempo(struct timespec * tempo);

#endif