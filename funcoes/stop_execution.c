/* Função que termina a execução do programa sovaccines. Deve começar por 
* afetar a flag data->terminate com o valor 1. De seguida, e por esta
* ordem, deve acordar processos adormecidos, esperar que terminem a sua 
* execução, escrever as estatisticas finais do programa, e por fim libertar
* os semáforos e zonas de memória partilhada e dinâmica previamente 
*reservadas. Para tal, pode usar as outras funções auxiliares do main.h.
*/
void stop_execution(struct main_data* data, struct communication_buffers* buffers, struct semaphores* sems){
    data->terminate = 1;
    wakeup_processes(data, sems);
   // nao entendio a parte de esperar talvez um fork e wait
   //escrever estatisticas 
   //libertar semaforos e zonas de moria partilhada e dinamica


}



