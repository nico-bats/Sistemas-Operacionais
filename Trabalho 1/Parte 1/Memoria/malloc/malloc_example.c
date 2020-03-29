#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

//Demonstrativo do funcionamento da syscall sbrk implementando a função malloc
//Nesse código, o intuito é alocar um espaço size de memória para uma variável qualquer
void* my_malloc(size_t size){
	//Ao declarar a variável *p, estamos colocando o ponteiro no começo do segmento de memória a ser reservado,-
	//-um segmento que é achado pela syscall sbrk.
    void *p = sbrk(0);

    //Ao declarar a variável *q, estamos colocando ela em uma região que é size vezes mais adiante que *p,-
	//que é exatamente o tamanho que queremos reservar.
    void *q = sbrk(size);


	//Se essa atribuição der certo, ou seja, se houver o espaço requisitado, o sbrk(size) retornará 1 e será feita a atribuição a *p,-
	//-assim retornando à função que o chamou o espaço requisitado. Caso contrário, sbrk retornará -1, indicando erro.
    if(q == (void*)-1){
        return NULL;

    }else{
        assert(p == q);
        return p;
    }
}

int main(){
    int *ex;//Declarando um ponteiro para uma variável inteira
    ex = my_malloc(5);//Alocando espaço em memória
    printf("\n p : 0x%x \n",ex);//Será impresso na tela o endereço de ex
}
