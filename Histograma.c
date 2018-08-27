#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "Histograma.h"
//#include "alloc.h"

/*-------STRUCTURES---------*/
//typedef struct {int rows; int cols; unsigned char* data;} sImage;

struct sImage{
	int rows;
	int cols;
	unsigned char* data;
};


void salvarNoTxt(int vet[256])
{
	FILE *hist;
	int I;

	hist = fopen("hist.txt", "wb");

	for (I = 0; I<256; I++)
	{
		fprintf(hist, "%d", I);
		fprintf(hist, ";");
		fprintf(hist, "%d", vet[I]);
		fprintf(hist, "\r");
		fputs("\n", hist);
	}
	fclose(hist);
}

void funcionHistEqualization(sImage originalImage, sImage edgeImage, int histograma[256])
{
	int vet[256] = { 0 };
	int teste = 0;
	float sum;
	int X, Y, i, j, k;

	for (i = 0; i < 256; i++){
		sum = 0;
		for (j = 0; j <= i; j++)
		{
			sum = sum + histograma[j];
		}

		vet[i] = (int)(sum * 255) / 1048576;
	}

	for (Y = 0; Y <= (originalImage.rows - 1); Y++)  {
		for (X = 0; X <= (originalImage.cols - 1); X++)  {

			k = (int)(*(originalImage.data + X + Y * originalImage.cols));
			*(edgeImage.data + X + Y*originalImage.cols) = (unsigned char)(vet[k]);

		}
	}
	for (Y = 0; Y <= (originalImage.rows - 1); Y++)  {
		for (X = 0; X <= (originalImage.cols - 1); X++)  {
			*(originalImage.data + X + Y*originalImage.cols) = *(edgeImage.data + X + Y*originalImage.cols);
		}
	}
}

void functionHistSpecification(sImage originalImage, sImage edgeImage, int histograma[256])
{
	int vet[256] = { 0 };

	int newVet[256] = { 0 };
	float sum;
	int i, j, x, y, k, X, Y;

	for (i = 0; i < 256; i++){
		sum = 0.0;
		for (j = 0; j <= i; j++)
		{
			sum = sum + histograma[j];
		}
		vet[i] = (int)(sum * 255) / 1048576;
	}

	for (i = 0; i<256; i++)
	{
		x = abs(i - vet[0]);
		y = 0;
		for (j = 0; j<256; j++)
		{
			if (abs(i - vet[j])< x)
			{
				x = abs(i - vet[j]);
				y = j;
			}
			newVet[i] = y;
		}
	}
	for (Y = 0; Y <= (originalImage.rows - 1); Y++)  {
		for (X = 0; X <= (originalImage.cols - 1); X++)  {

			k = (int)(*(originalImage.data + X + Y*originalImage.cols));

			*(edgeImage.data + X + Y*originalImage.cols) = (unsigned char)newVet[k];
		}
	}

	for (Y = 0; Y <= (originalImage.rows - 1); Y++)  {
		for (X = 0; X <= (originalImage.cols - 1); X++)  {
			*(originalImage.data + X + Y*originalImage.cols) = *(edgeImage.data + X + Y*originalImage.cols);
		}
	}

}

void imprimirTela(int vet[256])
{

	int I;
	int x, y;
	int porcentagem[16] = { 0 };
	float valor, num1, num2;
	int total = 0;

	for (I = 0; I<256; I++)
	{
		if ((I >= 0) && (I<16)){
			porcentagem[0] += vet[I];
		}
		if ((I >= 16) && (I<32)){
			porcentagem[1] += vet[I];
		}
		if ((I >= 32) && (I<48)){
			porcentagem[2] += vet[I];
		}
		if ((I >= 48) && (I<64)){
			porcentagem[3] += vet[I];
		}
		if ((I >= 64) && (I<80)){
			porcentagem[4] += vet[I];
		}
		if ((I >= 80) && (I<96)){
			porcentagem[5] += vet[I];
		}
		if ((I >= 96) && (I<112)){
			porcentagem[6] += vet[I];
		}
		if ((I >= 112) && (I<128)){
			porcentagem[7] += vet[I];
		}
		if ((I >= 128) && (I<144)){
			porcentagem[8] += vet[I];
		}
		if ((I >= 144) && (I<160)){
			porcentagem[9] += vet[I];
		}
		if ((I >= 160) && (I<172)){
			porcentagem[10] += vet[I];
		}
		if ((I >= 172) && (I<192)){
			porcentagem[11] += vet[I];
		}
		if ((I >= 192) && (I<208)){
			porcentagem[12] += vet[I];
		}
		if ((I >= 208) && (I<224)){
			porcentagem[13] += vet[I];
		}
		if ((I >= 224) && (I<240)){
			porcentagem[14] += vet[I];
		}
		if ((I >= 240) && (I<256)){
			porcentagem[15] += vet[I];
		}

		total += vet[I];
	}
	system("cls");
	//printf("%d",total);
	for (I = 0; I < 16; I++){

		num1 = (float)porcentagem[I];
		num2 = (float)total;
		x = (I * 16) + 1;
		y = (I * 16) + 16;
		printf("Corresponde a %d a %d: ", x, y);
		valor = (float)((num1 / num2) * 100);
		valor = (int)(valor);
		while (valor > 1){
			printf("* ");
			valor = valor - 2;
		}
		printf("\n");
	}
	printf("\nOBS: Cada * equivale a 2 %%.\n\n");
	system("pause");
	system("cls");
}


void functionHistograma(sImage originalImage, sImage edgeImage, int opcao)
{
	int Y, X, I, J, SUM, sumX, sumY;
	float num1, num2;
	int indice = 0;
	int histograma[256] = { 0 };

	for (Y = 0; Y <= (originalImage.rows - 1); Y++)  {
		for (X = 0; X <= (originalImage.cols - 1); X++)  {
			sumX = 0;
			sumY = 0;

			indice = (int)(*(originalImage.data + X + Y * originalImage.cols));
			histograma[indice] ++;

		}
	}
	if (opcao == 1)
	{
		salvarNoTxt(histograma);
	}
	if (opcao == 2){
		imprimirTela(histograma);
	}
	if (opcao == 3){
		funcionHistEqualization(originalImage, edgeImage, histograma);
	}
	if (opcao == 4){
		functionHistSpecification(originalImage, edgeImage, histograma);
	}


}
