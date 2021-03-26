#include "../include/main.h"
#include "../include/server.h"
#include <stdbool.h>

//SO-036
// Michael Baptista, 54478
// Afonso Rosa, 54395
// Duarte Pinheiro, 54475

int
execute_server(int server_id, struct communication_buffers *buffers, struct main_data *data, struct semaphores *sems) {
    while (true) {
        struct operation op;
        server_receive_operation(&op, buffers, data, sems);

        if (op.id != -1 && *data->terminate == 0) {
            server_process_operation(&op, server_id, &data->server_stats[server_id]);
            server_send_answer(&op, buffers, data, sems);
        }

        if (op.id != -1 && *data->terminate == 1) {
            return data->server_stats[server_id];
        }
    }
}


void server_receive_operation(struct operation *op, struct communication_buffers *buffers, struct main_data *data,
                              struct semaphores *sems) {
    consume_begin(sems->prx_srv);
    if (*data->terminate == 1) {
        return; //ou break;
    }
    read_rnd_access_buffer(buffers->prx_srv, data->buffers_size, op);
    consume_end(sems->prx_srv);
}


void server_process_operation(struct operation *op, int proxy_id, int *counter){
    op->client = proxy_id;
    op->status = 'S';
    *counter +=1;
}


void server_send_answer(struct operation *op, struct communication_buffers *buffers, struct main_data *data,
                        struct semaphores *sems){
    produce_begin(sems->srv_cli);
    write_circular_buffer(buffers->srv_cli, (data->buffers_size +1), op);
    produce_end(sems->srv_cli);
}

