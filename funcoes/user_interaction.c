#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
/* Função que faz interação do utilizador com o sistema, podendo receber 4 comandos:
* op - cria uma nova operação, através da função create_request
* read - verifica o estado de uma operação através da função read_answer
* stop - termina o execução do sovaccines através da função stop_execution
* help - imprime informação sobre os comandos disponiveis
*/
void user_interaction(struct communication_buffers* buffers, struct main_data* data, struct semaphores* sems) {
    ;
    
    #define SIZE  ( floor(log10(abs(data->max_ops))) + 1)


    //FALTA LOOP 
    char msg[ 5 + SIZE];
    char word[5];
    char num [SIZE];
    int numbers;
    
    printf("Ações disponíveis: \n");
    printf("        op - criar um pedido de aquisição de vacinas.\n");
    printf("        read x - consultar o estado do pedido x.\n");       
    printf("        stop - termina a execução do sovaccines.\n");
    printf("        help - imprime informação sobre as ações disponíveis.\n")    
    printf(" Introduzir ação:\n")    
    
    fgets(msg, SIZE, stdin);
    strncpy(word, msg, 3);
    
    if (strcmp(word,"op ") == 0)
    { 
        create_request( /*nao sei o que por aqui*/, buffers, data,  sems);
    }

    strncpy(word, msg, 5);
    strncpy(num, msg + 5, SIZE);

    if (strcmp(word,"read ") == 0 )
    {
        
        //alterar devido ao tamanho de msg, que vai ser diferente
        if ( isdigit(sizeof(word)/sizeof(char), word)) {
            //falta verificar se o numero é um processo corrente 
             
            numbers = atoi(word);
            read_answer(data, sems);
        }else
        {
            printf("erro nao é numero")
        }
        //falta erro açao nao reconhecida
        
    }
    strncpy(word, msg, 4);

    if (strcmp(word,"stop") == 0)
    {
        stop_execution(data, buffers, sems);
    }
    else if (strcmp(word,"help" != 0))
    {
        printf("acçao nao reconhecida");
    }

    
}


int isDigit( int length, char num[]){
    int count;
    for (int i = 0; i < length; i++)
    {
        count += (isdigit(num[i]) != 0 || num[i] == NULL) ? 0 : 1;
    }

    return count;
    
}

