#include "../include/main.h"
#include "../include/client.h"
#include "../include/memory.h"
#include "../include/memory-private.h"
#include "../include/process.h"
#include "../include/proxy.h"
#include "../include/server.h"
#include "../include/synchronization.h"

#include <stdbool.h>

int
execute_server(int server_id, struct communication_buffers *buffers, struct main_data *data, struct semaphores *sems) {
    while (true) {
        struct operation op;
        server_receive_operation(&op, buffers, data, sems);
        if (op.id != -1 && data->terminate == 0) {
            server_process_operation(&op, server_id, data->server_stats);
            server_send_answer(&op, buffers, data, sems);
        }
        //2.
        if (op.id == -1) {};

        if (*data->terminate == 1) {
            return sizeof(data->results);
        }
    }
}



/* Função que lê uma operação do buffer de memória partilhada entre
* proxies e servidores, efetuando a necessária sincronização antes e
* depois de ler. Quando o processo acorda da sincronização, e antes de
* tentar ler a operação, deve verificar se data->terminate tem valor 1.
* Em caso afirmativo, retorna imediatamente da função.
*/
void server_receive_operation(struct operation *op, struct communication_buffers *buffers, struct main_data *data,
                              struct semaphores *sems) {
    consume_begin(sems->prx_srv);
    if (*data->terminate == 1) {
        return; //ou break;
    }
    read_rnd_access_buffer(buffers->prx_srv, sizeof(buffers->prx_srv), op);
    consume_end(sems->prx_srv);
}


/* Função que processa uma operação, alterando o seu campo server para o id
* passado como argumento, alterando o estado da mesma para 'S' (served), e
* incrementando o contador de operações.
*/
void server_process_operation(struct operation *op, int proxy_id, int *counter){
    op->client = proxy_id;
    op->status = 'S';
    *counter +=1;
}


/* Função que escreve uma operação no buffer de memória partilhada entre
* servidores e clientes, efetuando a necessária sincronização antes e
* depois de escrever.
*/
void server_send_answer(struct operation *op, struct communication_buffers *buffers, struct main_data *data,
                        struct semaphores *sems){
    produce_begin(sems->srv_cli);
    write_circular_buffer(buffers->srv_cli, sizeof(buffers->srv_cli), op);
    produce_end(sems->srv_cli);
}

