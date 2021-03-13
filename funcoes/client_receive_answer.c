
/* Função que lê uma operação do buffer de memória partilhada entre 
* servidores e clientes, efetuando a necessária sincronização antes e
* depois de ler. Quando o processo acorda da sincronização, e antes de
* tentar ler a operação, deve verificar se data->terminate tem valor 1.
* Em caso afirmativo, retorna imediatamente da função.
*/
void client_receive_answer(struct operation* op, struct communication_buffers* buffers, struct main_data* data, struct semaphores* sems){
    
    //sinc
    if(data->terminate == 1){ //Quando o processo acorda da sincronização, e antes de tentar ler a operação, deve verificar se data->terminate tem valor 1. Em caso  afirmativo, retorna imediatamente da função.
                               // nao sei se é isto ou se esta no sitio certo

        return;
    }
    read_circular_buffer(buffers->srv_cli, data->buffer_size,op);
    //sinc
}

