/* Função principal de um Proxy. Deve executar um ciclo infinito onde em 
* cada iteração do ciclo lê uma operação dos clientes e se a mesma tiver id 
* diferente de -1 e se data->terminate ainda for igual a 0, processa-a e
* escreve-a para os servidores. Operações com id igual a -1 são ignoradas
* (op inválida) e se data->terminate for igual a 1 é porque foi dada ordem
* de terminação do programa, portanto deve-se fazer return do número de 
* operações processadas. Para efetuar estes passos, pode usar os outros
* métodos auxiliares definidos em proxy.h.
*/
int execute_proxy(int proxy_id, struct communication_buffers* buffers, struct main_data* data, struct semaphores* sems){
    //nao sei se esta certo
  
  
    struct operation* op;
    int *counter =0;  //ver counter
     while ( data->terminate != 1)
    {
        void proxy_receive_operation( op,  buffers, data, sems);

        if(op->id != -1 && data->terminate == 0){                                                                                                                                                                                                                                                                                                                                                                                                                                                             
            proxy_process_operation(op, int proxy_id, counter);

            proxy_forward_operation(op, buffers, data, sems);


        }
        

        //op == a -1 invalida ver se é preciso print

    }
    return *counter;
}




