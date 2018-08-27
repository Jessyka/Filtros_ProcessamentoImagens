#include <stdio.h>
#include <stdlib.h>

#include "math.h"
#include "FiltroEstatico.h"
#include "FiltrosLineares.h"
#include "Histograma.h"
#include "StructImage.h"
#include "string.h"

//#include "alloc.h"

struct sImage{
	int rows;
	int cols;
	unsigned char* data;
};


/*-------PROTOTYPES---------*/
long getImageInfo(FILE*, long, int);
void copyImageInfo(FILE* inputFile, FILE* outputFile);
void copyColorTable(FILE* inputFile, FILE* outputFile, int nColors);
int opcoesHistograma(sImage originalImage, sImage edgeImage);

int main(int argc, char* argv[])
{
	FILE                 *bmpInput, *bmpOutput;
	sImage               originalImage;
	sImage               edgeImage;
	sImage			     newImage;
	char				 nomeArquivo[100];
	char				 nomeimagem[100];
	int                  statusEdicao = 0;
	int                  nColors, val, hist, X, Y;
	unsigned long        vectorSize;
	unsigned long        fileSize;
	unsigned char        *pChar, someChar;
	unsigned int         row, col;

	val = 1;
	
	//Altere aqui o nome da imagem que deseja processar.
	strcpy(nomeimagem, "baby.bmp");
	
	someChar = '0'; 
	pChar = &someChar;
	bmpInput = fopen(nomeimagem, "rb");

	fseek(bmpInput, 0L, SEEK_END);

	/*-------GET INPUT BMP DATA--------*/
	fileSize = getImageInfo(bmpInput, 2, 4);
	originalImage.cols = (int)getImageInfo(bmpInput, 18, 4);
	originalImage.rows = (int)getImageInfo(bmpInput, 22, 4);
	edgeImage.rows = originalImage.rows;
	edgeImage.cols = originalImage.cols;

	/*--------PRINT DATA TO SCREEN----------*/
	printf("Largura: %d\n", originalImage.cols);
	printf("Altura: %d\n", originalImage.rows);
	printf("Tamanho do Arquivo: %lu\n", fileSize);

	nColors = (int)getImageInfo(bmpInput, 46, 4);
	printf("Cores: %d\n", nColors);

	/*------ALLOCATE MEMORY FOR FILES--------*/
	vectorSize = fileSize - (14 + 40 + 4 * nColors);
	printf("vectorSize: %lu\n", vectorSize);
	edgeImage.data = malloc(vectorSize*sizeof(unsigned char));

	if (edgeImage.data == NULL) {
		printf("Falha para malloc edgeImage.data\n");
		exit(0);
	}

	originalImage.data = malloc(vectorSize*sizeof(unsigned char));

	if (originalImage.data == NULL) {
		printf("Falha para malloc originalImage.data\n");
		exit(0);
	}	

	fseek(bmpInput, (14 + 40 + 4 * nColors), SEEK_SET);

	/* Read input.bmp and store it's raster data into originalImage.data */
	for (row = 0; row <= originalImage.rows - 1; row++) {
		for (col = 0; col <= originalImage.cols - 1; col++) {
			fread(pChar, sizeof(char), 1, bmpInput);
			*(originalImage.data + row*originalImage.cols + col) = *pChar;
		}
	}

	printf("Lendo o arquivo... %s\n", nomeimagem);

	while (val != 7)
	{
		system("cls");
		printf("Escolha Um Efeito:\n");
		printf("1 - Sobel:\n");
		printf("2 - Smoothing:\n");
		printf("3 - Histograma:\n");
		printf("4 - Max:\n");
		printf("5 - Min:\n");
		printf("6 - Mediana:\n");
		printf("7 - Sair:\n");
		printf("Digite Sua Opcao:\n");
		scanf("%d", &val);

		switch (val)
		{
			case 1:
				statusEdicao = 1;
				functionSobel(originalImage, edgeImage);
				printf("\nEfeito processado.\n");
				system("pause");
				printf("\n");
				break;
			case 2:
				statusEdicao = 1;
				functionSmoothing(originalImage, edgeImage);
				printf("\nEfeito processado.\n");
				system("pause");
				printf("\n");
				break;
			case 3:	
				if (opcoesHistograma(originalImage, edgeImage) == 1)
					statusEdicao = 1;
				break;
			case 4:
				statusEdicao = 1;
				functionEstatic(originalImage, edgeImage, 0);
				printf("\nEfeito processado.\n");
				system("pause");
				printf("\n");
				break;
			case 5:
				statusEdicao = 1;
				functionEstatic(originalImage, edgeImage, 8);
				printf("\nEfeito processado.\n");
				system("pause");
				printf("\n");
				break;
			case 6:
				statusEdicao = 1;
				functionEstatic(originalImage, edgeImage, 4);
				printf("\nEfeito processado.\n");
				system("pause");
				printf("\n");
				break;
			case 7:
				break;
			default:
				printf("\nOpcao invalida.\n");
				system("pause");
				printf("\n");
		}
	}

	if (statusEdicao == 1){

		//Armazenar a imagem
		printf("\nDigite um nome para a imagem(sem a extensao .bmp)\n");
		fflush(stdin);
		gets(nomeArquivo);
		strcat(nomeArquivo, ".bmp");

		bmpOutput = fopen(nomeArquivo, "wb");
		copyImageInfo(bmpInput, bmpOutput);
		copyColorTable(bmpInput, bmpOutput, nColors);

		fseek(bmpOutput, (14 + 40 + 4 * nColors), SEEK_SET);
		for (Y = 0; Y <= (originalImage.rows - 1); Y++)  {
			for (X = 0; X <= (originalImage.cols - 1); X++)  {
				fwrite((originalImage.data + X + Y*originalImage.cols), sizeof(char), 1, bmpOutput);
			}
		}

		fclose(bmpOutput);

		printf("Para ver os resultados acesse %s\n", nomeArquivo);
	}
	
	fclose(bmpInput);
	free(edgeImage.data);      
	free(originalImage.data);  
	system("pause");
	return 0;
}


int opcoesHistograma(sImage originalImage, sImage edgeImage)
{
	int opcao, statusEdicao = 0;
	printf("Escolha Uma das Opcoes:\n");
	printf("1 - Salvar em Arquivo:\n");
	printf("2 - Em Tela:\n");
	printf("3 - Equalizar:\n");
	printf("4 - Specification:\n");

	scanf("%d", &opcao);

	switch (opcao)
	{
		case 1:
			functionHistograma(originalImage, edgeImage, 1);
			break;
		case 2:
			functionHistograma(originalImage, edgeImage, 2);
			break;
		case 3:
			statusEdicao = 1;
			functionHistograma(originalImage, edgeImage, 3);
			break;
		case 4:
			statusEdicao = 1;
			functionHistograma(originalImage, edgeImage, 4);
			break;
		default:
			printf("opcao invalida");
			system("pause");
			printf("\n");
			break;
	}

	return statusEdicao;
}

/*----------GET IMAGE INFO SUBPROGRAM--------------*/
long getImageInfo(FILE* inputFile, long offset, int numberOfChars)
{
	unsigned char                 *ptrC;
	long                          value = 0L;
	unsigned char                 dummy;
	int                           i;

	dummy = '0';
	ptrC = &dummy;

	fseek(inputFile, offset, SEEK_SET);

	for (i = 1; i <= numberOfChars; i++)
	{
		fread(ptrC, sizeof(char), 1, inputFile);
		/* calculate value based on adding bytes */
		value = (long)(value + (*ptrC)*(pow(256, (i - 1))));
	}
	return(value);

} /* end of getImageInfo */

/*-------------COPIES HEADER AND INFO HEADER----------------*/
void copyImageInfo(FILE* inputFile, FILE* outputFile)
{
	unsigned char         *ptrC;
	unsigned char         dummy;
	int                           i;

	dummy = '0';
	ptrC = &dummy;

	fseek(inputFile, 0L, SEEK_SET);
	fseek(outputFile, 0L, SEEK_SET);

	for (i = 0; i <= 50; i++)
	{
		fread(ptrC, sizeof(char), 1, inputFile);
		fwrite(ptrC, sizeof(char), 1, outputFile);
	}

}

/*----------------COPIES COLOR TABLE-----------------------------*/
void copyColorTable(FILE* inputFile, FILE* outputFile, int nColors)
{
	unsigned char         *ptrC;
	unsigned char         dummy;
	int                           i;

	dummy = '0';
	ptrC = &dummy;

	fseek(inputFile, 54L, SEEK_SET);
	fseek(outputFile, 54L, SEEK_SET);

	for (i = 0; i <= (4 * nColors); i++)  /* there are (4*nColors) bytesin color table */
	{
		fread(ptrC, sizeof(char), 1, inputFile);
		fwrite(ptrC, sizeof(char), 1, outputFile);
	}

}
