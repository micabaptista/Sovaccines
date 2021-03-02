#ifndef SYNCHRONIZATION_H_GUARD
#define SYNCHRONIZATION_H_GUARD

#include <semaphore.h>
	
// Nomes usados na criacao dos semaforos
#define STR_SEM_MAIN_CLI_FULL 	"sem_main_cli_full"
#define STR_SEM_MAIN_CLI_EMPTY 	"sem_main_cli_empty"
#define STR_SEM_MAIN_CLI_MUTEX 	"sem_main_cli_mutex"
#define STR_SEM_CLI_PRX_FULL 	"sem_cli_prx_full"
#define STR_SEM_CLI_PRX_EMPTY 	"sem_cli_prx_empty"
#define STR_SEM_CLI_PRX_MUTEX 	"sem_cli_prx_mutex"
#define STR_SEM_PRX_SRV_FULL	"sem_prx_srv_full"
#define STR_SEM_PRX_SRV_EMPTY 	"sem_prx_srv_empty"
#define STR_SEM_PRX_SRV_MUTEX 	"sem_prx_srv_mutex"
#define STR_SEM_SRV_CLI_FULL	"sem_srv_cli_full"
#define STR_SEM_SRV_CLI_EMPTY 	"sem_srv_cli_empty"
#define STR_SEM_SRV_CLI_MUTEX 	"sem_srv_cli_mutex"
#define STR_SEM_RESULTS_MUTEX	"sem_results_mutex"

//estrutura de 3 semáforos utilizada no modelo produtor/consumidor
struct prodcons {
	sem_t *full, *empty, *mutex;
};

//estrutura que agrega informação de todos os semáforos necessários pelo socps
struct semaphores {
	struct prodcons *main_cli;	// semáforos para acesso ao buffer entre a main e clientes
	struct prodcons *cli_prx; 	// semáforos para acesso ao buffer entre clientes e proxies
	struct prodcons *prx_srv; 	// semáforos para acesso ao buffer entre proxies e servidores
	struct prodcons *srv_cli;	// semáforos para acesso ao buffer entre servidores e clientes
	sem_t *results_mutex;		// semáforo para exclusão mútua no acesso ao array de resultados
};


/* Função que cria um novo semáforo com nome name e valor inicial igual a
* value. Pode concatenar o resultado da função getuid() a name, para tornar
* o nome único para o processo.
*/
sem_t * semaphore_create(char* name, int value);

/* Função que destroi o semáforo passado em argumento.
*/
void semaphore_destroy(char* name, sem_t* semaphore);

/* Função que inicia o processo de produzir, fazendo sem_wait nos semáforos
* corretos da estrutura passada em argumento.
*/
void produce_begin(struct prodcons* pc);

/* Função que termina o processo de produzir, fazendo sem_post nos semáforos
* corretos da estrutura passada em argumento.
*/
void produce_end(struct prodcons* pc);

/* Função que inicia o processo de consumir, fazendo sem_wait nos semáforos
* corretos da estrutura passada em argumento.
*/
void consume_begin(struct prodcons* pc);

/* Função que termina o processo de consumir, fazendo sem_post nos semáforos
* corretos da estrutura passada em argumento.
*/
void consume_end(struct prodcons* pc);

/* Função que faz wait a um semáforo.
*/
void semaphore_mutex_lock(sem_t* sem);

/* Função que faz post a um semáforo.
*/
void semaphore_mutex_unlock(sem_t* sem);

#endif
