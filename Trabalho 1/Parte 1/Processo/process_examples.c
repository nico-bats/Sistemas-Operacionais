#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    char nome1[40]; // Estas strings sao utilizadas para realizar entradas em diferentes processos
    char nome2[40];
    char nome3[40];
    pid_t pid;     // variavel utilizada determinar qual processo esta sendo utilizado

    int status;

    //Verifica algum erro de execucao durante a execucao de um processo
     if ((pid = fork()) < 0){
        printf("Ocorreu um erro no processo de criacao de novo processo");
        return 0;
    }

    //Execucao do processo pai
    if (pid != 0){
        printf("\nInsira dois nomes: ");
        scanf("%s", nome1);
        printf("Nome lido pelo processo pai: %s\n", nome1);

        while(1){
            printf("aguardando status do filho...");
            wait(&status);
            printf("\nStatus reebido!");

         if(WIFEXITED(status)){
            printf("\nProcesso do filho finalizado!");
            printf("\nStatus de termino: %d.", WEXITSTATUS(status));
            break;
         }
         if(WIFSIGNALED(status)){
            printf("\nProcesso filho recebeu sinal e terminou!");
            printf("\nSinal que finalizou o processo filho: %d.", WTERMSIG(status));
            break;
         }

         if( WIFSTOPPED(status) ){
            printf("\nO processo filho recebeu sinal de parada");
            printf("\nSinal que finalizou o processo filho %d.", WSTOPSIG(status));
         }
        }
    }else{
        int j;
        scanf("%s", nome2);
        printf("Nome lido pelo processo filho: %s\n", nome2);
        printf("1 - finalizar processo");
        printf("\nOutra tecla - continuar para contagem\n");
        scanf("%d", &j);

        if(j==1){
            exit(0);
        }

        for(int i=10; i>-1; i--){
            printf("fim do processo filho em %d s...\n", i);
            sleep(1);
        }
    }

    printf("\nInsira um nome: ");
    scanf("%s", nome3);
    printf("nome lido pelos dois processos: %s\n", nome3);
    return 0;
}
