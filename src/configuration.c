#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "../include/main.h"

void getInfo(char *inputFile,struct main_data *data)
{
    FILE *fp = fopen(inputFile, "r");
    char line[256];

    data->max_ops=atoi(fgets(line, sizeof(line), fp));
    data->buffers_size=atoi(fgets(line, sizeof(line), fp));
    data->n_clients=atoi(fgets(line, sizeof(line), fp));
    data->n_proxies=atoi(fgets(line, sizeof(line), fp));
    data->n_servers=atoi(fgets(line, sizeof(line), fp));
    data->log_filename=fgets(line, sizeof(line), fp) ;
    data->statistics_filename=fgets(line, sizeof(line), fp);
    data->alarm_time=atoi(fgets(line, sizeof(line), fp));
    fclose(fp);
    };

//talvez juntar as duas
bool acceptValues(char * inputFile){
    bool valid=false;
    FILE *fp = fopen(inputFile, "r");
    char line[256];

    if(atoi(fgets(line, sizeof(line), fp)) > 0 && atoi(fgets(line, sizeof(line), fp) > 0 )  && atoi(fgets(line, sizeof(line), fp))
        && atoi(fgets(line, sizeof(line), fp)) > 0 && atoi(fgets(line, sizeof(line), fp)) && !strcomp(fgets(line, sizeof(line), fp), "") 
        && !strcomp(fgets(line, sizeof(line), fp),"") && atoi(fgets(line, sizeof(line), fp) > 0)){ 
        valid=true;
    }
    fclose(fp);
    return valid;
}
