/* Função que escreve uma operação no buffer de memória partilhada entre
* proxies e servidores, efetuando a necessária sincronização antes e
* depois de escrever.
*/
void proxy_forward_operation(struct operation* op, struct communication_buffers* buffers, struct main_data* data, struct semaphores* sems){

//SINC
    write_rnd_access_buffer(buffers->prx_srv, data->buffers_size, op);
//SINC
}




