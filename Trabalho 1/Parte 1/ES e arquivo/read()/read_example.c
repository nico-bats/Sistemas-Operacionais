#include <unistd.h>
#include <stdio.h>
 
/*
Este programa exemplifica a utilizacao da syscall "read" a qual le uma estrada especifica e salva o conteudo e um buffer fornecido 

*/

int main()
{
    char buffer[6]; //buffer
 
    if(read(0, buffer, 6) < 0){ //0 é a stdin

        printf("Erro ao ler o buffer\n");
    }

    int i;
    for(i=0;i<6;i++){
        printf("%c\n",buffer[i]);
    }
 
    return 0;
}