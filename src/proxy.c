#include "../include/main.h"
#include "../include/client.h"
#include "../include/memory.h"
#include "../include/memory-private.h"
#include "../include/process.h"
#include "../include/proxy.h"
#include "../include/server.h"
#include "../include/synchronization.h"
#include <stdio.h>

#include <stdbool.h>


int
execute_proxy(int proxy_id, struct communication_buffers *buffers, struct main_data *data, struct semaphores *sems) {
    while (true) {
        struct operation op;
        proxy_receive_operation(&op, buffers, data, sems);
        if (op.id != -1 && data->terminate == 0) {
            proxy_process_operation(&op, proxy_id, data->proxy_stats);
            proxy_forward_operation(&op, buffers, data, sems);
        }
        //2.
        if (op.id == -1) {};

        if (*data->terminate == 1) {
            return sizeof(data->results);
        }
    }
}

void proxy_receive_operation(struct operation *op, struct communication_buffers *buffers, struct main_data *data,
                             struct semaphores *sems) {
    consume_begin(sems->cli_prx);
    if (*data->terminate == 1) {
        return; //ou break;
    }
    read_circular_buffer(buffers->cli_prx, sizeof(buffers->cli_prx), op);
    consume_end(sems->cli_prx);
}

void proxy_process_operation(struct operation *op, int server_id, int *counter) {
    op->client = server_id;
    op->status = 'P';
    *counter+=1;
}

void proxy_forward_operation(struct operation *op, struct communication_buffers *buffers, struct main_data *data,
                             struct semaphores *sems) {
    produce_begin(sems->prx_srv);
    write_rnd_access_buffer(buffers->prx_srv, sizeof(buffers->prx_srv), op);
    produce_end(sems->prx_srv);
}
