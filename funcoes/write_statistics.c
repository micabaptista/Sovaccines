/* Função que imprime as estatisticas finais do sovaccines, nomeadamente quantas
* operações foram processadas por cada cliente, proxy e servidor.
*/
void write_statistics(struct main_data* data){
     int process_id;
   
    for (size_t i = 0; i < data-> n_clients; i++)
    {
        process_id = *(data->client_pids + i);
        printf("o cliente /d tratou de  /d processo", process_id , *(data->client_stats[process_id]);

    }
    
    for (size_t i = 0; i < data-> n_proxies; i++)
    {
        process_id = *(data->proxy_pids + i);
        printf("o cliente /d tratou de  /d processo", process_id , *(data->proxy_stats[process_id]);
            
    }

    for (size_t i = 0; i < data-> n_servers; i++)
    {
        process_id = *(data->server_pids + i);
        printf("o cliente /d tratou de  /d processo", process_id , *(data->server_stats[process_id]);
            
    }
