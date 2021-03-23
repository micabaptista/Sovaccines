#ifndef MEMORY_H_GUARD
#define MEMORY_H_GUARD

#include "memory-private.h"

// Nomes usados na criação de zonas de memoria partilhada
#define STR_SHM_MAIN_CLI_PTR 			"SHM_MAIN_CLI_PTR"
#define STR_SHM_MAIN_CLI_BUFFER 		"SHM_MAIN_CLI_BUFFER"
#define STR_SHM_CLI_PRX_PTR 			"SHM_CLI_PRX_PTR"
#define STR_SHM_CLI_PRX_BUFFER 			"SHM_CLI_PRX_BUFFER"
#define STR_SHM_PRX_SRV_PTR 			"SHM_PRX_SRV_PTR"
#define STR_SHM_PRX_SRV_BUFFER 			"SHM_PRX_SRV_BUFFER"
#define STR_SHM_SRV_CLI_PTR 			"SHM_SRV_CLI_PTR"
#define STR_SHM_SRV_CLI_BUFFER			"SHM_SRV_CLI_BUFFER"
#define STR_SHM_RESULTS					"SHM_RESULTS"
#define STR_SHM_TERMINATE				"SHM_TERMINATE"


//Estrutura que representa uma operação (pedido/resposta)
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


/* Função que reserva uma zona de memória partilhada com tamanho indicado
* por size e nome name, preenche essa zona de memória com o valor 0, e 
* retorna um apontador para a mesma. Pode concatenar o resultado da função
* getuid() a name, para tornar o nome único para o processo.
*/
void* create_shared_memory(char* name, int size);


/* Função que reserva uma zona de memória dinâmica com tamanho indicado
* por size, preenche essa zona de memória com o valor 0, e retorna um 
* apontador para a mesma.
*/
void* create_dynamic_memory(int size);


/* Função que liberta uma zona de memória dinâmica previamente reservada.
*/
void destroy_shared_memory(char* name, void* ptr, int size);


/* Função que liberta uma zona de memória partilhada previamente reservada.
*/
void destroy_dynamic_memory(void* ptr);


/* Função que escreve uma operação num buffer de acesso aleatório. A
* operação deve ser escrita numa posição livre do buffer, segundo as
* regras de escrita em buffers de acesso aleatório. Se não houver nenhuma
* posição livre, não escreve nada.
*/
void write_rnd_access_buffer(struct rnd_access_buffer* buffer, int buffer_size, struct operation* op);


/* Função que escreve uma operação num buffer circular. A operação deve 
* ser escrita numa posição livre do buffer, segundo as regras de escrita
* em buffers circulares. Se não houver nenhuma posição livre, não escreve
* nada.
*/
void write_circular_buffer(struct circular_buffer* buffer, int buffer_size, struct operation* op);


/* Função que lê uma operação de um buffer de acesso aleatório, se houver
* alguma disponível para ler. A leitura deve ser feita segundo as regras
* de leitura em buffers acesso aleatório. Se não houver nenhuma operação
* disponível, afeta op com o valor -1.
*/
void read_rnd_access_buffer(struct rnd_access_buffer* buffer, int buffer_size, struct operation* op);


/* Função que lê uma operação de um buffer circular, se houver alguma 
* disponível para ler. A leitura deve ser feita segundo as regras de
* leitura em buffers circular. Se não houver nenhuma operação disponível,
* afeta op->id com o valor -1.
*/
void read_circular_buffer(struct circular_buffer* buffer, int buffer_size, struct operation* op);



#endif
