#include "../include/main.h"

//SO-036
// Michael Baptista, 54478
// Afonso Rosa, 54395
// Duarte Pinheiro, 54475


int main(int argc, char *argv[]) {

//init data structures
    struct main_data * data = create_dynamic_memory(sizeof(struct main_data));
    struct communication_buffers* buffers = create_dynamic_memory(sizeof(struct communication_buffers));
    
    buffers->main_cli = create_dynamic_memory(sizeof(struct
            rnd_access_buffer));
    buffers->cli_prx = create_dynamic_memory(sizeof(struct
            circular_buffer));
    buffers->prx_srv = create_dynamic_memory(sizeof(struct
            rnd_access_buffer));
    buffers->srv_cli = create_dynamic_memory(sizeof(struct
            circular_buffer));
    struct semaphores* sems = create_dynamic_memory(sizeof(struct
            semaphores));
    sems->main_cli = create_dynamic_memory(sizeof(struct prodcons));
    sems->cli_prx = create_dynamic_memory(sizeof(struct prodcons));
    sems->prx_srv = create_dynamic_memory(sizeof(struct prodcons));
    sems->srv_cli = create_dynamic_memory(sizeof(struct prodcons));

//execute main code
    create_dynamic_memory_buffers(data);
    main_args(argc, argv, data); 
    create_shared_memory_buffers(data, buffers);
    create_semaphores(data, sems);
    launch_processes(buffers, data, sems);    
    user_interaction(buffers, data, sems);
//release final memory
    destroy_dynamic_memory(data);
    destroy_dynamic_memory(buffers->main_cli);
    destroy_dynamic_memory(buffers->cli_prx);
    destroy_dynamic_memory(buffers->prx_srv);
    destroy_dynamic_memory(buffers->srv_cli);
    destroy_dynamic_memory(buffers);
    destroy_dynamic_memory(sems->main_cli);
    destroy_dynamic_memory(sems->cli_prx);
    destroy_dynamic_memory(sems->prx_srv);
    destroy_dynamic_memory(sems->srv_cli);
    destroy_dynamic_memory(sems);
    return 0;
}

