#include <stdio.h>
#include <stdlib.h>

#include "/home/aluno-di/Desktop/SOVACCINES/include/main.h"


//main.h
/* Função que lê os argumentos da aplicação, nomeadamente o número
* máximo de operações, o tamanho dos buffers de memória partilhada
* usados para comunicação, e o número de clientes, de proxies e de
* servidores. Guarda esta informação nos campos apropriados da
* estrutura main_data.
*/
void main_args(int argc, char* argv[], struct main_data* data) {
   if (argc != 6) { 
      printf("Uso: sovaccines max_ops buffers_size n_clients n_proxies n_servers\nExemplo: ./bin/sovaccines 10 10 1 1 1");
             
   } 
   else {

    data->max_ops = atoi(*argv[1]);
    data->buffers_size =  atoi(*argv[2]);
    data->n_clients = atoi(*argv[3]);
    data->n_proxies = atoi(*argv[4]);
    data->n_servers = atoi(*argv[5]);
    
   }
};