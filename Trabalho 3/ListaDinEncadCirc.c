#include <stdio.h>
#include <stdlib.h>
#include "ListaDinEncadCirc.h"


Lista* cria_lista(){
    Lista* li = (Lista*) malloc(sizeof(Lista));
    if(li != NULL)
        *li = NULL;
    return li;
}

void libera_lista(Lista* li){
    if(li != NULL && (*li) != NULL){
        Elem *aux, *no = *li;
        while((*li) != no->prox){
            aux = no;
            no = no->prox;
            free(aux);
        }
        free(no);
        free(li);
    }
}

int consulta_lista_pos(Lista* li, int pos, page *al){
    if(li == NULL || (*li) == NULL || pos <= 0)
        return 0;
    Elem *no = *li;
    int i = 1;
    while(no->prox != (*li) && i < pos){
        no = no->prox;
        i++;
    }
    if(i != pos)
        return 0;
    else{
        *al = no->pagina;
        return 1;
    }
}

int consulta_lista_mat(Lista* li, int id, page *al){
    if(li == NULL || (*li) == NULL)
        return 0;
    Elem *no = *li;
    while(no->prox != (*li) && no->pagina.id != id)
        no = no->prox;
    if(no->pagina.id != id)
        return 0;
    else{
        *al = no->pagina;
        return 1;
    }
}

int insere_lista_final(Lista* li, page al){
    if(li == NULL)
        return 0;
    Elem *no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL)
        return 0;
    no->pagina = al;
    no->r = 0;
    if((*li) == NULL){//lista vazia: insere inicio
        *li = no;
        no->prox = no;
    }else{
        Elem *aux = *li;
        while(aux->prox != (*li)){
            aux = aux->prox;
        }
        aux->prox = no;
        no->prox = *li;
    }
    return 1;
}

int remove_lista_inicio(Lista* li){
    if(li == NULL)
        return 0;
    if((*li) == NULL)//lista vazia
        return 0;

    if((*li) == (*li)->prox){//lista fica vaza
        free(*li);
        *li = NULL;
        return 1;
    }
    Elem *atual = *li;
    while(atual->prox != (*li))//procura o ultimo
        atual = atual->prox;

    Elem *no = *li;
    atual->prox = no->prox;
    *li = no->prox;
    free(no);
    return 1;
}

int remove_lista_final(Lista* li){
    if(li == NULL)
        return 0;
    if((*li) == NULL)//lista vazia
        return 0;

    if((*li) == (*li)->prox){//lista fica vaza
        free(*li);
        *li = NULL;
        return 1;
    }
    Elem *ant, *no = *li;
    while(no->prox != (*li)){//procura o ultimo
        ant = no;
        no = no->prox;
    }
    ant->prox = no->prox;
    free(no);
    return 1;
}

int remove_lista(Lista* li, page al){
    if(li == NULL)
        return 0;
    if((*li) == NULL)//lista vazia
        return 0;
    Elem *no = *li;
    if(no->pagina.id == al.id){//remover do inicio
        if(no == no->prox){//lista fica vaza
            free(no);
            *li = NULL;
            return 1;
        }else{
            Elem *ult = *li;
            while(ult->prox != (*li))//procura o ultimo
                ult = ult->prox;
            ult->prox = (*li)->prox;
            *li = (*li)->prox;
            free(no);
            return 1;
        }
    }
    Elem *ant = no;
    no = no->prox;
    while(no != (*li) && no->pagina.id != al.id){
        ant = no;
        no = no->prox;
    }
    if(no == *li)//nao encontrado
        return 0;

    ant->prox = no->prox;
    free(no);
    return 1;
}

int tamanho_lista(Lista* li){
    if(li == NULL || (*li) == NULL)
        return 0;
    int cont = 0;
    Elem* no = *li;
    do{
        cont++;
        no = no->prox;
    }while(no != (*li));
    return cont;
}

int lista_cheia(Lista* li){
    return 0;
}

int lista_vazia(Lista* li){
    if(li == NULL)
        return 1;
    if(*li == NULL)
        return 1;
    return 0;
}

void imprimir_lista(Lista* li){
    Elem* aux = *li;
    int i = 0;
    printf("IMPRIMINDO LISTA CIRCULAR:\n");
    do{
        printf("Processo %d, quadro %d, r=%d\n",aux->pagina.page_id, aux->pagina.id, aux->r);
        i++;
        aux = aux->prox;
    }while(aux != *li);
    printf("Tamanho: %d\n\n",i);
}


