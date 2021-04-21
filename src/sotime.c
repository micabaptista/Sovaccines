#ifndef SERVER_H_GUARD
#define SERVER_H_GUARD

#include <time.h>
 


/*
* Funçao que marca o tempo atual.
* Retorna -1 em caso de erro.
*/
struct  timespec * marcaTempo(){
    struct timespec * tempo;
     clock_gettime( CLOCK_REALTIME, tempo);
     return tempo;
};

#endif


char * FormataTempo( struct timespec * tempo){
    struct tm* time2 = localtime(tempo->tv_sec);
    char * timeFormat;
    time_t milli = (tempo->tv_nsec) / 1000000;
    sprintf(timeFormat, "%d-%d-%d %d:%d:%d.%d", 1900 + time2->tm_year, time2->tm_mon, time2->tm_mday, time2->tm_hour, time2->tm_min, time2->tm_sec, (int) milli);
    return timeFormat
}