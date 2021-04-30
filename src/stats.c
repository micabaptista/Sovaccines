#include "../include/stats.h"
#include "../include/sotime.h"


void write_stats(struct main_data *data, struct semaphores *sems){
    FILE * fp = fopen(data->statistics_filename, "w");
    char text [100];
    struct operation op;

    fputs("Process Statistics:\n", fp);
    for (int i = 0; i < data->n_clients; ++i) {
        sprintf(text, "Client %d received %d requests!\n", i, (data->client_stats[i]));
        fputs(text, fp);
    }

    for (int i = 0; i < data->n_proxies; ++i) {
        sprintf(text, "Proxy %d forwarded de %d requests!\n", i, (data->proxy_stats[i]));
        fputs(text, fp);
    }

    for (int i = 0; i < data->n_servers; ++i) {
        sprintf(text, "Server %d responded de %d requests!\n", i, (data->server_stats[i]));
        fputs(text, fp);
    }

    fputs("Operation Statistics:\n", fp);

    int temp1 = 0;
    for (int i = 0; i < data->n_clients ; ++i) {
        temp1 = temp1 + data->client_stats[i];
    }

    printf("%d",temp1);

    for (int i = 0; i < temp1; i++){
        semaphore_mutex_lock(sems->results_mutex);
        op = data->results[i];
        semaphore_mutex_unlock(sems->results_mutex);

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

        int sec = ( op.end_time.tv_sec - op.start_time.tv_sec );
        int msec = ( op.end_time.tv_nsec - op.start_time.tv_nsec ) / 1000000L;

        sprintf(text, "Total Time: %d.%d\n",abs(sec),abs(msec));
        fputs(text,fp);
    }

    fclose(fp);
}