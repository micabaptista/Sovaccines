#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "../include/main.h"
#include "../include/memory.h"




void getInfo(char *inputFile, struct main_data * data){

    FILE *fp = fopen(inputFile, "r");
    char * line = NULL ;
    size_t len = 0;


    getline(&line, &len, fp);
    data->max_ops = atoi(line);



    getline(&line, &len, fp);
    data->buffers_size = atoi(line);


    getline(&line, &len, fp);
    data->n_clients = atoi(line);
 
    
    getline(&line, &len, fp);
    data->n_proxies = atoi(line);
  

    getline(&line, &len, fp);
    data->n_servers = atoi(line);
   
    getline(&line, &len, fp);
    line[strcspn(line, "\n")] = 0;
    sprintf(data->log_filename, "%s", line);
   

    getline(&line, &len, fp);
    line[strcspn(line, "\n")] = 0;
    sprintf(data->statistics_filename, "%s", line);

    getline(&line, &len, fp);
    data->alarm_time = atoi(line);

  fclose(fp);
}

bool acceptValues(char * inputFile){
    bool valid=false;
    FILE *fp = fopen(inputFile, "r");
    char line[256];

    if(atoi(fgets(line, sizeof(line), fp)) > 0 &&
        atoi(fgets(line, sizeof(line), fp)) > 0   &&
        atoi(fgets(line, sizeof(line), fp))&&
        atoi(fgets(line, sizeof(line), fp)) > 0 &&
        atoi(fgets(line, sizeof(line), fp)) &&
        !strcmp(fgets(line, sizeof(line), fp), "") &&
        !strcmp(fgets(line, sizeof(line), fp),"") &&
        atoi(fgets(line, sizeof(line), fp)) > 0){

        valid=true;
    }
    fclose(fp);

    return valid;
}
