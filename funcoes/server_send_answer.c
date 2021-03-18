/* Função que escreve uma operação no buffer de memória partilhada entre
* servidores e clientes, efetuando a necessária sincronização antes e
* depois de escrever.
*/
void server_send_answer(struct operation* op, struct communication_buffers* buffers, struct main_data* data, struct semaphores* sems){

//SINC
    write_circular_buffer(buffers->srv_cli, data->buffers_size, op);
//SINC
}

