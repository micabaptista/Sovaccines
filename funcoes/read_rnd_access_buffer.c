/* Função que lê uma operação de um buffer de acesso aleatório, se houver
* alguma disponível para ler. A leitura deve ser feita segundo as regras
* de leitura em buffers acesso aleatório. Se não houver nenhuma operação
* disponível, afeta op com o valor -1.
*/
void read_rnd_access_buffer(struct rnd_access_buffer* buffer, int buffer_size, struct operation* op){
    op = -1;
    for (int i = 0; i < buffer_size; i++)
    {
        if(buffer->ptr[i == 1]) {
            op = buffer->buff[i];
            buffer->ptr[i] = 0;
            break
        }
    }
    
   
}
