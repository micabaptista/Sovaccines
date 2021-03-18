#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

//main.h
/* Função que faz interação do utilizador com o sistema, podendo receber 4 comandos:
* op - cria uma nova operação, através da função create_request
* read - verifica o estado de uma operação através da função read_answer
* stop - termina o execução do sovaccines através da função stop_execution
* help - imprime informação sobre os comandos disponiveis
*/
void user_interaction(struct communication_buffers* buffers, struct main_data* data, struct semaphores* sems) {
    ;
    
    


    //mudar com ifa dependendo do tamanho dos int;
    char msg[4];
    
    int numbers;
    
    
    printf("Ações disponíveis: \n");
    printf("        op - criar um pedido de aquisição de vacinas.\n");
    printf("        read x - consultar o estado do pedido x.\n");       
    printf("        stop - termina a execução do sovaccines.\n");
    printf("        help - imprime informação sobre as ações disponíveis.\n") ;
   
    while (strcmp(msg,"stop") == 0){

       
    printf(" Introduzir ação:\n");
    scanf("%s", &msg);

    
    if (strcmp(msg,"op") == 0  // && falta ver)
    { 
        create_request( /*nao sei o que por aqui*/, buffers, data,  sems);
    }
    else if (strcmp(msg,"read") == 0 )
    {
        
            read_answer(data, sems);
       
        
       
        
        
    } 
    else if (strcmp(msg,"stop") == 0)
    {
        stop_execution(data, buffers, sems);
    }

    else if (strcmp(msg,"help" == 0)){
        printf("Ações disponíveis: \n");
        printf("        op - criar um pedido de aquisição de vacinas.\n");
        printf("        read x - consultar o estado do pedido x.\n");       
        printf("        stop - termina a execução do sovaccines.\n");
        printf("        help - imprime informação sobre as ações disponíveis.\n") ;
    }
    else
    {
        printf("acçao nao reconhecida");
    }

    
    }
}

int isDigit( int length, char num[]){
    int count;
    for (int i = 0; i < length; i++)
    {
        count += (isdigit(num[i]) != 0) ? 0 : 1;
    }

    return count;
    
}

