#include "../include/stats.h"
#include "../include/sotime.h"


void write_stats(struct main_data *data, char * name, struct semaphores *sems){
    FILE * fp = fopen(name, "w");
    char text [100];
    struct operation op;
    
    double dif;
    fputs("Process Statistics:\n", fp);
    for (int i = 0; i < data->n_clients; ++i) {
        sprintf(text, "Cliente %d recebeu de %d processos!\n", i, (data->client_stats[i]));
        fputs(text, fp);
    }

    for (int i = 0; i < data->n_proxies; ++i) {
        sprintf(text, "Proxy %d encaminhou de %d processo!\n", i, (data->proxy_stats[i]));
        fputs(text, fp);
    }

    for (int i = 0; i < data->n_servers; ++i) {
        sprintf(text, "Server %d respondeu de %d processo!\n", i, (data->server_stats[i]));
        fputs(text, fp);
    }

    fputs("Operation Statistics:\n", fp);
    for (int i = 0; i < *data->client_stats; i++)
    {
        semaphore_mutex_lock(sems->results_mutex);
        op = data->results[i];
        semaphore_mutex_unlock(sems->results_mutex);
        //ver se funciona fputs + fputs
        sprintf(text, "OP: %d\n", op.id);
        fputs(text,fp);

        sprintf(text, "Status: %c\n", op.status);
        fputs(text,fp);

        sprintf(text, "Client_id: %d\n", op.client);
        fputs(text,fp);

        sprintf(text, "Proxy_id: %d\n", op.proxy);
        fputs(text,fp);

        sprintf(text, "Server_id: %d\n", op.server);
        fputs(text,fp);

        sprintf(text, "Created: %d\n", op.client);
        fputs(text,fp);

        char timeFormat [40 * sizeof (int)];

        formataTempo(&op.start_time,timeFormat);
        sprintf(text, "Created: %s\n", timeFormat);
        fputs(text,fp);

        formataTempo(&op.client_time,timeFormat);
        sprintf(text, "Client_time: %s\n", timeFormat);
        fputs(text,fp);

        formataTempo(&op.proxy_time,timeFormat);
        sprintf(text, "Proxy_time: %s\n", timeFormat);
        fputs(text,fp);

        formataTempo(&op.server_time,timeFormat);
        sprintf(text, "Server_time: %s\n", timeFormat);
        fputs(text,fp);

        formataTempo(&op.end_time,timeFormat);
        sprintf(text, "Ended: %s\n", timeFormat);
        fputs(text,fp);

        dif = ( op.end_time.tv_sec - op.start_time.tv_sec ) + ( op.end_time.tv_nsec - op.start_time.tv_nsec ) / 1000000000L;

         sprintf(text, "Ended: %f\n",dif);

    }
    

    fclose(fp);
}