#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "FiltroEstatico.h"


//typedef struct {int rows; int cols; unsigned char* data;} sImage;

struct sImage{
	int rows;
	int cols;
	unsigned char* data;
};


int compare(const void * a, const void * b)
{
	return (*(int*)a - *(int*)b);
}

void functionEstatic(sImage originalImage, sImage edgeImage, int type)
{
	int Y, X, I, J, SUM;
	int vet[9];
	int indVetor = 0;

	for (Y = 0; Y <= (originalImage.rows - 1); Y++)  {
		for (X = 0; X <= (originalImage.cols - 1); X++)  {
			/* image boundaries */
			if (Y == 0 || Y == originalImage.rows - 1)
				SUM = 0;
			else{


				if (X == 0 || X == originalImage.cols - 1)
					SUM = 0;
				/* Convolution starts here */
				else   {

					indVetor = 0;

					for (I = -1; I <= 1; I++)  {
						for (J = -1; J <= 1; J++)  {
							vet[indVetor] = (int)(*(originalImage.data + X + I +
								(Y + J)*originalImage.cols));
							indVetor++;
						}
					}

					qsort(vet, 9, sizeof(int), compare);

					//Maximo
					SUM = vet[type];

				}
			}

			if (SUM>255) SUM = 255;
			if (SUM<0) SUM = 0;

			//  *(originalImage.data + X + Y*originalImage.cols) = 255 - (unsigned char)(SUM);
			*(edgeImage.data + X + Y*originalImage.cols) = (unsigned char)(SUM);


		}


	}
	for (Y = 0; Y <= (originalImage.rows - 1); Y++)  {
		for (X = 0; X <= (originalImage.cols - 1); X++)  {
			*(originalImage.data + X + Y*originalImage.cols) = (unsigned char)*(edgeImage.data + X + Y*originalImage.cols);
		}
	}
	//originalImage = edgeImage;
}

