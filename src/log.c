#include "../include/sotime.h"
#include <stdio.h>
#include <string.h>
#include <time.h>


FILE * openLogFile(char * name){
    printf("openlog file + ola1 + %s\n", name);
    if (fopen(name, "a") != NULL)
    {
        printf("openlog file +parabens\n");
    }
    
    
    //depois ver o a
    return fopen(name, "a"); 
}


void registaLog( FILE * fp, char * input){
    
    struct timespec time = {-1, -1};
    marcaTempo(&time);
    
    char * timeFormat = formataTempo( &time);
    
    strcat(input, "\n"); //nao sei se é preciso
    strcat(timeFormat,input);
    
    fputs(timeFormat, fp);
    printf("ola1\n");
}

void closeLogFile(FILE * fp){
    fclose(fp); 
}