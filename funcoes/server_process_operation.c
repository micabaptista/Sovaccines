/* Função que processa uma operação, alterando o seu campo server para o id
* passado como argumento, alterando o estado da mesma para 'S' (served), e 
* incrementando o contador de operações.
*/
void server_process_operation(struct operation* op, int proxy_id, int* counter){
    op->id = server_id;
    op->status = 'S';
    *counter ++; // ou counter ++; nao percebi
}
