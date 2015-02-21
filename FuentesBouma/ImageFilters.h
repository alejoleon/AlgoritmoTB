#ifndef IMAGEFILTERS_H
#define IMAGEFILTERS_H

//Para manejo de imagenes.
#include "itkImage.h"
#include "itkImageSeriesReader.h"

//Para filtrado de imagenes con filtro mediana
#include "itkMedianImageFilter.h"

//Para binarizacion con crecimiento de regiones.
#include "itkConnectedThresholdImageFilter.h"
#include "itkCastImageFilter.h"
#include "itkCurvatureFlowImageFilter.h"

//Clases del proyecto
#include "BinaryFilters.h"


//Definicion del tipo de imagen.
typedef signed short    PixelType;
const unsigned int      DimensionIF = 3;
typedef itk::Image< PixelType, DimensionIF > ImageType;
typedef itk::ImageSeriesReader< ImageType > ReaderType;

//Definiciion de imagen Binaria
typedef unsigned char   PixelBinaryType;
typedef itk::Image<PixelBinaryType, DimensionIF> ImageBinaryType;

//Definicion de imagen para Crecimiento de regiones (WARNING del compilador)
typedef float PixelGrowingType;
typedef itk::Image<PixelGrowingType, DimensionIF> ImageGrowingType;

using namespace std;

class ImageFilters
{
private:
	
public:
	ImageFilters();
	~ImageFilters();

	void filtroMediana(ReaderType::Pointer reader, int radius,ImageType::Pointer &filterOutput);
	void filtroMediana(ImageType::Pointer image, int radius,ImageType::Pointer &filterOutput);
	void regionGrowing(ReaderType::Pointer reader,ImageBinaryType::Pointer &binLungs,float seeds[]) ;
	void regionGrowing(ImageType::Pointer image,ImageBinaryType::Pointer &binLungs,float seeds[]) ;


};

#endif // IMAGEFILTERS_H
