#include "memory.h"
#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>


//process.h
/* Função que inicia um processo através da função fork do SO. O novo
* processo pode ser um cliente, proxy, ou servidor, consoante a variável
* process_code tem valor 0, 1, ou 2 respectivamente, e irá executar a função
* execute_* respetiva, fazendo exit do retorno. O processo pai devolve o pid
* do processo criado.
*/
int launch_process(int process_id, int process_code, struct communication_buffers* buffers, struct main_data* data, struct semaphores* sems);
    // VER PARA QUE SERVE O PROCESS_ID


    int pid ;
    int value;
    if ((pid = fork()) == -1) { //houve um erro
        perror(argv[0]);
        exit(1);
    }


    if (pid == 0) { //fork funcionou e este processo é o filho
    /* Processo filho */
        if (process_code == 0)
        {
            value = execute_client( /*nao sei se é isto*/process_id,  buffers,  data,  sems);
            exit(value);
        }
        else if (process_code ==1)
        {
            value = execute_proxy( /*nao sei se é isto*/ process_id,  buffers,  data,  sems);
            exit(value);
        }
        else if (process_code == 2)
        {
            value = execute_server(/*nao sei se é isto*/ process_id,  buffers,  data,  sems);
            exit(value);

        }
        else
        {
            //erro
        }
    } 
    else 
    { //fork funcionou e este processo é o pai
    /* Processo pai */
    return pid;
    }



