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
    
    char * timeFormat = formataTempo( &time);
    
    strcat(input, "\n"); //nao sei se é preciso
    strcat(timeFormat,input);
    
    fputs(timeFormat, fp);
    
}

void closeLogFile(FILE * fp){
    fclose(fp); 
}