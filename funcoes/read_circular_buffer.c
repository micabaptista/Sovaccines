/* Função que lê uma operação de um buffer circular, se houver alguma 
* disponível para ler. A leitura deve ser feita segundo as regras de
* leitura em buffers circular. Se não houver nenhuma operação disponível,
* afeta op->id com o valor -1.
*/
void read_circular_buffer(struct circular_buffer* buffer, int buffer_size, struct operation* op){
    while (buffer-> in == buffer -> out)
    {
        
    }
    op = buffer->buff[buffer->out];
    buffer->out = (buffer->out + 1) & buffer_size;    
}
