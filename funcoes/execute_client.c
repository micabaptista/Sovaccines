/* Função principal de um Cliente. Deve executar um ciclo infinito
* onde cada iteração do ciclo tem dois passos: primeiro, lê uma operação
* da main e se a mesma lida tiver id diferente de -1 e se data->terminate
* ainda for igual a 0, processa-a e escreve-a para os proxies; segundo,
* lê uma resposta dos servidores e se a mesma tiver id diferente de -1 e se
* data->terminate ainda for igual a 0, processa-a. Operações com id igual a
* -1 são ignoradas (op inválida) e se data->terminate for igual a 1 é porque
* foi dada ordem de terminação do programa, portanto deve-se fazer return do
* o número de operações processadas. Para efetuar estes passos, pode usar os
* outros métodos auxiliares definidos em client.h. 
*/
int execute_client(int client_id, struct communication_buffers* buffers, struct main_data* data, struct semaphores* sems){
    //nao sei se esta certo
  
  
    struct operation* op;
    int *counter =0;
    while ( data->terminate != 1)
    {
        client_get_operation(op, buffers, data, sems);
        if(op->id != -1 && data->terminate == 0){
            client_process_operation( op, client_id, counter); //nao sei o que é o counter ou de onde vem 
            client_send_operation( op,  buffers,  data, sems);

        }
    
        client_receive_answer( op, buffers, data, sems);
        if(op->id != -1 && data->terminate == 0){
            client_process_answer( op,  data,  sems);     
        }


        //op == a -1 invalida ver se é preciso print

    }
    return *counter;
}
