#include "../include/main.h"
#include "../include/client.h"
#include "../include/memory.h"
#include "../include/memory-private.h"
#include "../include/process.h"
#include "../include/proxy.h"
#include "../include/server.h"
#include "../include/synchronization.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include  <ctype.h>
#include <math.h>
#include <semaphore.h>
#include  <stdbool.h>

/* Função que lê os argumentos da aplicação, nomeadamente o número
* máximo de operações, o tamanho dos buffers de memória partilhada
* usados para comunicação, e o número de clientes, de proxies e de
* servidores. Guarda esta informação nos campos apropriados da
* estrutura main_data.
*/
void main_args(int argc, char *argv[], struct main_data *data) {
    if (argc != 6) {
        printf("Uso: sovaccines max_ops buffers_size n_clients n_proxies n_servers\n"
               "Exemplo: ./bin/sovaccines 10 10 1 1 1\n$$$");

    } else {

        data->max_ops = atoi(argv[1]);
        data->buffers_size = atoi(argv[2]);
        data->n_clients = atoi(argv[3]);
        data->n_proxies = atoi(argv[4]);
        data->n_servers = atoi(argv[5]);

    }
}

/* Função que reserva a memória dinâmica necessária para a execução
* do sovaccines, nomeadamente para os arrays *_pids e *_stats da estrutura 
* main_data. Para tal, pode ser usada a função create_dynamic_memory do memory.h.
*/
void create_dynamic_memory_buffers(struct main_data *data) {
    data->client_pids = create_dynamic_memory(data->max_ops * sizeof(int));
    data->proxy_pids = create_dynamic_memory(data->max_ops * sizeof(int));
    data->server_pids = create_dynamic_memory(data->max_ops * sizeof(int));

    data->client_stats = create_dynamic_memory(data->max_ops * sizeof(int));
    data->proxy_stats = create_dynamic_memory(data->max_ops * sizeof(int));
    data->server_stats = create_dynamic_memory(data->max_ops * sizeof(int));
}

/* Função que reserva a memória partilhada necessária para a execução do
* sovaccines. É necessário reservar memória partilhada para todos os buffers da
* estrutura communication_buffers, incluindo os buffers em si e respetivos
* pointers, assim como para o array data->results e variável data->terminate.
* Para tal, pode ser usada a função create_shared_memory do memory.h.
*/
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

/* Função que inicializa os semáforos da estrutura semaphores. Semáforos
* *_full devem ser inicializados com valor 0, semáforos *_empty com valor
* igual ao tamanho dos buffers de memória partilhada, e os *_mutex com valor
* igual a 1. Para tal pode ser usada a função semaphore_create.
*/

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

/* Função que inicia os processos dos clientes, proxies e
* servidores. Para tal, pode usar a função launch_process,
* guardando os pids resultantes nos arrays respetivos
* da estrutura data.
*/
void launch_processes(struct communication_buffers *buffers, struct main_data *data, struct semaphores *sems) {
    for (int i = 0; i < data->n_clients ; ++i) {
        data->client_pids[i] = launch_process(i,0,buffers,data,sems);
    }
    for (int i = 0; i < data->n_proxies ; ++i) {
        data->proxy_pids[i] = launch_process(i,1,buffers,data,sems);

    }
    for (int i = 0; i < data->n_servers ; ++i) {
        data->server_pids[i] = launch_process(i,2,buffers,data,sems);
    }
}

/* Função que faz interação do utilizador com o sistema, podendo receber 4 comandos:
* op - cria uma nova operação, através da função create_request
* read - verifica o estado de uma operação através da função read_answer
* stop - termina o execução do sovaccines através da função stop_execution
* help - imprime informação sobre os comandos disponiveis
*/
void user_interaction(struct communication_buffers *buffers, struct main_data *data, struct semaphores *sems) {
    //mudar com ifa dependendo do tamanho dos int;
    char msg[4];


    printf("Ações disponíveis: \n");
    printf("        op - criar um pedido de aquisição de vacinas.\n");
    printf("        read x - consultar o estado do pedido x.\n");
    printf("        stop - termina a execução do sovaccines.\n");
    printf("        help - imprime informação sobre as ações disponíveis.\n");

    while (true) { // == 0 ???


        printf("Introduzir ação:\n");
        scanf("%s", msg);

        if (strcmp(msg, "op") == 0) {
            create_request(data->client_stats, buffers, data, sems);
        } else if (strcmp(msg, "read") == 0) {
            read_answer(data, sems);
        } else if (strcmp(msg, "stop") == 0) {
            stop_execution(data, buffers, sems);
            break;
        } else if (strcmp(msg, "help") == 0) {
            printf("Ações disponíveis: \n");
            printf("        op - criar um pedido de aquisição de vacinas.\n");
            printf("        read x - consultar o estado do pedido x.\n");
            printf("        stop - termina a execução do sovaccines.\n");
            printf("        help - imprime informação sobre as ações disponíveis.\n");
        } else {
            printf("Ação não reconhecida, insira 'help' para assistência.\n");
        }
    }
}

/* Se o limite de operações ainda não tiver sido atingido, cria uma nova
* operação identificada pelo valor atual de op_counter, escrevendo a mesma
* no buffer de memória partilhada entre main e clientes e efetuando a
* necessária sincronização antes e depois de escrever. Imprime o id da
* operação e incrementa o contador de operações op_counter.
*/
void create_request(int *op_counter, struct communication_buffers *buffers, struct main_data *data,
                    struct semaphores *sems) {

    if (*op_counter < data->max_ops) {
        struct operation op = {*op_counter, ' ', 0, 0, 0};

        produce_begin(sems->main_cli);
        write_rnd_access_buffer(buffers->main_cli, data->buffers_size, &op);
        produce_end(sems->main_cli);

        printf("O pedido #%d foi criado!\n"
               "Pedido #%d concluído! É agora possível consultar!\n", *data->client_stats,*data->client_stats);

        *op_counter = *op_counter + 1;
    }else{

        printf("O número máximo de pedidos foi alcançado!\n");
    }

}

struct operation getOperation (int id,int size,struct operation *results){

}


int isDigit(int length, char num[]) {
    int count;
    for (int i = 0; i < length; i++) {
        count += (isdigit(num[i]) != 0) ? 1 : 0;
    }

    return count;

}
/* Função que lê um id de operação do utilizador e verifica se a mesma
* é valida e se já foi respondida por um servidor. Em caso afirmativo,
* imprime informação da mesma, nomeadamente o seu estado, e os ids do
* cliente, proxy e servidor que a processaram. O acesso à estrutura
* data->results deve ser sincronizado com as funções e semáforos
* respetivos.
*/
void read_answer(struct main_data *data, struct semaphores *sems) {
// #define SIZE  (floor(log10(abs(data->max_ops))) + 1)

    char msg[data->max_ops];
    int number;

    scanf("%s", msg);
    if (isDigit(sizeof(msg) / sizeof(char), msg)) {
        number = atoi(msg);

        if(number > data->max_ops){
            printf("id de operação fornecido é inválido!\n");
            return;
        }


        semaphore_mutex_lock(sems->results_mutex);
        struct operation operation = {-1,' ',-1,-1,-1};

        for (int i = 0; i <data->max_ops ; i++) {
            if(data->results[i].id == number){
                operation = data->results[i];
                break;
            }
        }
        semaphore_mutex_unlock(sems->results_mutex);


        if(operation.id == -1){
            printf("Op %d ainda não é válido!\n", number);
        }else{

        printf("Op %d com estado %c foi recebida pelo cliente %d, encaminhada pelo proxy %d, ""e tratada pelo servidor %d!\n",
               operation.id,operation.status,operation.client,operation.proxy,operation.server);
        }

    } else {
            printf("id de operação fornecido é inválido!\n");
    }
}


/* Função que termina a execução do programa sovaccines. Deve começar por
* afetar a flag data->terminate com o valor 1. De seguida, e por esta
* ordem, deve acordar processos adormecidos, esperar que terminem a sua
* execução, escrever as estatisticas finais do programa, e por fim libertar
* os semáforos e zonas de memória partilhada e dinâmica previamente
*reservadas. Para tal, pode usar as outras funções auxiliares do main.h.
*/
void stop_execution(struct main_data *data, struct communication_buffers *buffers, struct semaphores *sems) {
    *data->terminate = 1;
    wakeup_processes(data, sems);
    wait_processes(data);
    write_statistics(data);
    destroy_semaphores(sems);
    destroy_shared_memory_buffers(data,buffers);
    destroy_dynamic_memory_buffers(data);
}

/* Função que acorda todos os processos adormecidos em semáforos, para que
* estes percebam que foi dada ordem de terminação do programa. Para tal,
* pode ser usada a função produce_end sobre todos os conjuntos de semáforos
* onde possam estar processos adormecidos e um número de vezes igual ao 
* máximo de processos que possam lá estar.
*/
void wakeup_processes(struct main_data *data, struct semaphores *sems) {
    // se o VALOR DO sems.mutex for maior que 0 então é pq tem processos ainda por ler.
    //mutex pergunta se agluem esta a aceder
    int *value;

    //main_cli
    sem_getvalue(sems->main_cli->mutex,value);
    while (*value > 0){
        consume_end(sems->main_cli);
        sem_getvalue(sems->main_cli->mutex,value);
    }
    //cli_prx
    sem_getvalue(sems->cli_prx->mutex,value);
    while (*value > 0){
        consume_end(sems->cli_prx);
        sem_getvalue(sems->cli_prx->mutex,value);
    }
    //prx_srv
    sem_getvalue(sems->prx_srv->mutex,value);
    while (*value > 0){
        consume_end(sems->prx_srv);
        sem_getvalue(sems->prx_srv->mutex,value);
    }
    //srv_cli
    sem_getvalue(sems->srv_cli->mutex,value);
    while (*value > 0){
        consume_end(sems->srv_cli);
        sem_getvalue(sems->srv_cli->mutex,value);
    }
}

/* Função que espera que todos os processos previamente iniciados terminem,
* incluindo clientes, proxies e servidores. Para tal, pode usar a função 
* wait_process do process.h.
*/
void wait_processes(struct main_data *data) {
    wait_process(*data->client_pids);
    wait_process(*data->proxy_pids);
    wait_process(*data->server_pids);
}


/* Função que imprime as estatisticas finais do sovaccines, nomeadamente quantas
* operações foram processadas por cada cliente, proxy e servidor.
*/
void write_statistics(struct main_data *data) {
    int process_id;

    for (size_t i = 0; i < data-> n_clients; i++){
        process_id = *(data->client_pids + i);
        printf("o cliente %d tratou de  %d processo", process_id , (data->client_stats[process_id]));
    }

    for (size_t i = 0; i < data-> n_proxies; i++)
    {
        process_id = *(data->proxy_pids + i);
        printf("o cliente %d tratou de  %d processo", process_id , (data->proxy_stats[process_id]));

    }

    for (size_t i = 0; i < data-> n_servers; i++){
        process_id = *(data->server_pids + i);
        printf("o cliente %d tratou de  %d processo", process_id , (data->server_stats[process_id]));
    }
}

/* Função que liberta todos os buffers de memória dinâmica previamente
* reservados na estrutura data.
*/
void destroy_dynamic_memory_buffers(struct main_data *data) {
    destroy_dynamic_memory(data->client_pids);
    destroy_dynamic_memory(data->proxy_pids);
    destroy_dynamic_memory(data->server_pids);
}


/* Função que liberta todos os buffers de memória partilhada previamente
* reservados nas estruturas data e buffers.
*/
void destroy_shared_memory_buffers(struct main_data *data, struct communication_buffers *buffers) {

    destroy_shared_memory(STR_SHM_MAIN_CLI_BUFFER, buffers->main_cli, data->buffers_size);

    destroy_shared_memory(STR_SHM_CLI_PRX_BUFFER, buffers->cli_prx, data->buffers_size);

    destroy_shared_memory(STR_SHM_PRX_SRV_BUFFER, buffers->prx_srv, data->buffers_size);

    destroy_shared_memory(STR_SHM_SRV_CLI_BUFFER, buffers->srv_cli, data->buffers_size);

}

/* Função que liberta todos os semáforos da estrutura semaphores.
*/
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

