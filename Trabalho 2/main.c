#include <stdio.h>
#include <stdlib.h>
#include "ListaDinEncad.h"
#define N 100

typedef int semaphore;
semaphore mutex = 1;
semaphore empty = N;
semaphore full = 0;

void inicialise(int *buffer, Lista* fila_livre, Lista* fila_ocupada){
    for(int i=0;i<N;i++){
        buffer[i] = -1;
        insere_lista_final(fila_livre, i);
    }
}

void down(int *x){
    (*x)--;
}

void up(int *x){
    (*x)++;
}

int random_gen(){
   time_t t;
   srand((unsigned) time(&t));

   int n;
   n = rand()%N;

   return n;
}

void produce_item(int *item){
    int n = random_gen();

    (*item) = n;
}

void enter_item(int item, int *buffer, Lista* fila_livre, Lista* fila_ocupada){
     //Inserir no buffer, remover a posição da lista de livres e inserir na lista de ocupados
     int pos;
     pos = (*fila_livre)->dado;
     remove_lista_inicio(fila_livre);
     insere_lista_final(fila_ocupada, pos);
     buffer[pos] = item;
}

void remove_item(int item, int *buffer, Lista* fila_livre, Lista* fila_ocupada){
    //Remover do buffer (procura antes), inserir a posição na fila de livres e remover da lista de ocupados
    int pos;
    pos = (*fila_ocupada)->dado;
    remove_lista_inicio(fila_ocupada);
    buffer[pos] = -1;
    insere_lista_final(fila_livre, pos);
}

void consume_item(int item){
    item++;
}

void producer(int *buffer, Lista* fila_livre, Lista* fila_ocupada){
    int item;
    int i=0;
    while(1){
        produce_item(&item);
        down(&empty);
        down(&mutex);
        enter_item(item, buffer, fila_livre, fila_ocupada);
        up(&mutex);
        up(&full);
    }
}

void consumer(int *buffer, Lista* fila_livre, Lista* fila_ocupada){
    int item;
    while(1){
        down(&full);
        down(&mutex);
        remove_item(item, buffer, fila_livre, fila_ocupada);
        up(&mutex);
        up(&empty);
        consume_item(item);
    }
}

int main()
{
    int buffer[N];
    Lista* fila_livre = cria_lista();
    Lista* fila_ocupada = cria_lista();
    inicialise(buffer, fila_livre, fila_ocupada);
    //imprime_lista(fila_livre);
    producer(buffer, fila_livre, fila_ocupada);
    consumer(buffer, fila_livre, fila_ocupada);

}
