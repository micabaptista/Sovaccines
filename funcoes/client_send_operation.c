
/* Função que escreve uma operação no buffer de memória partilhada entre
* clientes e proxies, efetuando a necessária sincronização antes e depois
* de escrever.
*/
void client_send_operation(struct operation* op, struct communication_buffers* buffers, struct main_data* data, struct semaphores* sems){

    //sinc
    write_circular_buffer(buffers->cli_prx, data->buffers_size, op);
    //sinc

}
