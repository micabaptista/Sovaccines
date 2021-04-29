#include <time.h>
#include <stdio.h>
#include <string.h>
#include "../include/sotime.h"
#include "../include/memory.h"

/*
* Funçao que marca o tempo atual.
* Retorna -1 em caso de erro.
*/
void marcaTempo(struct timespec* tempo){
    clock_gettime( CLOCK_REALTIME, tempo);   
}

void formataTempo(struct timespec * tempo, char * timeFormat){
    struct tm* time2 = localtime(&tempo->tv_sec);
    time_t milli = (tempo->tv_nsec) / 1000000;
    sprintf(timeFormat, "%d-%d-%d %d:%d:%d.%d", 1900 + time2->tm_year, time2->tm_mon + 1, time2->tm_mday, time2->tm_hour, time2->tm_min, time2->tm_sec, (int) milli);
    printf("ola11\n");

}
