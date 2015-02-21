#ifndef BINARYFILTERS_H
#define BINARYFILTERS_H

//CPP standar
#include <iostream>
#include <stdlib.h>


//Filtro OR
#include "itkOrImageFilter.h"
//Filtro Closing
#include "itkBinaryMorphologicalClosingImageFilter.h"
#include "itkBinaryBallStructuringElement.h"


const unsigned int      DimensionBF = 3;
//Definiciion de imagen Binaria
typedef unsigned char   PixelBinaryType;
typedef itk::Image<PixelBinaryType, DimensionBF> ImageBinaryType;



using namespace std;

class BinaryFilters
{
public:
	BinaryFilters();
	~BinaryFilters();

	void orFunction(ImageBinaryType::Pointer input1,ImageBinaryType::Pointer input2,ImageBinaryType::Pointer &output);
	void closingFilter(ImageBinaryType::Pointer imageIn,ImageBinaryType::Pointer &imageOut,double radius);

};

#endif // BINARYFILTERS_H
