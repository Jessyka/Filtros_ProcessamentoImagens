#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "StructImage.h"

//typedef struct {int rows; int cols; unsigned char* data;} sImage;

void functionSobel(sImage originalImage, sImage edgeImage);
void functionSmoothing(sImage originalImage, sImage edgeImage);
