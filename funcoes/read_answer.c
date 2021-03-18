
/* Função que lê um id de operação do utilizador e verifica se a mesma
* é valida e se já foi respondida por um servidor. Em caso afirmativo,
* imprime informação da mesma, nomeadamente o seu estado, e os ids do 
* cliente, proxy e servidor que a processaram. O acesso à estrutura 
* data->results deve ser sincronizado com as funções e semáforos
* respetivos.
*/
void read_answer(struct main_data* data, struct semaphores* sems){
    #define SIZE  ( floor(log10(abs(data->max_ops))) + 1);

	char msg[SIZE];
	int number;
    scanf("%s", &msg);

        
        if ( isdiatoigit(sizeof(msg)/sizeof(char), msg)) {
            
            number = atoi(msg);
			//falta fazer
		}else{
			printf("not a number");
		}	
}

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
