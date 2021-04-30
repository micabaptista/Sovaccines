#include "../include/main.h"
#include "../include/process.h"
#include "../include/sotime.h"
#include "../include/sosignal.h"
#include "../include/log.h"
#include "../include/configuration.h"
#include "../include/memory.h"
#include "../include/stats.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>

//SO-036
// Michael Baptista, 54478
// Afonso Rosa, 54395
// Duarte Pinheiro, 54475

void main_args(int argc, char *argv[], struct main_data * data) {

    if (argc != 2) {
        printf("Porfavor insira o ficheiro com a entrada dos parametros,\n"
               "Exemplo: ./bin/SOVACCINES config.txt\n");
        exit(-1);
    
    } else if (acceptValues(argv[1])) {
        printf("Parâmetros passados pelo ficheiro estão incorretos!\n");
        exit(-1);

    } else {
        getInfo(argv[1], data);
    }
}


void create_dynamic_memory_buffers(struct main_data *data) {

    data->client_pids = create_dynamic_memory(data->max_ops * sizeof(int));
    data->proxy_pids = create_dynamic_memory(data->max_ops * sizeof(int));
    data->server_pids = create_dynamic_memory(data->max_ops * sizeof(int));

    data->client_stats = create_dynamic_memory(data->max_ops * sizeof(int));
    data->proxy_stats = create_dynamic_memory(data->max_ops * sizeof(int));
    data->server_stats = create_dynamic_memory(data->max_ops * sizeof(int));

    data->log_filename = create_dynamic_memory(sizeof(char) * 15);
    data->statistics_filename = create_dynamic_memory(sizeof(char) * 15);


}


void create_shared_memory_buffers(struct main_data *data, struct communication_buffers *buffers) {
    
    //random
    buffers->main_cli->ptr = create_shared_memory(STR_SHM_MAIN_CLI_PTR, data->buffers_size);
    buffers->main_cli->buffer = create_shared_memory(STR_SHM_MAIN_CLI_BUFFER, data->buffers_size);
    //circular
    buffers->cli_prx->buffer = create_shared_memory(STR_SHM_CLI_PRX_BUFFER, data->buffers_size);
    //random
    buffers->prx_srv->ptr = create_shared_memory(STR_SHM_PRX_SRV_PTR, data->buffers_size);
    buffers->prx_srv->buffer = create_shared_memory(STR_SHM_PRX_SRV_BUFFER, data->buffers_size);
    //circular
    buffers->srv_cli->buffer = create_shared_memory(STR_SHM_SRV_CLI_BUFFER, data->buffers_size);

    //outros
    data->results = create_shared_memory(STR_SHM_RESULTS, data->buffers_size);
    data->terminate = create_shared_memory(STR_SHM_TERMINATE, data->buffers_size);
}

void create_semaphores(struct main_data *data, struct semaphores *sems) {

    //full
    sems->main_cli->full = semaphore_create(STR_SEM_MAIN_CLI_FULL, 0);
    sems->cli_prx->full = semaphore_create(STR_SEM_CLI_PRX_FULL, 0);
    sems->prx_srv->full = semaphore_create(STR_SEM_PRX_SRV_FULL, 0);
    sems->srv_cli->full = semaphore_create(STR_SEM_SRV_CLI_FULL, 0);

    //empty
    sems->main_cli->empty = semaphore_create(STR_SEM_MAIN_CLI_EMPTY, data->buffers_size);
    sems->cli_prx->empty = semaphore_create(STR_SEM_CLI_PRX_EMPTY, data->buffers_size);
    sems->prx_srv->empty = semaphore_create(STR_SEM_PRX_SRV_EMPTY, data->buffers_size);
    sems->srv_cli->empty = semaphore_create(STR_SEM_SRV_CLI_EMPTY, data->buffers_size);

    //mutex
    sems->main_cli->mutex = semaphore_create(STR_SEM_MAIN_CLI_MUTEX, 1);
    sems->cli_prx->mutex = semaphore_create(STR_SEM_CLI_PRX_MUTEX, 1);
    sems->prx_srv->mutex = semaphore_create(STR_SEM_PRX_SRV_MUTEX, 1);
    sems->srv_cli->mutex = semaphore_create(STR_SEM_SRV_CLI_MUTEX, 1);

    //results
    sems->results_mutex = semaphore_create(STR_SEM_RESULTS_MUTEX, 1);
}

void launch_processes(struct communication_buffers *buffers, struct main_data *data, struct semaphores *sems) {

    for (int i = 0; i < data->n_clients; ++i) {
        data->client_pids[i] = launch_process(i, 0, buffers, data, sems);
    }
    for (int i = 0; i < data->n_proxies; ++i) {
        data->proxy_pids[i] = launch_process(i, 1, buffers, data, sems);

    }
    for (int i = 0; i < data->n_servers; ++i) {
        data->server_pids[i] = launch_process(i, 2, buffers, data, sems);
    }
}




void user_interaction(struct communication_buffers *buffers, struct main_data *data, struct semaphores *sems) {

    FILE * log_file = openLogFile(data->log_filename);
    capturaSinal(buffers, sems);

    char msg[4];
    acionaAlarme(data, sems);

    printf("Ações disponíveis: \n");
    printf("        op - criar um pedido de aquisição de vacinas.\n");
    printf("        read x - consultar o estado do pedido x.\n");
    printf("        stop - termina a execução do sovaccines.\n");
    printf("        help - imprime informação sobre as ações disponíveis.\n");

    while (true) {
        printf("Introduzir ação:\n");
        scanf("%s", msg);
        
        if (strcmp(msg, "op") == 0) {
            registaLog(log_file, msg);
            create_request(data->client_stats, buffers, data, sems);
        } else if (strcmp(msg, "read") == 0) {
            read_answer(data, sems, log_file);
        } else if (strcmp(msg, "stop") == 0) {
            registaLog(log_file, msg);
            stop_execution(data, buffers, sems);
            break;
        } else if (strcmp(msg, "help") == 0) {
            registaLog(log_file, msg);
            printf("Ações disponíveis: \n");
            printf("        op - criar um pedido de aquisição de vacinas.\n");
            printf("        read x - consultar o estado do pedido x.\n");
            printf("        stop - termina a execução do sovaccines.\n");
            printf("        help - imprime informação sobre as ações disponíveis.\n");
        } else {
            registaLog(log_file, msg);
            printf("Ação não reconhecida, insira 'help' para assistência.\n");
        }
        usleep(10000);
    }
    closeLogFile(log_file);
}

void create_request(int *op_counter, struct communication_buffers *buffers, struct main_data *data,
                    struct semaphores *sems) {
                    
    if (*op_counter < data->max_ops) {
        struct timespec time = {0, 0};
        struct operation op = {*op_counter, ' ', -1, -1, -1, time, time, time, time, time};

        produce_begin(sems->main_cli);
        marcaTempo(&op.start_time);
        write_rnd_access_buffer(buffers->main_cli, data->buffers_size, &op);
        produce_end(sems->main_cli);
        printf("O pedido #%d foi criado!\n", *data->client_stats);
        *op_counter = *op_counter + 1;
    } else {
        printf("O número máximo de pedidos foi alcançado!\n");
    }

}


int isDigit(int length, char num[]) {
    int count;
    for (int i = 0; i < length; i++) {
        count += (isdigit(num[i]) != 0) ? 1 : 0;
    }

    return count;

}


void read_answer(struct main_data *data, struct semaphores *sems, FILE * fp) {

    char msg[data->max_ops];
    int number;

    scanf("%s", msg);
    char input[12];
    sprintf(input,"read %s", msg);

    registaLog(fp, input);

    if (isDigit(sizeof(msg) / sizeof(char), msg)) {
        number = atoi(msg);

        if (number > data->max_ops) {
            printf("id de operação fornecido é inválido!\n");
            return;
        }


        semaphore_mutex_lock(sems->results_mutex);
        struct timespec time = {-1, -1};
        struct operation operation = {-1, ' ', -1, -1, -1, time, time, time, time, time};

        for (int i = 0; i < data->max_ops; i++) {
            if (data->results[i].id == number) {
                operation = data->results[i];
                break;
            }
        }
        semaphore_mutex_unlock(sems->results_mutex);


        if (operation.id == -1) {
            printf("Op %d ainda não é válido!\n", number);
        } else {

            printf("Op %d com estado %c foi recebida pelo cliente %d, encaminhada pelo proxy %d, ""e tratada pelo servidor %d!\n",
                   operation.id, operation.status, operation.client, operation.proxy, operation.server);
        }

    } else {
        printf("id de operação fornecido é inválido!\n");
    }
}


void stop_execution(struct main_data *data, struct communication_buffers *buffers, struct semaphores *sems){
    *data->terminate = 1;
    wakeup_processes(data, sems);
    wait_processes(data);

    write_statistics(data);
    write_stats(data, sems);
    destroy_semaphores(sems);
    destroy_shared_memory_buffers(data, buffers);
    destroy_dynamic_memory_buffers(data);
}

/* Função que acorda todos os processos adormecidos em semáforos, para que
* estes percebam que foi dada ordem de terminação do programa. Para tal,
* pode ser usada a função produce_end sobre todos os conjuntos de semáforos
* onde possam estar processos adormecidos e um número de vezes igual ao 
* máximo de processos que possam lá estar.
*/
void wakeup_processes(struct main_data *data, struct semaphores *sems) {

    for (int i = 0; i < data->max_ops; ++i) {
        produce_end(sems->main_cli);
    }

    for (int i = 0; i < data->max_ops; ++i) {
        produce_end(sems->cli_prx);
    }

    for (int i = 0; i < data->max_ops; ++i) {
        produce_end(sems->prx_srv);
    }

    for (int i = 0; i < data->max_ops; ++i) {
        produce_end(sems->srv_cli);
    }

}


void wait_processes(struct main_data *data) {
    for (int i = 0; i < data->n_clients; ++i) {
        data->client_stats[i] = wait_process(data->client_pids[i]);
    }
    for (int i = 0; i < data->n_proxies; ++i) {
        data->proxy_stats[i] = wait_process(data->proxy_pids[i]);
    }
    for (int i = 0; i < data->n_servers; ++i) {
        data->server_stats[i] = wait_process(data->server_pids[i]);
    }
}

void write_statistics(struct main_data *data) {

    printf("Terminando o sovaccines! Imprimindo estatísticas:\n");
    for (int i = 0; i < data->n_clients; ++i) {
        printf("Cliente %d recebeu de %d processos!\n", i, (data->client_stats[i]));
    }

    for (int i = 0; i < data->n_proxies; ++i) {
        printf("Proxy %d encaminhou de %d processo!\n", i, (data->proxy_stats[i]));

    }

    for (int i = 0; i < data->n_servers; ++i) {
        printf("Server %d respondeu de %d processo!\n", i, (data->server_stats[i]));
    }
}


void destroy_dynamic_memory_buffers(struct main_data *data) {
    destroy_dynamic_memory(data->client_pids);
    destroy_dynamic_memory(data->proxy_pids);
    destroy_dynamic_memory(data->server_pids);

    destroy_dynamic_memory(data->client_stats);
    destroy_dynamic_memory(data->proxy_stats);
    destroy_dynamic_memory(data->server_stats);

    destroy_dynamic_memory(data->log_filename);
    destroy_dynamic_memory( data->statistics_filename);

}


void destroy_shared_memory_buffers(struct main_data *data, struct communication_buffers *buffers) {

    destroy_shared_memory(STR_SHM_MAIN_CLI_BUFFER, buffers->main_cli->buffer, data->buffers_size);
    destroy_shared_memory(STR_SHM_MAIN_CLI_PTR, buffers->main_cli->ptr, data->buffers_size);

    destroy_shared_memory(STR_SHM_CLI_PRX_BUFFER, buffers->cli_prx->buffer, data->buffers_size);

    destroy_shared_memory(STR_SHM_PRX_SRV_BUFFER, buffers->prx_srv->buffer, data->buffers_size);
    destroy_shared_memory(STR_SHM_PRX_SRV_PTR, buffers->prx_srv->ptr, data->buffers_size);

    destroy_shared_memory(STR_SHM_SRV_CLI_BUFFER, buffers->srv_cli->buffer, data->buffers_size);

    destroy_shared_memory(STR_SHM_RESULTS, data->results, data->buffers_size);

    destroy_shared_memory(STR_SHM_TERMINATE, data->terminate, data->buffers_size);


}


void destroy_semaphores(struct semaphores *sems) {
    //full
    semaphore_destroy(STR_SEM_MAIN_CLI_FULL, sems->main_cli->full);
    semaphore_destroy(STR_SEM_CLI_PRX_FULL, sems->cli_prx->full);
    semaphore_destroy(STR_SEM_PRX_SRV_FULL, sems->prx_srv->full);
    semaphore_destroy(STR_SEM_SRV_CLI_FULL, sems->srv_cli->full);

    //empty
    semaphore_destroy(STR_SEM_MAIN_CLI_EMPTY, sems->main_cli->empty);
    semaphore_destroy(STR_SEM_CLI_PRX_EMPTY, sems->cli_prx->empty);
    semaphore_destroy(STR_SEM_PRX_SRV_EMPTY, sems->prx_srv->empty);
    semaphore_destroy(STR_SEM_SRV_CLI_EMPTY, sems->srv_cli->empty);

    //mutex
    semaphore_destroy(STR_SEM_MAIN_CLI_MUTEX, sems->main_cli->mutex);
    semaphore_destroy(STR_SEM_CLI_PRX_MUTEX, sems->cli_prx->mutex);
    semaphore_destroy(STR_SEM_PRX_SRV_MUTEX, sems->prx_srv->mutex);
    semaphore_destroy(STR_SEM_SRV_CLI_MUTEX, sems->srv_cli->mutex);

    //results
    semaphore_destroy(STR_SEM_RESULTS_MUTEX, sems->results_mutex);
}
