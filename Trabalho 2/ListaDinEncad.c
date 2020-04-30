#include <stdio.h>
#include <stdlib.h>
#include "ListaDinEncad.h"  //inclui os Prototipos

Lista* cria_lista()
{
    Lista* li = (Lista*) malloc(sizeof(Lista));
    if(li != NULL)
        *li = NULL;
    return li;
}

void libera_lista(Lista* li)
{
    if(li != NULL){
        Elem* no;
        while((*li) != NULL){
            no = *li;
            *li = (*li)->prox;
            free(no);
        }
        free(li);
    }
}

int consulta_lista_pos(Lista* li, int pos, Elem **el)
{
    if(li == NULL || pos <= 0)
        return ERRO;
    Elem *no = *li;
    int i = 1;
    while(no != NULL && i < pos){
        no = no->prox;
        i++;
    }
    if(no == NULL)
        return ERRO;
    else{
        *el = no;
        return OK;
    }
}

int consulta_lista_dado(Lista* li, Tipo_Dado dt, Elem **el)
{
    if(li == NULL)
        return ERRO;
    Elem *no = *li;
    while(no != NULL && no->dado != dt){
        no = no->prox;
    }
    if(no == NULL)
        return ERRO;
    else{
        *el = no;
        return OK;
    }
}

int insere_lista_final(Lista* li, Tipo_Dado dt)
{
    if(li == NULL)
        return ERRO;
    Elem *no;
    no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL)
        return ERRO;
    no->dado = dt;
    no->prox = NULL;
    if((*li) == NULL){ //lista vazia: insere inicio
        *li = no;
    }else{
        Elem *aux;
        aux = *li;
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = no;
    }
    return OK;
}

int remove_lista(Lista* li, Tipo_Dado dt)
{
    if(li == NULL)
        return ERRO;
    if((*li) == NULL)//lista vazia
        return ERRO;
    Elem *ant, *no = *li;
    while(no != NULL && no->dado != dt){
        ant = no;
        no = no->prox;
    }
    if(no == NULL) //nao encontrado
        return ERRO;

    if(no == *li) //remover o primeiro?
        *li = no->prox;
    else
        ant->prox = no->prox;
    free(no);
    return OK;
}

int remove_lista_inicio(Lista* li)
{
    if(li == NULL)
        return ERRO;
    if((*li) == NULL) //lista vazia
        return ERRO;

    Elem *no = *li;
    *li = no->prox;
    free(no);
    return OK;
}


int tamanho_lista(Lista* li)
{
    if(li == NULL)
        return 0;
    int cont = 0;
    Elem* no = *li;
    while(no != NULL){
        cont++;
        no = no->prox;
    }
    return cont;
}

int lista_cheia(Lista* li)
{
    return 0;
}

int lista_vazia(Lista* li)
{
    if(li == NULL)
        return 1;
    if(*li == NULL)
        return 1;
    return 0;
}

void imprime_lista(Lista* li)
{
    if(li == NULL)
        return;
    Elem* no = *li;
    while(no != NULL){
        printf("Dado: %5d # %p - %p\n",no->dado,no,no->prox);
        no = no->prox;
    }
    printf("-------------- FIM LISTA -----------------\n");
}
