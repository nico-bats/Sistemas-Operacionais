#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
Para exemplificar o comportamento de um processo CPU-bound foi pego este programa o qual foi utilizado em uma disciplina de ICC1
para operacoes em uma imagem .pgm realizando a operacao de preenchimento de pixels dentro de uma linha

*/

//Resolucao de imagem 

typedef struct {  //Struct que armazena dados da imagem
	unsigned char* Data;
	int IsBinary;
	int Width;
	int Height;
	unsigned char MaxValue;
} Image;

Image* NewImage(int width, int height) {   //Funcao que aloca todo o espaco dinamico necessario

	Image* pointer;
	pointer = malloc(sizeof(Image));
	pointer->Height = height;
	pointer->Width = width;
	pointer->Data = calloc(width*height, sizeof(unsigned char));

	return pointer;

}

void FreeImage(Image* pointer) {   //Funcao que libera o espaco alocado


	free(pointer->Data);
	free(pointer);

}

void ReadBinary(FILE* file, Image* img) { //Funcao que le no caso da imagem ser do tipo binaria

	int i;

	for (i = 0; i < img->Width*img->Height; i++) {

		img->Data[i] = fgetc(file);

	}

}

void ReadText(FILE* file, Image* image) {  //Funcao que le no caso da imagem ser do tipo texto

	int i;

	for (i = 0; i < image->Width*image->Height; i++) {


		fscanf(file, "%hhu", &image->Data[i]);

	}

}

Image* ReadImage(FILE* file) {   //Funcao que le a imagem na ordem dos dados contidos no PDF
	int n;
	char buffer[100];
	int hieght;
	int width;
	Image* image;

	fscanf(file, "P%i #",&n);
	fgets(buffer, 100, file);
	fscanf(file, "%i", &hieght);
	fscanf(file, "%i", &width);

	image = NewImage(width, hieght);

	if (n == 2) image->IsBinary = 0;
	else image->IsBinary = 1;

	fscanf(file, "%hhu", &image->MaxValue);
	fgets(buffer, 100, file);

	if (image->IsBinary == 1) {

		ReadBinary(file, image);

	}
	else {

		ReadText(file, image);

	}


	return image;

}

void SaveImage(FILE* file, Image* image) {  //Funcao que salva a imagem na saida de acordo com o formato solicitado

	fprintf(file, "P2\n# CREATOR: Image Generator I\n%i %i\n%hhu\n", image->Height, image->Width, image->MaxValue);
	int i;

	for (i = 0; i < image->Width*image->Height; i++) {

		fprintf(file, "%hhu\n", image->Data[i]);
	}

}


//As duas funcoes abaixo buscam o maior e o menor pixel respectivamente

unsigned char GetMaxPixel(Image* image) {
	int i;
	unsigned char maxPixel;

	for (i = 0; i < image->Height*image->Width; i++) {
		if (maxPixel < image->Data[i]) {

			maxPixel = image->Data[i];

		}
	}

	return maxPixel;
}

unsigned char GetMinPixel(Image* image) {
	int i;

	unsigned char minPixel;

	for (i = 0; i < image->Height*image->Width; i++) {
		if (minPixel > image->Data[i]) {

			minPixel = image->Data[i];

		}
	}


	return minPixel;
}


void FloodFill(Image* image, int index) {  //Operação 3 - FlooFill (balde do paint brush) que procura preencher ao seu redor de acordo com a condiçao correta da posição do pixel

	if (image->Data[index] == 255 || image->Data[index] == 100) {
		return;
	}
	image->Data[index] = 100;

	if (image->Data[index+1] != 255 && image->Data[index+1] != 100) {

		FloodFill(image, index + 1);
	}

	if (image->Data[index-1] != 255 && image->Data[index-1] != 100) {

		FloodFill(image, index - 1);
	}

	if (image->Data[index+image->Height] != 255 && image->Data[index+image->Height] != 100) {

		FloodFill(image, index + image->Height);
	}

	if (image->Data[index-image->Height] != 255 && image->Data[index-image->Height] != 100) {

		FloodFill(image, index - image->Height);
	}

}


int main() {   //Funcao pricipal recebe os dados da operacao e o nome do arquivo

	int operation;
	char filename[100];

	FILE* fileAddress = fopen("folha2.pgm", "rb");

	Image* image = ReadImage(fileAddress);
	fclose(fileAddress);

	FILE* fileAddress2 = fopen("folha2dps.pgm", "wb");

	int index = (( image->Height / 2)*image->Width) + (image->Width/2);
	FloodFill(image, index);
	SaveImage(fileAddress2, image);

	fclose(fileAddress2);
		
}
