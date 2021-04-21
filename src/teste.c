#include <stdio.h>

int a= 0 ; 


void funcao2() {
    a = 4;
}

void funcao1 (){
    a = 3;
    funcao2();
}



int main(int argc, char const *argv[])
{
    int i = -1;
    char * line;
    FILE *fp = fopen("teste1", "r");
    printf("ola")
    do
    {
        i++;
        line[i] = getc(fp);
    
    } while (line[i] != EOF || line[i] != '\n');
    
    if (line[0] != EOF)
    {
        printf("%c \n", line[0]);
    }
}
