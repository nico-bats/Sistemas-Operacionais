#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

//Demonstrativo das syscalls mmap e munmap através do mapeamento de espaço em mémória para armazenar uma string
int main(void) {
    size_t pagesize = getpagesize();//Obtém tamanho da página virtual no sistema operacional

    printf("Tamanho da pagina do sistema: %zu bytes\n", pagesize);

    //Definindo uma string com 'mmap', ou seja, mapeando espaço na memória para armazenar uma string no tamanho de 2^10*pagesize bytes
    char* region = mmap((void*) (pagesize*(1<<10)), pagesize, PROT_READ|PROT_WRITE|PROT_EXEC,MAP_ANONYMOUS|MAP_PRIVATE,0,0);

    //Se esse macro for retornado (MAP_FAILED = (void*)-1), houve falha no mapeamento
    if(region == MAP_FAILED){
        perror("Nao foi possivel executar a syscall 'mmap'.");
        return 1;
    }
    //Definindo a string e copiando-a para a região mapeada, com memória já alocada
    strcpy(region, "Projeto 1");

    //Esse comando exibirá 'Projeto 1' na tela
    printf("Conteudo da regiao mapeada: %s\n", region);

    //Utilizando a syscall 'munmap' para limpar a região
    int unmap_result = munmap(region, 1<<10);

    //Se 'munmap' não retornou zero, não foi possível limpar a região mapeada.
    if(unmap_result != 0){
        perror("Nao foi possivel executar a syscall 'munmap");
        return 1;
    }
  return 0;
}

