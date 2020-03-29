#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
 /*
 Este programa exemplifica o uso da syscall "open" e "write" em linux, a qual abre um arquivo novo e recebe seu descritor e escreve o conteudo desejado na saida escolhida 

 */
int main()
{
    int filedesc = open("teste.txt", O_WRONLY | O_APPEND);

    if(filedesc < 0) return 1;
 
    if(write(filedesc,"Esta eh a saida de teste caso a syscall tenha sido chamada corretamente\n", 72) != 72){
        
        printf("Erro ao Escrever no arquivo\n");
        return 1;
    }
 
    return 0;
}