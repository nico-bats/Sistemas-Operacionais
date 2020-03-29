#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
 /*
 Este programa exemplifica o uso da syscall "open()" em linux, a qual abre um arquivo novo e recebe seu descritor

 */
int main()
{
FILE *fp = fopen("teste.txt", "rw"); 

    int qtd = 0;
  int ch = getc(fp); 
  while (ch != EOF)  
  { 
     
    putchar(ch);  //exibe o conteudo do arquivo na tela

    ch = getc(fp); 
  } 
    
  if (feof(fp))  printf("\n Fim \n"); 

  fclose(fp); 
      
  return 0; 
}