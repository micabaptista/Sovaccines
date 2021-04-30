

#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <stdlib.h>

#include <unistd.h>

#include "../include/main.h"
#include "../include/memory.h"
#include "../include/log.h"

struct main_data* data_global ;
struct communication_buffers *buffers_global;
struct semaphores* sems_global;
FILE * log_global;


void write_status(){

  struct operation op;
    if (*data_global->terminate != -1)
    {
      for (int i = 0; i < data_global->max_ops; i++)
      {

        if (i < *data_global->client_stats /*nao sei se esta certo*/)
        {
          semaphore_mutex_lock(sems_global->results_mutex);
          op = data_global->results[i];
          semaphore_mutex_unlock(sems_global->results_mutex);
          
          if (op.status == 'C'|| op.status == 'P'|| op.status == 'S' )
          {
            printf("op:%d status:%c start:%ld ", op.id, op.status, op.start_time.tv_sec);
            printf("client:%d client_time:%ld ", op.client, op.client_time.tv_sec);
            printf("proxy:%d proxy_time:%ld ", op.proxy, op.proxy_time.tv_sec);
            printf("server:%d server_time:%ld end:%ld \n", op.server, op.server_time.tv_sec, op.end_time.tv_sec);
          }else { 

            printf("op:%d status:0 start:%ld \n", i, op.start_time.tv_sec);
          }
        }
        else
        {
          printf("op:%d status:0\n", i);
        }
      }
      signal(SIGALRM, write_status);
    }
    else
    {
      exit(0);
    }        
};



/*
* Funçao que marca o tempo atual.
* Retorna -1 em caso de erro.
*/
void acionaAlarme( struct main_data* data, struct semaphores *sems){
    struct itimerval val;
    data_global = data;
    sems_global = sems;
    
    setbuf(stdout, NULL); //nap sei se é para usar
    signal(SIGALRM, write_status);
    val.it_interval.tv_sec = data->alarm_time;
    val.it_interval.tv_usec = 0;
    val.it_value.tv_sec = data->alarm_time;
    val.it_value.tv_usec = 0;
    setitimer(ITIMER_REAL, &val , 0);
    

}
 
/**/

void ctrlC(){
    stop_execution(data_global, buffers_global, sems_global,log_global);
    exit(0);
}


void capturaSinal( struct communication_buffers* buffers, struct semaphores* sems, FILE * log ){
  buffers_global = buffers;
  sems_global = sems;
  log_global = log;
  struct sigaction sa;
  sigemptyset(&sa.sa_mask);
  sa.sa_handler = ctrlC;
  sa.sa_flags= SA_RESTART;

  if (sigaction(SIGINT, &sa, NULL) == -1) {
    perror("main:");
    exit(-1);
  }
  
}







    


