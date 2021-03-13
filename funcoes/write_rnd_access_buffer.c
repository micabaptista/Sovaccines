/* Função que escreve uma operação num buffer de acesso aleatório. A
* operação deve ser escrita numa posição livre do buffer, segundo as
* regras de escrita em buffers de acesso aleatório. Se não houver nenhuma
* posição livre, não escreve nada.
*/
void write_rnd_access_buffer(struct rnd_access_buffer* buffer, int buffer_size, struct operation* op){
    for (int i = 0; i < buffer_size; i++)
    {
            //mudar buffer -> * caso mude o memory.private
       if( buffer->ptr[i] == 0) {
           buffer->buff[i] = op;
           buffer->ptr[i] = 1;
           break;
       }

    }
    
}
