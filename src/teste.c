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
    funcao1();
    printf("%d",a);
    return 0;
}
