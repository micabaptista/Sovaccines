#include "../include/client.h"
#include "../include/sotime.h"
#include <stdbool.h>
#include <stdio.h>

//SO-036
// Michael Baptista, 54478
// Afonso Rosa, 54395
// Duarte Pinheiro, 54475

int
execute_client(int client_id, struct communication_buffers *buffers, struct main_data *data, struct semaphores *sems) {
    while (true) {


        struct operation op;

        client_get_operation(&op, buffers, data, sems);
        if (op.id != -1 && *data->terminate == 0) {
            client_process_operation(&op, client_id, &data->client_stats[client_id]);
           op.client_time = marcaTempo();
            client_send_operation(&op, buffers, data, sems);
            
        }

        client_receive_answer(&op, buffers, data, sems);
        if (op.id != -1 && *data->terminate == 0) {
            client_process_answer(&op, data,sems);
            op.end_time = marcaTempo();
        }
        if (op.id != -1 && *data->terminate == 1) {

            return data->client_stats[client_id];
        }
    }
}


void client_get_operation(struct operation *op, struct communication_buffers *buffers, struct main_data *data,
                          struct semaphores *sems) {

    consume_begin(sems->main_cli);
    if (*data->terminate == 1) {
        return;
    }
    read_rnd_access_buffer(buffers->main_cli, (data->buffers_size +1), op);
    consume_end(sems->main_cli);

}


void client_process_operation(struct operation *op, int cient_id, int *counter) {
    op->client = cient_id;
    op->status = 'C';
    *counter+=1;
}


void client_send_operation(struct operation *op, struct communication_buffers *buffers, struct main_data *data,
                           struct semaphores *sems) {
    produce_begin(sems->cli_prx);
    write_circular_buffer(buffers->cli_prx, (data->buffers_size +1), op);
    produce_end(sems->cli_prx);
}


void client_receive_answer(struct operation *op, struct communication_buffers *buffers, struct main_data *data,
                           struct semaphores *sems) {
    consume_begin(sems->srv_cli);
    if (*data->terminate == 1) {
        return;
    }
    read_circular_buffer(buffers->srv_cli,(data->buffers_size +1), op);
    consume_end(sems->srv_cli);
}
   

void client_process_answer(struct operation *op, struct main_data *data, struct semaphores *sems) {
    semaphore_mutex_lock(sems->results_mutex);
    data->results[op->id] = *op; // data->results = op;
    printf("Pedido #%d concluído! É agora possível consultar!\n", op->id);
    semaphore_mutex_unlock(sems->results_mutex);
}

