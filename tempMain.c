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
};

struct operation getOperation (int id,struct operation *results){
    while ( results != NULL){
        if(results->id == id){
            return *results;
        }
        results++;
    }
}



int main(int argc, char *argv[]) {


    struct operation results [] = {
            {0,'S',0,0,0},
            {1,'K',1,1,1},
            {2,'S',2,2,2}
    };

    struct operation a = getOperation(1,results);
    printf("%c",a.status);
    // get operação que teve o id = number

    // percorrer data->results ( ou seja percorrer um array de strucsts e devolver aquela cujo id = number)
    return 0;
}