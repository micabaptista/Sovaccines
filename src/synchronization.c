#include "../include/main.h"

#include <fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include <string.h>


sem_t *semaphore_create(char *name, int value) {
    uid_t id = getuid();
    char idValue [strlen(name) + sizeof id];
    sprintf(idValue, "%s%d", name, id);

    sem_t *sem = sem_open(idValue, O_CREAT, 0xFFFFFFFF, value);
    if (sem == SEM_FAILED) {
        perror("Não consegui criar o semaforo pretendido");
        return NULL;
    }
    return sem;
}


void semaphore_destroy(char *name, sem_t *semaphore) {
    if (sem_close(semaphore) == -1) {
        perror("sem_close");
    }
    uid_t id = getuid();
    char idValue [strlen(name) + sizeof id];
    sprintf(idValue, "%s%d", name, id);   // concatenar o id gerado com o nome passado por argumento.

    if (sem_unlink(idValue) == -1) {
        perror("unlink");
    }
}

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


void semaphore_mutex_lock(sem_t *sem) {
    if (sem_wait(sem) == -1) {
        perror("sem wait");
    }
}


void semaphore_mutex_unlock(sem_t *sem) {
    if (sem_post(sem) == -1) {
        perror("sem post");
    }
}
