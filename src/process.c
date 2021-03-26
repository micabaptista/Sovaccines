#include "../include/main.h"
#include "../include/client.h"
#include "../include/process.h"
#include "../include/proxy.h"
#include "../include/server.h"
#include <unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include <sys/wait.h>

//SO-036
// Michael Baptista, 54478
// Afonso Rosa, 54395
// Duarte Pinheiro, 54475

int launch_process(int process_id, int process_code, struct communication_buffers *buffers, struct main_data *data,
                   struct semaphores *sems) {

    int pid ;
    int value;
    if ((pid = fork()) == -1) {
        perror("fork-launcher");
        exit(1);
    }
    if (pid == 0) { //fork funcionou e este processo é o filho
        /* Processo filho */
        if (process_code == 0) {
            value = execute_client(process_id, buffers, data, sems);
            exit(value);
        } else if (process_code == 1) {
            value = execute_proxy( process_id, buffers, data, sems);
            exit(value);
        } else if (process_code == 2) {
            value = execute_server( process_id, buffers, data, sems);
            exit(value);
        }
    } else {
        return pid;
    }
}


int wait_process(int process_id) {
    int status;
    waitpid(process_id, &status,0);

    if (!WIFEXITED(status)) {
        perror("wait-process-launhcer");
        exit(1);
    }
    return WEXITSTATUS(status);
}
