#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "FiltrosLineares.h"

//#include "alloc.h"

/*-------STRUCTURES---------*/
//typedef struct {int rows; int cols; unsigned char* data;} sImage;

struct sImage{
	int rows;
	int cols;
	unsigned char* data;
};



void functionSobel(sImage originalImage, sImage edgeImage)
{
	int Y, X, I, J, SUM, sumX, sumY;

	float cal;

	float                  GX[3][3];
	float                  GY[3][3];
	/* 3x3 GX Sobel mask.  Ref: www.cee.hw.ac.uk/hipr/html/sobel.html */
	GX[0][0] = 1; GX[0][1] = 2; GX[0][2] = 1;
	GX[1][0] = 0; GX[1][1] = 0; GX[1][2] = 0;
	GX[2][0] = -1; GX[2][1] = -2; GX[2][2] = -1;

	/* 3x3 GY Sobel mask.  Ref: www.cee.hw.ac.uk/hipr/html/sobel.html*/
	GY[0][0] = 1; GY[0][1] = 2; GY[0][2] = 1;
	GY[1][0] = 0; GY[1][1] = 0; GY[1][2] = 0;
	GY[2][0] = -1; GY[2][1] = -2; GY[2][2] = -1;

	for (Y = 0; Y <= (originalImage.rows - 1); Y++)  {
		for (X = 0; X <= (originalImage.cols - 1); X++)  {
			sumX = 0;
			sumY = 0;
			/* image boundaries */
			if (Y == 0 || Y == originalImage.rows - 1)
				SUM = 0;
			else if (X == 0 || X == originalImage.cols - 1)
				SUM = 0;

			/* Convolution starts here */
			else   {

				/*-------X GRADIENT APPROXIMATION------*/
				for (I = -1; I <= 1; I++)  {
					for (J = -1; J <= 1; J++)  {
						sumX = sumX + (int)((*(originalImage.data + X + I +
							(Y + J)*originalImage.cols)) * GX[I + 1][J + 1]);
					}
				}

				/*-------Y GRADIENT APPROXIMATION-------*/
				for (I = -1; I <= 1; I++)  {
					for (J = -1; J <= 1; J++)  {
						sumY = sumY + (int)((*(originalImage.data + X + I +
							(Y + J)*originalImage.cols)) * GY[I + 1][J + 1]);
					}
				}

				/*---GRADIENT MAGNITUDE APPROXIMATION (Myler p.218)----*/
				SUM = abs(sumX) + abs(sumY);
				cal = (float)(abs(sumX) * abs(sumX)) + (abs(sumY) * abs(sumY));
				SUM = sqrt(cal);
			}

			if (SUM>255) SUM = 255;
			if (SUM<0) SUM = 0;

			//*(originalImage.data + X + Y*originalImage.cols) = 255 - (unsigned char)(SUM);
			*(edgeImage.data + X + Y*originalImage.cols) = 255 - (unsigned char)(SUM);

		}


	}

	for (Y = 0; Y <= (originalImage.rows - 1); Y++)  {
		for (X = 0; X <= (originalImage.cols - 1); X++)  {
			*(originalImage.data + X + Y*originalImage.cols) = *(edgeImage.data + X + Y*originalImage.cols);
		}
	}
}



void functionSmoothing(sImage originalImage, sImage edgeImage)
{
	int Y, X, I, J, SUM, sumX, sumY;

	float cal;
	float                  GX[3][3];
	float                  GY[3][3];

	GX[0][0] = 1; GX[0][1] = 2; GX[0][2] = 1;
	GX[1][0] = 0; GX[1][1] = 0; GX[1][2] = 0;
	GX[2][0] = -1; GX[2][1] = -2; GX[2][2] = -1;

	for (Y = 0; Y <= (originalImage.rows - 1); Y++)  {
		for (X = 0; X <= (originalImage.cols - 1); X++)  {
			sumX = 0;
			sumY = 0;

			/* image boundaries */
			if (Y == 0 || Y == originalImage.rows - 1)
				SUM = 0;
			else if (X == 0 || X == originalImage.cols - 1)
				SUM = 0;

			/* Convolution starts here */
			else   {

				/*-------X GRADIENT APPROXIMATION------*/
				for (I = -1; I <= 1; I++)  {
					for (J = -1; J <= 1; J++)  {
						sumX = sumX + (int)((*(originalImage.data + X + I +
							(Y + J)*originalImage.cols)) * GX[I + 1][J + 1]);
					}
				}

				/*-------Y GRADIENT APPROXIMATION-------*/
				for (I = -1; I <= 1; I++)  {
					for (J = -1; J <= 1; J++)  {
						sumY = sumY + (int)((*(originalImage.data + X + I +
							(Y + J)*originalImage.cols)) * GY[I + 1][J + 1]);
					}
				}

				/*---GRADIENT MAGNITUDE APPROXIMATION (Myler p.218)----*/
				//SUM = abs(sumX) + abs(sumY);
				cal = (float)(abs(sumX) * abs(sumX)) + (abs(sumY) * abs(sumY));
				SUM = sqrt(cal);
			}

			if (SUM>255) SUM = 255;
			if (SUM<0) SUM = 0;

			//*(originalImage.data + X + Y*originalImage.cols) = 255 - (unsigned char)(SUM);
			*(edgeImage.data + X + Y*originalImage.cols) = 255 - (unsigned char)(SUM);

		}


	}
	for (Y = 0; Y <= (originalImage.rows - 1); Y++)  {
		for (X = 0; X <= (originalImage.cols - 1); X++)  {
			*(originalImage.data + X + Y*originalImage.cols) = *(edgeImage.data + X + Y*originalImage.cols);
		}
	}
}

