#include "../include/main.h"
#include "../include/client.h"
#include "../include/memory.h"
#include "../include/memory-private.h"
#include "../include/process.h"
#include "../include/proxy.h"
#include "../include/server.h"
#include "../include/synchronization.h"

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include <string.h>

/* Função que cria um novo semáforo com nome name e valor inicial igual a
* value. Pode concatenar o resultado da função getuid() a name, para tornar
* o nome único para o processo.
*/
sem_t *semaphore_create(char *name, int value) {
    uid_t id = getuid();
    // sempre que altero a variavel (a) ja consigo criar um pedido no entanto como o semaforo nao fecha
    // não consigo depois voltar a usar o memso e tenho de alterar o valor do int
    int a = 10;
    char idValue [strlen(name) + sizeof id]; // declarar uma string do msm tamanho do name
    sprintf(idValue, "%s%d%d", name, id,a);   // concatenar o id gerado com o nome passado por argumento.

    sem_t *sem = sem_open(idValue, O_CREAT, 0xFFFFFFFF, value);
    if (sem == SEM_FAILED) {
        perror("Não consegui criar o semaforo pretendido");
        return NULL;
    }
    return sem;
}

/* Função que destroi o semáforo passado em argumento.
*/
void semaphore_destroy(char *name, sem_t *semaphore) {
    if (sem_close(semaphore) == -1) {
        perror(name);
    }
    if (sem_unlink(name) == -1) {
        perror(name);
    }
}

/* Função que inicia o processo de produzir, fazendo sem_wait nos semáforos
* corretos da estrutura passada em argumento.
*/
void produce_begin(struct prodcons *pc) {
    if(sem_wait(pc->empty) == -1){
        perror("sem wait");
        exit(1);
    }
    if(sem_wait(pc->mutex) == -1){
        perror("sem wait");
        exit(1);
    }
}

/* Função que termina o processo de produzir, fazendo sem_post nos semáforos
* corretos da estrutura passada em argumento.
*/
void produce_end( struct prodcons *pc) {
    if(sem_post(pc->mutex) == -1){
        perror("sem post");
        exit(1);
    }
    if(sem_post(pc->full) == -1){
        perror("sem post");
        exit(1);
    }
}

/* Função que inicia o processo de consumir, fazendo sem_wait nos semáforos
* corretos da estrutura passada em argumento.
*/
void consume_begin(struct prodcons *pc) {
    if(sem_wait(pc->full) == -1){
        perror("sem wait");
        return;
    }
    if(sem_wait(pc->mutex) == -1){
        perror("sem wait");
        return;
    }
}

/* Função que termina o processo de consumir, fazendo sem_post nos semáforos
* corretos da estrutura passada em argumento.
*/
void consume_end(struct prodcons *pc) {
    if(sem_post(pc->mutex) == -1){
        perror("sem post");
        return;
    }
    if(sem_post(pc->empty) == -1){
        perror("sem post");
        return;
    }
}

/* Função que faz wait a um semáforo.
*/
void semaphore_mutex_lock(sem_t *sem) {
    if (sem_wait(sem) == -1) {
        perror("sem wait");
    }
}

/* Função que faz post a um semáforo.
*/
void semaphore_mutex_unlock(sem_t *sem) {
    if (sem_post(sem) == -1) {
        perror("sem post");
    }
}
