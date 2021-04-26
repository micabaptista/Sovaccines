#ifndef SERVER_H_GUARD
#define SERVER_H_GUARD

#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <stdlib.h>
#include "../include/main.h"
#include "../include/memory.h"

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
    if (*data_global->terminate != -1)
    {
      for (int i = 0; i < data_global->max_ops; i++)
      {

        if (i < *data_global->client_stats /*nao sei se esta certo*/)
        {
          //ver se sincronizaçao
          *op = data_global->results[i];

          if (op->status == 'C'|| op->status == 'P'|| op->status == 'S' )
          {
            printf("op:%d status:%c start:%ld", op->id, op->status, op->start_time.tv_sec);
            printf("client:%d client_time:%ld ", op->client, op->client_time.tv_sec);
            printf("proxy:%d proxy_time:%ld ", op->proxy, op->proxy_time.tv_sec);
            printf("server:%d server_time:%ld end:%ld \n", op->server, op->server_time.tv_sec, op->end_time.tv_sec);
          }else { 

            printf("op:%d status:0 start:%ld \n", i, op->start_time.tv_sec);
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
    

    


#endif