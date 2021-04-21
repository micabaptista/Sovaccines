#include <stdio.h>
#include <string.h>
#include <time.h>


FILE * openLogFile(char * name){
    return fopen(name, "w");
}


void registaLog( FILE * fp, char * input){
    struct timespec* time = marcaTempo();
    char * timeFormat = FormataTempo( time);
    
    strcat(input, "\n"); //nao sei se é preciso
    strcat(timeFormat,input);
    fputs(timeFormat, fp);
}

void closeLogFile(FILE * fp){
    fclose(fp); 
}