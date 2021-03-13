/* Função que escreve uma operação num buffer circular. A operação deve 
* ser escrita numa posição livre do buffer, segundo as regras de escrita
* em buffers circulares. Se não houver nenhuma posição livre, não escreve
* nada.
*/
void write_circular_buffer(struct circular_buffer* buffer, int buffer_size, struct operation* op){
    
   
    while ((buffer-> in +1) % buffer_size == buffer-> out) {

    } 
    buffer->buff[in] = op;
    buffer->in = (buffer->in +1) % buffer_size;
}

