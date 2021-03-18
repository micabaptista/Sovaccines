/* Função que lê uma operação do buffer de memória partilhada entre
* proxies e servidores, efetuando a necessária sincronização antes e
* depois de ler. Quando o processo acorda da sincronização, e antes de
* tentar ler a operação, deve verificar se data->terminate tem valor 1.
* Em caso afirmativo, retorna imediatamente da função.
*/
void server_receive_operation(struct operation* op, struct communication_buffers* buffers, struct main_data* data, struct semaphores* sems){


   //falta sinc
    if( data->terminate == 1){ //Quando o processo acorda da sincronização, e antes de tentar ler a operação, deve verificar se data->terminate tem valor 1. Em caso  afirmativo, retorna imediatamente da função.
                               // nao sei se é isto ou se esta no sitio certo
        return;
    }
    
    read_rnd_access_buffer( buffers->cli_prx, data->buffers_size,  op);   //nao tenho a certeza
    //falta sinc

}
