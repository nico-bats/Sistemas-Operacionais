#include <stdio.h>
#include <stdlib.h>
#include "ListaDinEncadCirc.h"
#include <string.h>

//configuracao de mecanismos associados a memoria vintual
#define pagesize 500
#define quadrosize 50
#define adresssize 10
#define memorysize 5000 //memoria princial com 5kB
#define secondmemorysize 5000000 //memoria secundaria com 5MB
#define processimagesize 50

int memory[memorysize]; //Vetor que representa a memoria princial
int secondmemory[secondmemorysize]; //Vetor que representa a memoria virtual

int qtdquadros = (memorysize/quadrosize);
int qtdpaginas = (secondmemorysize/pagesize);
Lista* relogio;

int alg_relogio(Lista* relogio, page al){
    int flag = 0;
    Elem* no_aux = *relogio;
    while(1){
        if(no_aux->r == 0){
            flag = 1;
            break;
        }
        no_aux = no_aux->prox;
        if(no_aux == *relogio)
            break;
    }
    if(flag==0)
        return flag;
    else{
        remove_lista(relogio, al);
        insere_lista_final(relogio, al);
        return flag;
    }
}

void insere_relogio(Lista* relogio, int start, int id, int num_paginas){

    page aux;

    if(qtdpaginas > 0){
        for(int i=start;i<num_paginas;i++){
            aux.id = i;
            aux.page_id = id;
            insere_lista_final(relogio, aux);
            printf("Quadro %d criado!\n",i);
        }
    }
    else{//mem�ria secund�ria cheia = algoritmo do rel�gio
        for(int i=start;i<num_paginas;i++){
            aux.id = i;
            aux.page_id = id;
            if(alg_relogio(relogio, aux) == 1)
                printf("Quadro %d criado!\n",i);
            else
                printf("Nao ha memoria suficiente para alocar o quadro %d do processo %d.\n",i,id);
        }
    }
}

int main(){

    //Variavel de controle da memoria
    int memoryavailable = memorysize;
    int secondmemoryavailable = secondmemorysize;

    FILE* fp = fopen("input.txt","rt");
    if(fp == NULL){
        printf("Erro ao abrir o arquivo de entrada");
        return 0;
    }
    char carac;
    int b = 0;
    int siz = 0;
    char buffer[100];
    relogio = cria_lista();
    page aux;
    Elem* no_aux;
    int tam;
    fgets(buffer,100,fp); //primeira linha do arquivo deve ser ignorada

    int id;
    char op;
    int size;
    char adrnum[5];
    int num_paginas;
    printf("<<GERENCIADOR DE MEMORIA>>\n\n");
    printf("A memoria primaria possui:\n%d quadros\nA memoria secundaria possui:\n%d paginas\n",qtdquadros, qtdpaginas);
    while (b == 0){
        tam = tamanho_lista(relogio); //Obtem tamanho da lista de quadros de cada processo
        fgets(buffer,100,fp);//captura a linha

        carac = buffer[0];
        if(carac == '#'){ //verifica se eh fim do arquivo
            b = 1;
        }
        else{//Leitura dos processos
            if(carac == 'P'){
                carac = buffer[1];
                id = atoi(&carac); //recebe o id

                op = buffer[3]; //recebe a operacao

                carac = buffer[5];
                if(carac == '('){ //capturo o tamanho em binario
                    siz = strlen(buffer);
                    siz = siz - 8;
                    strncpy(adrnum,&buffer[6],siz);
                    size = atoi(adrnum);

                }
                else{//capturo o tamanho
                    siz = strlen(buffer);
                    siz = siz - 5;
                    strncpy(adrnum,&buffer[5],siz);
                    size = atoi(adrnum);

                }
            }
            num_paginas = size/processimagesize;

        }
        if(op == 'C'){
            printf("\nCriando quadros do processo %d...\n",id);
            insere_relogio(relogio, 0, id, num_paginas);
            //imprimir_lista(relogio);
        }
        else if(op == 'R'){
            if(qtdpaginas >= num_paginas){
                qtdquadros += num_paginas;
                qtdpaginas -= num_paginas;
                printf("\nA memoria primaria possui:\n%d quadros\nA memoria secundaria possui:\n%d paginas\n",qtdquadros, qtdpaginas);
                int i = 1;

                printf("\nLendo processo %d...\n",id);
                if(num_paginas != 0){
                    no_aux = *relogio;
                    do{
                        if(no_aux->pagina.page_id == id){
                            printf("Quadro %d lido!\n",no_aux->pagina.id);
                            no_aux->r = 1; //Foi referenciado recentemente
                            no_aux = no_aux->prox;
                            i++;
                        }
                        else
                            no_aux = no_aux->prox;
                    }while(no_aux != *relogio);

                    if(i < num_paginas){
                        printf("Criando mais %d quadros para o processo %d...\n", num_paginas - i, id);
                        insere_relogio(relogio, i, id, num_paginas);
                    }
                }
                else
                    printf("Nao ha nada pra ler.\n");
            }
            else{
                num_paginas-=qtdpaginas;
                insere_relogio(relogio, 0, id, num_paginas);
            }
        }
        else if(op == 'W'){//operacao de escrita requer trazer da memoria secundaria para principal para a escrita
            if(qtdpaginas >= num_paginas){
                qtdquadros += num_paginas;
                qtdpaginas -= num_paginas;

                printf("\nA memoria primaria possui:\n%d quadros\nA memoria secundaria possui:\n%d paginas\n",qtdquadros, qtdpaginas);
                int i = 1;

                printf("\nEscrevendo processo %d...\n",id);
                if(num_paginas != 0){
                    no_aux = *relogio;
                    do{
                        if(no_aux->pagina.page_id == id){
                            printf("Quadro %d escrever!\n",no_aux->pagina.id);
                            no_aux->r = 1; //Foi referenciado recentemente
                            no_aux = no_aux->prox;
                            i++;
                        }
                        else
                            no_aux = no_aux->prox;
                    }while(no_aux != *relogio);

                    if(i < num_paginas){
                        printf("Criando mais %d quadros para o processo %d...\n", num_paginas - i, id);
                        insere_relogio(relogio, i, id, num_paginas);
                    }
                }
                else
                    printf("Nao ha nada pra escrever.\n");
            }
            else{
                num_paginas-=qtdpaginas;
                insere_relogio(relogio, 0, id, num_paginas);
            }

        }
        else if (op == 'P'){
            printf("\nInstrucao de CPU #%d executada no processo %d\n",size,id);
            if(size == 2)
                printf("a");
        }
        else if(op == 'I'){
            printf("\nInstrucao de I/O #%d executada no processo %d\n",size,id);
        }


    }
    imprimir_lista(relogio);
    fclose(fp);
}
