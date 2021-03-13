#ifndef MEMORY_PRIVATE_H_GUARD
#define MEMORY_PRIVATE_H_GUARD

// ver buffer size
// ver objetos (item)
//nao sei se esta certo, provavelmente nao

//estrutura que representa um buffer circular, completar pelos alunos
struct circular_buffer { 	
   // int size; //nao sei se é isto
    struct operation* buff[]; //nao sei se é isto
    int in 0;
    int out 0;
};

//estrutura que representa um buffer de acesso aleatório, completar pelos alunos
struct rnd_access_buffer { 		
   // int size;  //nao sei se é isto
    
    struct operation* buff[]; //nao sei se é isto
    int ptr[];

};



#endif
