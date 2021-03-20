#include "../include/client.h"
#include "../include/server.h"
#include "../include/proxy.h"
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <sys/wait.h>





int launch_process(int process_id, int process_code, struct communication_buffers *buffers, struct main_data *data,
                   struct semaphores *sems) {

    int pid;
    int value;
    if ((pid = fork()) == -1) {
        perror("fork-launcher");
        exit(1);
    }


    if (pid == 0) { //fork funcionou e este processo é o filho
        /* Processo filho */
        if (process_code == 0) {
            value = execute_client(process_id, buffers, data, sems);
            exit(value);
        } else if (process_code == 1) {
            value = execute_proxy( process_id, buffers, data, sems);
            exit(value);
        } else if (process_code == 2) {
            value = execute_server( process_id, buffers, data, sems);
            exit(value);
        }
    } else {
        return pid;
    }
}


/* Função que espera que um processo termine através da função waitpid.
* Devolve o retorno do processo, se este tiver terminado normalmente.
*/
int wait_process(int process_id) {
    int status;
    waitpid(process_id, &status,0);

    if (status == -1) {
        perror("wait-process-launhcer");
        exit(1);
    }
    return status;
}
