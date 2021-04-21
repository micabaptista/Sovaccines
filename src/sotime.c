#ifndef SERVER_H_GUARD
#define SERVER_H_GUARD

#include <time.h>
 


/*
* Funçao que marca o tempo atual.
* Retorna -1 em caso de erro.
*/
int marcaTempo(struct timespec* tempo){
    return clock_gettime( CLOCK_REALTIME, tempo);
};

#endif