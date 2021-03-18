#include "memory.h"
#include <unistd.h>
#include "main.h"
#include "client.h"
#include "proxy.h"
#include "server.h"

int launch_process(int process_id, int process_code, struct communication_buffers *buffers, struct main_data *data,
                   struct semaphores *sems) {

    int pid;
    int value;
    if ((pid = fork()) == -1) { //houve um erro
        perror(argv[0]);
        exit(1);
    }


    if (pid == 0) { //fork funcionou e este processo é o filho
        /* Processo filho */
        if (process_code == 0) {
            value = execute_client( /*nao sei se é isto*/process_id, buffers, data, sems);
            exit(value);
        } else if (process_code == 1) {
            value = execute_proxy( /*nao sei se é isto*/ process_id, buffers, data, sems);
            exit(value);
        } else if (process_code == 2) {
            value = execute_server(/*nao sei se é isto*/ process_id, buffers, data, sems);
            exit(value);

        } else {
            //erro
        }
    } else { //fork funcionou e este processo é o pai
        /* Processo pai */
        return pid;
    }
}


/* Função que espera que um processo termine através da função waitpid.
* Devolve o retorno do processo, se este tiver terminado normalmente.
*/
int wait_process(int process_id) {
    int status;
    waitpid(process_id, &status);

    if (status == -1) {
        //erro + exit
    }

    return satus;
}

#endif
