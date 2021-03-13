/* Função que liberta uma zona de memória partilhada previamente reservada.
*/
void destroy_dynamic_memory(void* ptr){
    free(ptr);
}

