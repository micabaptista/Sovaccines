#include "../include/sotime.h"
#include <stdio.h>
#include <string.h>
#include <time.h>


FILE * openLogFile(char * name){
    printf("abre ficheiro\n");
    return fopen(name, "a"); 
    
}


void registaLog( FILE * fp, char * input){
    printf("registaLog\n");
    struct timespec time = {-1, -1};
    marcaTempo(&time);
    
    char * timeFormat = formataTempo( &time);
    
    strcat(input, "\n\0");
    strcat(timeFormat, " "); 
    strcat(timeFormat,input);
    printf("ola + %s \n", timeFormat);
    fputs(timeFormat, fp);
    
}

void closeLogFile(FILE * fp){
    fclose(fp); 
}