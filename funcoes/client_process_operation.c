
/* Função que processa uma operação, alterando o seu campo cliente para o id
* passado como argumento, alterando o estado da mesma para 'C' (client), e 
* incrementando o contador de operações.
*/
void client_process_operation(struct operation* op, int cient_id, int* counter){
    op->id = cient_id;
    op->status = 'c';
    *counter ++; // ou counter ++; nao percebi
}

