#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "ListaDinEncad.h"

#define N 100

//Defino o buffer e as listas como uma variavel global para nao haver problema com o compartilhamento de conteudo
int buffer[N];
Lista* fila_livre;
Lista* fila_ocupada;

pthread_mutex_t mutex;// declaracao da variavel de condicao para tratar a exclusao mutua

void inicialise(int *buffer, Lista* fila_livre, Lista* fila_ocupada){
    for(int i=0;i<N;i++){
        buffer[i] = -1;
        insere_lista_final(fila_livre, i);
    }
}

int random_gen(){ //funcao que gera o conteudo do produtor
   time_t t;
   srand((unsigned) time(&t));

   int n;
   n = rand()%N;//Gera um número pseudoaleatório de 0 a N-1

   return n;
}

void produce_item(int *item){ //insercao do item pelo produtor
    int n = random_gen();
    (*item) = n;
}

void enter_item(int item, int *buffer, Lista* fila_livre, Lista* fila_ocupada){//Inserir no buffer, remover a posicao da lista de livres e inserir na lista de ocupados

     int pos;
     if(*fila_livre == NULL)
        return;
     pos = (*fila_livre)->dado;
     remove_lista_inicio(fila_livre);
     insere_lista_final(fila_ocupada, pos);
     buffer[pos] = item;
}

void remove_item(int *item, int *buffer, Lista* fila_livre, Lista* fila_ocupada){//Remover do buffer (procura antes), inserir a posicao na fila de livres e remover da lista de ocupados

    int pos;
    if(*fila_ocupada == NULL)
        return;
    pos = (*fila_ocupada)->dado;
    (*item) = buffer[pos];
    remove_lista_inicio(fila_ocupada);
    buffer[pos] = -1;
    insere_lista_final(fila_livre, pos);
}

void consume_item(int *item){ //consumir item
    (*item)++;
}

void producer(int *buffer, Lista* fila_livre, Lista* fila_ocupada){ //funcao responsavel pelo produtor e todos os requisitos
    int item = 0;
    int flag = 1;
    int i=0;
    while(1){
        produce_item(&item);

        while(flag == 1){
             pthread_mutex_lock(&mutex);
             flag = 0;

             if(*fila_livre == NULL){ //significa que o buffer esta cheio
                flag = 1;
                pthread_mutex_unlock(&mutex);
             }

        }
        printf("\nItem inserido: %d", item);
        enter_item(item, buffer, fila_livre, fila_ocupada);
        (*fila_livre == NULL);
        pthread_mutex_unlock(&mutex);
    }
}

void consumer(int *buffer, Lista* fila_livre, Lista* fila_ocupada){//funcao responsavel pelo consumidor e todos os requisitos
    int item;
    int flag = 1;
    while(1){
        while(flag == 1){
            pthread_mutex_lock(&mutex);
            flag = 0;

            if(*fila_ocupada == NULL){ //significa que o buffer esta vazio
                flag = 1;
                pthread_mutex_unlock(&mutex);
            }
        }

        remove_item(&item, buffer, fila_livre, fila_ocupada);
        (*fila_ocupada) == NULL;
        pthread_mutex_unlock(&mutex);
        printf("\nItem consumido: %d", item);
        consume_item(&item);
    }
}

void* consumer_thread(void* no){ //defino a thread para o consumidor
    consumer(buffer, fila_livre, fila_ocupada);
}

void* producer_thread(void* no){ //defino a thread para o produtor
    producer(buffer, fila_livre, fila_ocupada);
}


int main(){
    fila_livre = cria_lista();
    fila_ocupada = cria_lista();

    inicialise(buffer, fila_livre, fila_ocupada); //inicializacao do buffer limitado

    pthread_t consumer1,consumer2, producer1,producer2, producer3; //defino os IDs das threads que correspondem ao consumidor e produtor, respectivamente

    pthread_mutex_init(&mutex,NULL); //inicializacao do semaforo com valor inicial igual a zero o qual sera compartilhado por ambas as threads

    pthread_create (&consumer1,NULL,(void*) consumer_thread, 1);
    pthread_create (&consumer2,NULL,(void*) consumer_thread, 2);
    pthread_create (&producer1,NULL,(void*) producer_thread, 1);
    pthread_create (&producer2,NULL,(void*) producer_thread, 2);
    pthread_create (&producer3,NULL,(void*) producer_thread, 3);

	pthread_join(producer1,NULL);
    pthread_join(producer2,NULL);
    pthread_join(producer3,NULL);
    pthread_join(consumer1,NULL);
    pthread_join(consumer2,NULL);

    return 0;
}
