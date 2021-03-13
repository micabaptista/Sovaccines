

/* Função que lê uma operação do buffer de memória partilhada entre a 
* main e clientes, efetuando a necessária sincronização antes e depois
* de ler. Quando o processo acorda da sincronização, e antes de tentar ler
* a operação, deve verificar se data->terminate tem valor 1. Em caso 
* afirmativo, retorna imediatamente da função.
*/
void client_get_operation(struct operation* op, struct communication_buffers* buffers, struct main_data* data, struct semaphores* sems){

    //falta sinc
    if( data->terminate == 1){ //Quando o processo acorda da sincronização, e antes de tentar ler a operação, deve verificar se data->terminate tem valor 1. Em caso  afirmativo, retorna imediatamente da função.
                               // nao sei se é isto ou se esta no sitio certo
        return;
    }
    
    read_rnd_access_buffer( buffers->main_cli, data->buffers_size,  op );   //nao tenho a certeza
    //falta sinc

    
}
