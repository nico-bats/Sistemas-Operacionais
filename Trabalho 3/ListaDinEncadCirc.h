//Arquivo ListaDinEncadCirc.h

typedef struct{
    int page_id;
    int id;
}page;

//Definicao do tipo lista
struct elemento{
    page pagina;
    int r;
    struct elemento *prox;
};

typedef struct elemento Elem;
typedef struct elemento* Lista;

Lista* cria_lista();
void libera_lista(Lista* li);
int consulta_lista_pos(Lista* li, int pos, page *al);
int consulta_lista_mat(Lista* li, int id, page *al);
int insere_lista_final(Lista* li, page al);
int remove_lista(Lista* li, page al);
int remove_lista_inicio(Lista* li);
int remove_lista_final(Lista* li);
int tamanho_lista(Lista* li);
int lista_vazia(Lista* li);

