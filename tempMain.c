#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>

struct main_data {
    int max_ops;		//número máximo de operações
    int buffers_size;	//tamanho máximo dos buffers de mem. partilhada

    int n_clients;		//número de clientes
    int n_proxies;		//número de proxies
    int n_servers;		//número de servidores

    int *client_pids;	//process ids de clientes
    int *proxy_pids;	//process ids de proxies
    int *server_pids;	//process ids de servidores

    int* client_stats;	//nº de operações recebidas por cada cliente
    int* proxy_stats;	//nº de operações encaminhadas por cada proxy
    int* server_stats;	//nº de operações respondidas por cada servidor

    struct operation* results;	//array com histórico de ops executadas

    int* terminate; //flag booleana, valor 1 indica que sovaccines deve terminar a sua execução
};

struct operation {
    int id; 		//id da operação
    char status;	//estado da operação. Pode ser 'C', 'P', 'S'
    int client;		//id do cliente que a recebeu
    int proxy; 		//id do proxy que a encaminhou
    int server;		//id do server que a serviu
};


//estrutura que agrega os shared memory buffers necessários para comunicação entre processos
struct communication_buffers {
    struct rnd_access_buffer* main_cli; //buffer para main fazer pedidos a clientes
    struct circular_buffer* cli_prx;	//buffer para clientes enviarem pedidos a proxies
    struct rnd_access_buffer* prx_srv;  //buffer para proxies encaminharem pedidos a servidores
    struct circular_buffer* srv_cli;	//buffer para servidores responderem a pedidos de clientes
};

struct circular_buffer {
    struct operation *buffer;
    int in; // apontador de escrita
    int out; // apontador de leitura
};

//estrutura que representa um buffer de acesso aleatório, completar pelos alunos
struct rnd_access_buffer {
    struct operation *buffer;
    int *ptr;
};



void write_rnd_access_buffer(struct rnd_access_buffer *buffer, int buffer_size, struct operation *op) {
    int n;
    for (n = 0; n < buffer_size; n++) {
        if (buffer->ptr[n] == 0) {
            buffer->buffer[n] = *op;
            buffer->ptr[n] = 1;
            break;
        }
    }
}

void read_rnd_access_buffer(struct rnd_access_buffer *buffer, int buffer_size, struct operation *op) {
    int n;
    for (n = 0; n < buffer_size; n++) {
        if (buffer->ptr[n] == 1) {
            *op = buffer->buffer[n];
            buffer->ptr[n] = 0;
            return;
        }
    }
    op->id = -1;
}


void *create_shared_memory(char *name, int size) {
    uid_t id = getuid();
    // sempre que altero a variavel (a) ja consigo criar um pedido no entanto como o semaforo nao fecha
    // não consigo depois voltar a usar o memso e tenho de alterar o valor do int
    int a = 10; // apagar no fim do projeto
    char idValue [strlen(name) + sizeof id]; // declarar uma string do msm tamanho do name
    sprintf(idValue, "%s%d%d", name, id,a);   // concatenar o id gerado com o nome passado por argumento.

    int *ptr;
    int ret;
    int fd = shm_open(idValue, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("shm");
        exit(1);
    }

    ret = ftruncate(fd, size);
    if (ret == -1) {
        perror("shm");
        exit(2);
    }
    ptr = mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED) {
        perror("shm-mmap");
        exit(3);
    }
    for (int i = 0; i <size ; ++i) {
        ptr[i] = 0;
    }
    return ptr;
}
void *create_dynamic_memory(int size) {
    void *ptr = malloc(size);
    return memset(ptr, 0, size);
}

int main(int argc, char *argv[]) {


    struct main_data* data = create_dynamic_memory(sizeof(struct
            main_data));
    struct communication_buffers* buffers =
            create_dynamic_memory(sizeof(struct communication_buffers));

    buffers->main_cli = create_dynamic_memory(sizeof(struct
            rnd_access_buffer));

    buffers->main_cli->ptr = create_shared_memory("ptr", 10);

    buffers->main_cli->buffer = create_shared_memory("buffer", 10);


    struct operation a1 = {0,'B',0,1,0};

    write_rnd_access_buffer(buffers->main_cli, data->buffers_size, &a1);

    sleep(1);
    struct operation a2;

    read_rnd_access_buffer(buffers->main_cli, sizeof(buffers->main_cli), &a2);

    printf("%d",a2.proxy);


    return 0;
}