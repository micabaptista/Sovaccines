#include "memory.h"
#include <unistd.h>
#include "main.h"
#include "client.h"
#include "proxy.h"
#include "server.h"

int launch_process(int process_id, int process_code, struct communication_buffers *buffers, struct main_data *data,
                   struct semaphores *sems) {
    switch (process_code) {
        case 0:
            fork();
            exit(execute_client(process_code, *buffers, *data, *sems));
            return getpid();
            break;

        case 1:
            fork();
            exit(execute_proxy(process_code, *buffers, *data, *sems));
            return getpid();
            break;

        case 2:
            fork();
            exit(execute_server(process_code, *buffers, *data, *sems));
            return getpid();
            break;

        default:
            break;
    }
}


/* Função que espera que um processo termine através da função waitpid.
* Devolve o retorno do processo, se este tiver terminado normalmente.
*/
int wait_process(int process_id) {
    // ?
}

#endif
