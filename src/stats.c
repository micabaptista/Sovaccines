#include "../include/stats.h"


void write_statistics(struct main_data *data, char * name){
    FILE * fp = fopen(name, "w");
    char * text = "";
    struct operation op;
    int counter = data->client_stats;
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
    for (int i = 0; i < data->client_stats; i++)
    {
        //ver sinc
        op = data->results[i];
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

        sprintf(text, "Created: %s\n", FormataTempo(op.start_time));
        fputs(text,fp);

        sprintf(text, "Client_time: %s\n", FormataTempo(op.client_time));
        fputs(text,fp);

        sprintf(text, "Proxy_time: %s\n", FormataTempo(op.proxy_time));
        fputs(text,fp);

        sprintf(text, "Server_time: %s\n", FormataTempo(op.server_time));
        fputs(text,fp);

        sprintf(text, "Ended: %s\n", FormataTempo(op.end_time));
        fputs(text,fp);

        dif = ( op.end_time.tv_sec - op.start_time.tv_sec ) + ( op.end_time.tv_nsec - op.start_time.tv_nsec ) / 1000000000L;

         sprintf(text, "Ended: %f\n",dif);

    }
    

    fclose(fp);
}