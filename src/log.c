#include "../include/sotime.h"
#include <stdio.h>
#include <string.h>
#include <time.h>


FILE * openLogFile(char * name){
    return fopen(name, "a");
    
}


void registaLog( FILE * fp, char * input){
    struct timespec time = {-1, -1};

    marcaTempo(&time);

    char timeFormat [40 * sizeof (int)];

    formataTempo(&time,timeFormat);

    strcat(timeFormat, " ");
    strcat(timeFormat,input);
    strcat(timeFormat,"\n\0");
    fputs(timeFormat, fp);

}

void closeLogFile(FILE * fp){
    fclose(fp); 
}