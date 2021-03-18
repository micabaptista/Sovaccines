



/* Função que processa uma operação, alterando o seu campo proxy para o id
* passado como argumento, alterando o estado da mesma para 'P' (proxied), e 
* incrementando o contador de operações.
*/
void proxy_process_operation(struct operation* op, int server_id, int* counter){
    op->id = server_id;
    op->status = 'P';
    *counter ++; // ou counter ++; nao percebi
}






