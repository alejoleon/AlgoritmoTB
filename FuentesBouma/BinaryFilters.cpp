#include "BinaryFilters.h"

BinaryFilters::BinaryFilters()
{
}

BinaryFilters::~BinaryFilters()
{
}

/**
 * @brief Realiza la operacion Binaria OR de dos imágenes binarias
 * @param input1 Imagen Binaria
 * @param input2 Imagen Binaria
 * @param output : Resultado de la función OR de las dos imágenes Binarias (Pasado por parámetro)
 * Ejemplo de : http://itk.org/Wiki/ITK/Examples/ImageProcessing/OrImageFilter
 */
void BinaryFilters::orFunction(ImageBinaryType::Pointer input1,ImageBinaryType::Pointer input2,ImageBinaryType::Pointer &output){
	
	typedef itk::OrImageFilter <ImageBinaryType> OrImageFilterType;
	OrImageFilterType::Pointer orFilter = OrImageFilterType::New();
	
	orFilter->SetInput(0, input1);
	orFilter->SetInput(1, input2);
	orFilter->Update();
	
	output=orFilter->GetOutput();

}