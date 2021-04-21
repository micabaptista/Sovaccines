#include "../include/main.h"
#include "../include/proxy.h"
#include "../include/sotime.h"
#include <stdbool.h>

//SO-036
// Michael Baptista, 54478
// Afonso Rosa, 54395
// Duarte Pinheiro, 54475

int
execute_proxy(int proxy_id, struct communication_buffers *buffers, struct main_data *data, struct semaphores *sems) {
    while (true) {
        struct operation op;
        proxy_receive_operation(&op, buffers, data, sems);
        if (op.id != -1 && *data->terminate == 0) {
            proxy_process_operation(&op, proxy_id, &data->proxy_stats[proxy_id]);
            op.proxy_time = marcaTempo();
            proxy_forward_operation(&op, buffers, data, sems);
        }

        if (op.id != -1 && *data->terminate == 1) {
            return data->proxy_stats[proxy_id];
        }
    }
}

void proxy_receive_operation(struct operation *op, struct communication_buffers *buffers, struct main_data *data,
                             struct semaphores *sems) {
    consume_begin(sems->cli_prx);
    if (*data->terminate == 1) {
        return;
    }
    read_circular_buffer(buffers->cli_prx, data->buffers_size, op);
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
    write_rnd_access_buffer(buffers->prx_srv, (data->buffers_size +1), op);
    produce_end(sems->prx_srv);
}
