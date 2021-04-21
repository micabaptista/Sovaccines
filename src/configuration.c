#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "main.h"

void putValues(char inputFile[],struct main_data *data)
{
    FILE *fp;
   
    
    fp = fopen(inputFile, "r");


    data->max_ops=atoi(fgetc(fp));
    data->buffers_size=atoi(fgetc(fp));
    data->n_clients=atoi(fgetc(fp));
    data->n_proxies=atoi(fgetc(fp));
    data->n_servers=atoi(fgetc(fp));
    data->log_filename=fgetc(fp);
    data->statistics_filename=fgetc(fp);
    data->alarm_time=atoi(fgetc(fp));


   fclose(fp);
   



};


bool acceptValues(char inputFile[]){
    bool valid=false;
    FILE *fp;

    if(atoi(fgetc(fp))>0&&atoi(fgetc(fp)>0)&&atoi(fgetc(fp)>0)&&atoi(fgetc(fp))>0&&atoi(fgetc(fp))// op buffer client proxy server
    &&!strcomp(fgetc(fp),"")&&!strcomp(fgetc(fp),"")// logFilename statisticsFileName
    &&atoi(fgetc(fp)>0)){ //alarmTime
    
        valid=true;
    }


   
    
    fp = fopen(inputFile, "r");
    fclose(fp);
    return valid;
}
