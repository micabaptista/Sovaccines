/* Função que reserva a memória partilhada necessária para a execução do
* sovaccines. É necessário reservar memória partilhada para todos os buffers da
* estrutura communication_buffers, incluindo os buffers em si e respetivos
* pointers, assim como para o array data->results e variável data->terminate.
* Para tal, pode ser usada a função create_shared_memory do memory.h.
*/
void create_shared_memory_buffers(struct main_data* data, struct communication_buffers* buffers){
    //acjo que falta um for para os buffers
    //FALTAFAZER
   buffers-> main_cli = create_shared_memory()
}
/*
void* create_shared_memory(char* name, int size){
#define STR_SHM_MAIN_CLI_PTR 			"SHM_MAIN_CLI_PTR"
#define STR_SHM_MAIN_CLI_BUFFER 		"SHM_MAIN_CLI_BUFFER"
#define STR_SHM_CLI_PRX_PTR 			"SHM_CLI_PRX_PTR" // ver o que e isto
#define STR_SHM_CLI_PRX_BUFFER 			"SHM_CLI_PRX_BUFFER"
#define STR_SHM_PRX_SRV_PTR 			"SHM_PRX_SRV_PTR"
#define STR_SHM_PRX_SRV_BUFFER 			"SHM_PRX_SRV_BUFFER"
#define STR_SHM_SRV_CLI_PTR 			"SHM_SRV_CLI_PTR"
#define STR_SHM_SRV_CLI_BUFFER			"SHM_SRV_CLI_BUFFER"
#define STR_SHM_RESULTS					"SHM_RESULTS"
#define STR_SHM_TERMINATE				"SHM_TERMINATE"

struct communication_buffers {
	struct rnd_access_buffer* main_cli; //buffer para main fazer pedidos a clientes
	struct circular_buffer* cli_prx;	//buffer para clientes enviarem pedidos a proxies
	struct rnd_access_buffer* prx_srv;  //buffer para proxies encaminharem pedidos a servidores
	struct circular_buffer* srv_cli;	//buffer para servidores responderem a pedidos de clientes
};

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