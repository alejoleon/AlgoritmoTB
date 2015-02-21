#ifndef BOUMAMETHODS_H
#define BOUMAMETHODS_H

//CPP standar
#include <iostream>
#include <stdlib.h>

using namespace std;









//Para duplicar una imagen.
#include "itkImageDuplicator.h"

//Para hacer las funciones de etiquetado de regiones.
#include "itkImageRegionIterator.h"
#include "itkBinaryImageToLabelMapFilter.h"
#include "itkLabelMapToLabelImageFilter.h"
#include "itkLabelStatisticsImageFilter.h"

//Definicion del tipo de imagen.
typedef signed short    PixelType;
const unsigned int      DimensionBM = 3;
typedef itk::Image< PixelType, DimensionBM > ImageType;

//Definicion de imagen binaria
typedef unsigned char   PixelBinaryType;
typedef itk::Image<PixelBinaryType, DimensionBM> ImageBinaryType;

class BoumaMethods
{
public:
	BoumaMethods();
	~BoumaMethods();
	void rowWiseMethod (ImageBinaryType::Pointer lungs, ImageBinaryType::Pointer &interestRegion, ImageBinaryType::Pointer &mediastinum);
	void clearSmallRegions (ImageBinaryType::Pointer &mediastinum);
};

#endif // BOUMAMETHODS_H
