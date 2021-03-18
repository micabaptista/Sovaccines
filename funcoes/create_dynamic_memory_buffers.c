
/* Função que reserva a memória dinâmica necessária para a execução
* do sovaccines, nomeadamente para os arrays *_pids e *_stats da estrutura 
* main_data. Para tal, pode ser usada a função create_dynamic_memory do memory.h.
*/
void create_dynamic_memory_buffers(struct main_data* data){
    data->client_pids = create_dynamic_memory( data->n_clients * sizeof(int));
    data->proxy_pids = create_dynamic_memory( data->n_proxies * sizeof(int)); 
    data->server_pids = create_dynamic_memory( data->n_servers * sizeof(int));
    
    data->client_stats = create_dynamic_memory( data->max_ops * sizeof(int));
    data->proxy_stats = create_dynamic_memory( data->max_ops * sizeof(int)); 
    data->server_stats = create_dynamic_memory( data->max_ops * sizeof(int));
    
    
    
}


