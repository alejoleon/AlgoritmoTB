#include "BoumaMethods.h"

/**
 * @brief Constructor por defecto.
 * @return Objeto de la clase BoumaMethods.
 */
BoumaMethods::BoumaMethods()
{
}

/**
 * @brief Destructor por defecto. 
 * @return 
 */
BoumaMethods::~BoumaMethods()
{
}

/**
 * @brief Se hace la funcion de procesamiento por filas para obtener las imagenes del mediastino y de la region de interes que se guardan en las variables pasadas por parametro.
 * @param lungs : Imagen de la segmentación de los pulmones.
 * @param interestRegion : Variable donde se guardará la segmentación de la región de interés.
 * @param mediastinum : Variable donde se guardará la segmentación del mediastino.
 * Ejemplo de Duplicar imagen: http://www.itk.org/Wiki/ITK/Examples/SimpleOperations/ImageDuplicator
 */

void BoumaMethods:: rowWiseMethod (ImageBinaryType::Pointer lungs, ImageBinaryType::Pointer &interestRegion, ImageBinaryType::Pointer &mediastinum) {
	
	//Copia de la imagen que sale del filtro de closing
	typedef itk::ImageDuplicator< ImageBinaryType > DuplicatorType;
	DuplicatorType::Pointer duplicator = DuplicatorType::New();
	DuplicatorType::Pointer duplicatorInteres = DuplicatorType::New();
	duplicator->SetInputImage(lungs);
	duplicatorInteres->SetInputImage(lungs);
	duplicator->Update();
	duplicatorInteres->Update();
	mediastinum = duplicator->GetOutput();
	interestRegion=duplicatorInteres->GetOutput();
	
	//Para dejar todos los vóxeles de ambas copias con valor de 0
	ImageBinaryType::SizeType size = mediastinum->GetLargestPossibleRegion().GetSize();
	ImageBinaryType::IndexType index = mediastinum->GetLargestPossibleRegion().GetIndex();
		
	for (int i=0 ; i< size[0] ; i++)
	{
		for (int j=0; j< size[1]; j++)
		{
			for (int k=0; k<size [2]; k++)
			{
				ImageBinaryType::IndexType currentIndex;
				currentIndex[0] = i;
				currentIndex[1] = j;
				currentIndex[2] = k;
				mediastinum->SetPixel(currentIndex,(char)(0));
				interestRegion->SetPixel(currentIndex,(char)(0));
			}	
		}
	}
	
	
	// Recorrer la imagen binaria de pulmones en forma de fila.
	// Encontrar el primer pixel que aparezca en cada fila recorriendo de izquierda a derecha y guardar esa coordenada
	// Encontrar el primer pixel que aparezca en cada fila recorriendo de derecha a izquierda y guardar esa coordenada
	// Poner en 1 toda la fila entre esas dos coordenadas
	
	
	ImageBinaryType::SizeType sizeBinLung = lungs->GetLargestPossibleRegion().GetSize();
	//Maximos y minimas coordenadas en cada fila
	int xmin=0;
	int xmax=0;
	bool minFound=false;
	bool maxFound=false;
	
	for (int i=0 ; i< sizeBinLung[2] ; i++)
	{
		for (int j=0; j< sizeBinLung[1]; j++)
		{
			for (int k=0; k<sizeBinLung [0]  && !minFound ; k++)
			{
				ImageBinaryType::IndexType currentIndexLeft;
				currentIndexLeft[0] = k;
				currentIndexLeft[1] = j;
				currentIndexLeft[2] = i;
				
				ImageBinaryType::PixelType currentValue = lungs->GetPixel(currentIndexLeft);
				
				if((int)currentValue==255){
					xmin=k;
					minFound=true;
				}
			}
			
			
			if(minFound){
				for (int m=sizeBinLung[0];m>=0 && !maxFound;m--){
										
					ImageBinaryType::IndexType currentIndexRight;
					currentIndexRight[0] = m;
					currentIndexRight[1] = j;
					currentIndexRight[2] = i;
					
					ImageBinaryType::PixelType currentValue = lungs->GetPixel(currentIndexRight);			
					
					if((int)currentValue==255){
						xmax=m;
						maxFound=true;
					}
				}
			}
				
			if(minFound && maxFound) {
				for (int e=xmin; e<xmax ; e++){
					ImageBinaryType::IndexType currentIndex;
					currentIndex[0] = e;
					currentIndex[1] = j;
					currentIndex[2] = i;
					ImageBinaryType::PixelType currentValueP = lungs->GetPixel(currentIndex);
					
					if((int)currentValueP!=255) {
						mediastinum->SetPixel(currentIndex,(char)(255));
						interestRegion->SetPixel(currentIndex,(char)(255));
					}
					else{
						interestRegion->SetPixel(currentIndex,(char)(255));
					}
					
					
				}
			}
			minFound=false;
			maxFound=false;
			xmin=0;
			xmax=0;
		}
	}
	//Para quitar regiones pequeñas que quizas no corresponden al mediastino.
	clearSmallRegions(mediastinum);
	
}

/**
 * @brief Se hace un procesamiento usando etiquetado de regiones con el fin de eliminar pequeñas regiones que pueden no pertenecer al mediastino.
 * @param mediastinum : Imagen de segmentación del mediastino.
 * Tomado de: http://www.itk.org/Wiki/ITK/Examples/ImageProcessing/LabelStatisticsImageFilter
 */
void BoumaMethods:: clearSmallRegions (ImageBinaryType::Pointer &mediastinum) {

	//Etiquetado para la imagen del mediastino con el fin de quitar las regiones muy pequeñas que quedaron en la imagen y que pueden no corresponder al mediastino.
	typedef itk::BinaryImageToLabelMapFilter<ImageBinaryType> BinaryImageToLabelMapFilterType;
	BinaryImageToLabelMapFilterType::Pointer binaryImageToLabelMapFilter = BinaryImageToLabelMapFilterType::New();
	binaryImageToLabelMapFilter->SetInput(mediastinum);
	binaryImageToLabelMapFilter->Update();
	
	typedef itk::LabelMapToLabelImageFilter<BinaryImageToLabelMapFilterType::OutputImageType, ImageBinaryType> LabelMapToLabelImageFilterType;
	LabelMapToLabelImageFilterType::Pointer labelMapToLabelImageFilter = LabelMapToLabelImageFilterType::New();
	labelMapToLabelImageFilter->SetInput(binaryImageToLabelMapFilter->GetOutput());
	labelMapToLabelImageFilter->Update();
	
	typedef itk::LabelStatisticsImageFilter< ImageBinaryType, ImageBinaryType > LabelStatisticsImageFilterType;
	LabelStatisticsImageFilterType::Pointer labelStatisticsImageFilter = LabelStatisticsImageFilterType::New();
	labelStatisticsImageFilter->SetLabelInput( labelMapToLabelImageFilter->GetOutput() );
	labelStatisticsImageFilter->SetInput(mediastinum);
	labelStatisticsImageFilter->Update();
 	
	unsigned int maximum=0;
	unsigned int maxValue=0;
	unsigned int pos=0;
	
	typedef LabelStatisticsImageFilterType::ValidLabelValuesContainerType ValidLabelValuesType;
	typedef LabelStatisticsImageFilterType::LabelPixelType                LabelPixelType; 
	 
	 //Se calcula la region mas grande que corresponde al mediastino
	for(ValidLabelValuesType::const_iterator vIt=labelStatisticsImageFilter->GetValidLabelValues().begin();
      vIt != labelStatisticsImageFilter->GetValidLabelValues().end();
      ++vIt)
    {
		if ( labelStatisticsImageFilter->HasLabel(*vIt) )
		{
			LabelPixelType labelValue = *vIt;
						
			//std::cout << "sum: " << labelStatisticsImageFilter->GetSum( labelValue ) << std::endl;
			//std::cout << "region: " << labelStatisticsImageFilter->GetRegion( labelValue ) << std::endl;
			
			if(labelStatisticsImageFilter->GetSum( labelValue )>maxValue){
				maxValue=labelStatisticsImageFilter->GetSum( labelValue );
				maximum=pos;
			}
		}
		pos++;
	}
	
	pos=0;
	
	//Para borrar regiones pequeñas y dejar solo el mediastino
	for(ValidLabelValuesType::const_iterator vIt=labelStatisticsImageFilter->GetValidLabelValues().begin();
      vIt != labelStatisticsImageFilter->GetValidLabelValues().end();
      ++vIt)
    {
		if ( labelStatisticsImageFilter->HasLabel(*vIt) )
		{
			LabelPixelType labelValue = *vIt;
						
			if(pos!=maximum && pos!=0 ){
							//std::cout << "sum: " << labelStatisticsImageFilter->GetSum( labelValue ) << std::endl;
							//std::cout << "region: " << labelStatisticsImageFilter->GetRegion( labelValue ) << std::endl;
						unsigned int ii,j,k;
						unsigned int sizex=labelStatisticsImageFilter->GetRegion( labelValue ).GetSize()[0];
						unsigned int sizey=labelStatisticsImageFilter->GetRegion( labelValue ).GetSize()[1];
						unsigned int sizez=labelStatisticsImageFilter->GetRegion( labelValue ).GetSize()[2];
						
							for (ii=labelStatisticsImageFilter->GetRegion( labelValue ).GetIndex()[0]; ii< (labelStatisticsImageFilter->GetRegion( labelValue ).GetIndex()[0])+sizex;ii++)
							{
								for (j=labelStatisticsImageFilter->GetRegion( labelValue ).GetIndex()[1]; j< (labelStatisticsImageFilter->GetRegion( labelValue ).GetIndex()[1])+sizey;j++)
								{
									for (k=labelStatisticsImageFilter->GetRegion( labelValue ).GetIndex()[2];k<labelStatisticsImageFilter->GetRegion( labelValue ).GetIndex()[2]+sizez; k++)
									{
										
										ImageBinaryType::IndexType currentIndex;
										currentIndex[0] = ii;
										currentIndex[1] = j;
										currentIndex[2] = k;
										ImageBinaryType::PixelType currentValue = mediastinum->GetPixel(currentIndex);
										mediastinum->SetPixel(currentIndex,char(0));
									}
								}
							}
			}
		}
		pos++;
	}	
}

