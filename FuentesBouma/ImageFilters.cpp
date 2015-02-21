#include "ImageFilters.h"
/**
 * @brief Constructor por defecto
 * @return Objeto de la clase ImageFilters
 */
ImageFilters::ImageFilters()
{
}

/**
 * @brief Destructor por defecto.
 * @return 
 */
ImageFilters::~ImageFilters()
{
}

/**
 * @brief Hace un filtro mediada de la imagen (seriesReader) que es pasa por parametro. Se guarda la salida del filtro en la variable pasada por referencia.
 * @param reader :Apuntador a la imagen (seriesReader) que se va a filtrar.
 * @param radius :Radio con el cual se hará el filtro mediada.
 * Ejemplo tomado de: http://itk.org/Wiki/ITK/Examples/Smoothing/MedianImageFilter
 */
void ImageFilters:: filtroMediana(ReaderType::Pointer reader, int radio,ImageType::Pointer &filterOutput){
	
	typedef itk::MedianImageFilter<ImageType, ImageType > FilterType;
	FilterType::Pointer medianFilter = FilterType::New();
	FilterType::InputSizeType radiusInic;
	
	radiusInic.Fill(radio);
	
	medianFilter->SetRadius(radiusInic);
	medianFilter->SetInput( reader->GetOutput() );
	medianFilter->Update();
	filterOutput=medianFilter->GetOutput();
}

/**
 * @brief Hace un filtro mediada de la imagen que es pasa por parametro. Se guarda la salida del filtro en la variable pasada por referencia.
 * @param image :Apuntador a la imagen que se va a filtrar.
 * @param radius :Radio con el cual se hará el filtro mediada.
 * @param filterOutput: Apuntador pasado por referencia en el que se guarda la salida del filtro.
 * Ejemplo tomado de: http://itk.org/Wiki/ITK/Examples/Smoothing/MedianImageFilter
 */
void ImageFilters:: filtroMediana(ImageType::Pointer image, int radius,ImageType::Pointer &filterOutput){
	
	typedef itk::MedianImageFilter<ImageType, ImageType > FilterType;
	FilterType::Pointer medianFilter = FilterType::New();
	FilterType::InputSizeType radiusInic;
	
	radiusInic.Fill(radius);
	
	medianFilter->SetRadius(radiusInic);
	medianFilter->SetInput( image );
	medianFilter->Update();
	filterOutput=medianFilter->GetOutput();
}

/**
 * @brief Realiza una binarización usando crecimiento de regiones en una imagen a partir de dos semillas pasadas por parametro.
 * @param image: imagen de tipo Reader
 * @param binLungs: variable pasada por parametro donde se guardará el resultado de la binarización con crecimiento de regiones.
 * @param seeds: Arreglo que contiene las coordenadas de las dos semillas (una de cada pulmón)	 
 * Ejemplo de binarización http://www.itk.org/Doxygen45/html/Segmentation_2ConnectedThresholdImageFilter_8cxx-example.html
 * Ejemplo de Casteo de imagenes: http://www.itk.org/Wiki/ITK/Examples/ImageProcessing/CastImageFilter
 */
void ImageFilters::regionGrowing(ReaderType::Pointer reader,ImageBinaryType::Pointer &binLungs, float seeds[]) {

	typedef itk::CastImageFilter< ImageType, ImageBinaryType > CastingFilterType;	
	CastingFilterType::Pointer caster = CastingFilterType::New();
	CastingFilterType::Pointer caster2 = CastingFilterType::New();
	
	typedef itk::CurvatureFlowImageFilter< ImageType, ImageGrowingType > CurvatureFlowImageFilterType;
	CurvatureFlowImageFilterType::Pointer smoothing = CurvatureFlowImageFilterType::New();
	CurvatureFlowImageFilterType::Pointer smoothing2 = CurvatureFlowImageFilterType::New();
	
	typedef itk::ConnectedThresholdImageFilter< ImageGrowingType,ImageType > ConnectedFilterType;
	ConnectedFilterType::Pointer connectedThreshold = ConnectedFilterType::New();
	ConnectedFilterType::Pointer connectedThreshold2 = ConnectedFilterType::New();
	
	smoothing->SetInput( reader->GetOutput() );
	smoothing2->SetInput( reader->GetOutput() );
	connectedThreshold->SetInput( smoothing->GetOutput());
	connectedThreshold2->SetInput( smoothing2->GetOutput() );
	caster->SetInput( connectedThreshold->GetOutput() );
	caster2->SetInput( connectedThreshold2->GetOutput() );
	
	smoothing->SetNumberOfIterations( 5 );
	smoothing2->SetNumberOfIterations( 5 );
	//smoothing->SetTimeStep( 0.125 );
	smoothing->SetTimeStep( 0.025 );
	smoothing2->SetTimeStep( 0.025 );
	
	const PixelType lowerThreshold = -2000;
	const PixelType upperThreshold = -500;
	
	connectedThreshold->SetLower(  lowerThreshold  );
	connectedThreshold->SetUpper(  upperThreshold  );
	
	connectedThreshold2->SetLower(  lowerThreshold  );
	connectedThreshold2->SetUpper(  upperThreshold  );
	
	//connectedThreshold->SetReplaceValue( 32767 );
	connectedThreshold->SetReplaceValue( 32767 );
	connectedThreshold2->SetReplaceValue( 32767 );
	
	ImageType::IndexType leftLungSeed;
	leftLungSeed[0] = (signed short)seeds[0];
	leftLungSeed[1] = (signed short)seeds[1];
	leftLungSeed[2] = (signed short)seeds[2];
	
	ImageType::IndexType rightLungSeed;
	rightLungSeed[0] = (signed short)seeds[3];
	rightLungSeed[1] = (signed short)seeds[4];
	rightLungSeed[2] = (signed short)seeds[5];
	
	connectedThreshold->SetSeed( leftLungSeed );
	connectedThreshold2->SetSeed( rightLungSeed );

	//Operacion or
	BinaryFilters* orFunc=new BinaryFilters();
	orFunc->orFunction(caster->GetOutput(),caster2->GetOutput(),binLungs);
}

/**
 * @brief Realiza una binarización usando crecimiento de regiones en una imagen a partir de dos semillas pasadas por parametro.
 * @param image: imagen a la que se le hará el crecimiento de regiones.
 * @param binLungs: variable pasada por parametro donde se guardará el resultado de la binarización con crecimiento de regiones.
 * @param seeds: Arreglo que contiene las coordenadas de las dos semillas (una de cada pulmón)	 
 * Ejemplo de binarización http://www.itk.org/Doxygen45/html/Segmentation_2ConnectedThresholdImageFilter_8cxx-example.html
 * Ejemplo de Casteo de imagenes: http://www.itk.org/Wiki/ITK/Examples/ImageProcessing/CastImageFilter
 */
void ImageFilters::regionGrowing(ImageType::Pointer image,ImageBinaryType::Pointer &binLungs, float seeds[]) {

	typedef itk::CastImageFilter< ImageType, ImageBinaryType > CastingFilterType;	
	CastingFilterType::Pointer caster = CastingFilterType::New();
	CastingFilterType::Pointer caster2 = CastingFilterType::New();
	
	typedef itk::CurvatureFlowImageFilter< ImageType, ImageGrowingType > CurvatureFlowImageFilterType;
	CurvatureFlowImageFilterType::Pointer smoothing = CurvatureFlowImageFilterType::New();
	CurvatureFlowImageFilterType::Pointer smoothing2 = CurvatureFlowImageFilterType::New();
	
	typedef itk::ConnectedThresholdImageFilter< ImageGrowingType,ImageType > ConnectedFilterType;
	ConnectedFilterType::Pointer connectedThreshold = ConnectedFilterType::New();
	ConnectedFilterType::Pointer connectedThreshold2 = ConnectedFilterType::New();
	
	smoothing->SetInput( image );
	smoothing2->SetInput( image );
	connectedThreshold->SetInput( smoothing->GetOutput());
	connectedThreshold2->SetInput( smoothing2->GetOutput() );
	caster->SetInput( connectedThreshold->GetOutput() );
	caster2->SetInput( connectedThreshold2->GetOutput() );
	
	smoothing->SetNumberOfIterations( 5 );
	smoothing2->SetNumberOfIterations( 5 );
	//smoothing->SetTimeStep( 0.125 );
	smoothing->SetTimeStep( 0.025 );
	smoothing2->SetTimeStep( 0.025 );
	
	const PixelType lowerThreshold = -2000;
	const PixelType upperThreshold = -500;
	
	connectedThreshold->SetLower(  lowerThreshold  );
	connectedThreshold->SetUpper(  upperThreshold  );
	
	connectedThreshold2->SetLower(  lowerThreshold  );
	connectedThreshold2->SetUpper(  upperThreshold  );
	
	//connectedThreshold->SetReplaceValue( 32767 );
	connectedThreshold->SetReplaceValue( 32767 );
	connectedThreshold2->SetReplaceValue( 32767 );
	
	ImageType::IndexType leftLungSeed;
	leftLungSeed[0] = (signed short)seeds[0];
	leftLungSeed[1] = (signed short)seeds[1];
	leftLungSeed[2] = (signed short)seeds[2];
	
	ImageType::IndexType rightLungSeed;
	rightLungSeed[0] = (signed short)seeds[3];
	rightLungSeed[1] = (signed short)seeds[4];
	rightLungSeed[2] = (signed short)seeds[5];
	
	connectedThreshold->SetSeed( leftLungSeed );
	connectedThreshold2->SetSeed( rightLungSeed );

	//Operacion or
	BinaryFilters* orFunc=new BinaryFilters();
	orFunc->orFunction(caster->GetOutput(),caster2->GetOutput(),binLungs);
}