#ifndef BINARYFILTERS_H
#define BINARYFILTERS_H

//Filtro OR
#include "itkOrImageFilter.h"

const unsigned int      DimensionBF = 3;
//Definiciion de imagen Binaria
typedef unsigned char   PixelBinaryType;
typedef itk::Image<PixelBinaryType, DimensionBF> ImageBinaryType;


class BinaryFilters
{
public:
	BinaryFilters();
	~BinaryFilters();

	void orFunction(ImageBinaryType::Pointer input1,ImageBinaryType::Pointer input2,ImageBinaryType::Pointer &output);
};

#endif // BINARYFILTERS_H
