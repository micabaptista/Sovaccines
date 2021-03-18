/* Se o limite de operações ainda não tiver sido atingido, cria uma nova
* operação identificada pelo valor atual de op_counter, escrevendo a mesma
* no buffer de memória partilhada entre main e clientes e efetuando a 
* necessária sincronização antes e depois de escrever. Imprime o id da
* operação e incrementa o contador de operações op_counter.
*/
void create_request(int* op_counter, struct communication_buffers* buffers, struct main_data* data, struct semaphores* sems){
    if (op_counter < data -> max_ops)
    {
        struct operation op = {op_counter, '', 0,0,0};
        
        //si*nc
        void write_rnd_access_buffer(buffers->main_cli, data->buffers_size, op);

        //sinc
        print("%d", op_counter);

        *op_counter++;   

    }
    
}

