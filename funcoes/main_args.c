#include <stdio.h>
#include <stdlib.h>

#include "/home/aluno-di/Desktop/SOVACCINES/include/main.h"



void main_args(int argc, char* argv[], struct main_data* data) {
   if (argc != 6) { 
      printf("Uso: sovaccines max_ops buffers_size n_clients n_proxies n_servers\nExemplo: ./bin/sovaccines 10 10 1 1 1");
             
   } else
   {
    //MUDAR PARA ATOI()   
    data->max_ops = *argv[1] - '0';
    data->buffers_size =  *argv[2] - '0';
    data->n_clients = *argv[3] - '0';
    data->n_proxies = *argv[4] - '0';
    data->n_servers = *argv[5] - '0';
    
   }
};