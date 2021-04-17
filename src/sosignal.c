#ifndef SERVER_H_GUARD
#define SERVER_H_GUARD

#include <stdio.h>
#include <signal.h>
#include <sys/time.h>

#include <stdlib.h>

#include "main.h"
#include "memory.h"

struct main_data* data_global ;



/*
* Funçao que marca o tempo atual.
* Retorna -1 em caso de erro.
*/
void acionaAlarme( struct main_data* data ){

    struct itimerval val;
    data_global = data;
    
    setbuf(stdout, NULL); //nap sei se é para usar
    signal(SIGALRM, write_status);
     val.it_interval.tv_sec = data->alarm_time;
    val.it_interval.tv_usec = 0;
    val.it_value.tv_sec = data->alarm_time;
    val.it_value.tv_usec = 0;
    setitimer(ITIMER_REAL, &val , 0);
    for(;;);

}


/**/
void write_status(){
  struct operation* op;
    //falata acabar, duvida aqui
    if (data_global->terminate != -1)
    {
      for (int i = 0; i < data_global->max_ops; i++)
      {
        //ver se sincronizaçao
          if (data_global->results[i].id != -1 /*nao sei o que por aqui, vou por -1 por agora*/ )
          {
            *op = data_global->results[i];
            //acho que falta por os casos em que nao tem info
            printf("op:%d status:%c start:%d",op->id, op->status, op->start_time);
            printf("client:%d client_time:%c ",op->client, op->client_time);
            printf("proxy:%d proxy_time:%c ",op->proxy, op->proxy_time);
            printf("server:%d server_time:%c end:%d \n",op->server, op->server_time, op->end_time);  
              
          }else
          {
             printf("op:%d status:0", i);
          }
          
          
        
        
        signal(SIGALRM, write_status);
      }
    }else
    {
      exit(0);
    }        
};
    

    


#endif