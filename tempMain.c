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


struct operation {
    int id;        //id da operação
    char status;    //estado da operação. Pode ser 'C', 'P', 'S'
    int client;        //id do cliente que a recebeu
    int proxy;        //id do proxy que a encaminhou
    int server;        //id do server que a serviu
    int array [2];

};

void write_rnd_access_buffer(struct operation *buffer, int buffer_size, struct operation *op) {
    int n;
    for (n = 0; n < buffer_size; n++) {
        if (buffer->array[n] == 0) {

            buffer->array[n] = op;
            buffer->array[n] = 1;
            break;
        }
    }
}

void client_get_operation(struct operation *sems) {
    sems->array[0];
    sems->client=2;
    printf("%d",sems->client);
}


int main(int argc, char *argv[]) {
    struct operation operation;
    client_get_operation(&operation);
    operation.array[0];
    return 0;
}