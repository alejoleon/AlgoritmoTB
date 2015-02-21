#include "DICOMIOManage.h"

/**
 * @brief Constructor por defecto
 * @return Objeto de la clase DICOMIOManage
 */
DICOMIOManage::DICOMIOManage()
{
	this->nameOutputFiles = "";
	this->inputSize = 0;
	this->reader = ReaderType::New();
	this->imgRegionGrow = ReaderBinaryType::New();	
}

/**
 * @brief Destructor por defecto. 
 * @return 
 */
DICOMIOManage::~DICOMIOManage()
{
}

/**
 * @brief Lee una imagen DICOM Binaria y la guarda en una variable para trabajar con ITK
 * @param inputDirectory Directorio donde están las imágenes de entrada.
 * @return Imagen para trabajar con ITK
 * Ejemplo en : http://www.itk.org/Doxygen/html/Examples_2IO_2DicomSeriesReadSeriesWrite_8cxx-example.html
 */
ReaderBinaryType::Pointer DICOMIOManage:: readInputImageBin(string inputDirectory){
	
	ImageIOType::Pointer gdcmIO = ImageIOType::New();
	NamesGeneratorType::Pointer namesGenerator = NamesGeneratorType::New();
	
	namesGenerator->SetInputDirectory( inputDirectory );
	const ReaderBinaryType::FileNamesContainer & filenames = namesGenerator->GetInputFileNames();
	
	//Guarda el numero de archivos que hay en el directorio de entrada.
	this->inputSize=(int)filenames.size();
	
	//Para imprimir el nombre de los archivos de DICOM
	/*
	const unsigned int numberOfFileNames =  filenames.size();
	cout << numberOfFileNames << endl;
	
	for(unsigned int fni = 0; fni < numberOfFileNames; ++fni)
    {
		cout << "filename # " << fni << " = ";
		cout << filenames[fni] << std::endl;
    }
	*/
	
	imgRegionGrow->SetImageIO( gdcmIO );
	imgRegionGrow->SetFileNames( filenames );
	
	try
    {
		imgRegionGrow->Update();
    }
	catch (itk::ExceptionObject &excp)
    {
		std::cerr << "Exception thrown while writing the image" << std::endl;
		std::cerr << excp << std::endl;
		return NULL;
    }
	return imgRegionGrow;
}


/**
 * @brief Lee una imagen DICOM y la guarda en una variable para trabajar con ITK
 * @param inputDirectory Directorio donde están las imágenes de entrada.
 * @return Imagen para trabajar con ITK
 * Ejemplo en : http://www.itk.org/Doxygen/html/Examples_2IO_2DicomSeriesReadSeriesWrite_8cxx-example.html
 */
ReaderType::Pointer DICOMIOManage:: readInputImage(string inputDirectory){
	
	ImageIOType::Pointer gdcmIO = ImageIOType::New();
	NamesGeneratorType::Pointer namesGenerator = NamesGeneratorType::New();
	
	namesGenerator->SetInputDirectory( inputDirectory );
	const ReaderType::FileNamesContainer & filenames = namesGenerator->GetInputFileNames();
	
	//Guarda el numero de archivos que hay en el directorio de entrada.
	this->inputSize=(int)filenames.size();
	
	//Para imprimir el nombre de los archivos de DICOM
	/*
	const unsigned int numberOfFileNames =  filenames.size();
	cout << numberOfFileNames << endl;
	
	for(unsigned int fni = 0; fni < numberOfFileNames; ++fni)
    {
		cout << "filename # " << fni << " = ";
		cout << filenames[fni] << std::endl;
    }
	*/
	
	reader->SetImageIO( gdcmIO );
	reader->SetFileNames( filenames );
	
	try
    {
		reader->Update();
    }
	catch (itk::ExceptionObject &excp)
    {
		std::cerr << "Exception thrown while writing the image" << std::endl;
		std::cerr << excp << std::endl;
		return NULL;
    }
	return reader;
}

//DEPRECATED
/*
void DICOMIOManage:: writeDicomFile (ImageType::Pointer image,string outputPath){
	//Nombre del directorio de salida
	
	
	const char * outputDirectory = outputPath.c_str();
	
	//Se debe verificar que el directorio exista, de lo contrario se crea si no existe aun.
	itksys::SystemTools::MakeDirectory( outputDirectory );
	
	//Tipo de imagen que se va a escribir
	typedef signed short    OutputPixelType;
	const unsigned int      OutputDimension = 2;
	
	typedef itk::Image< OutputPixelType, OutputDimension >    Image2DType;
	typedef itk::ImageSeriesWriter<ImageType, Image2DType >  SeriesWriterType;

	SeriesWriterType::Pointer seriesWriter = SeriesWriterType::New();
	
	seriesWriter->SetInput( image);
	ImageIOType::Pointer gdcmIO = ImageIOType::New();
	seriesWriter->SetImageIO( gdcmIO );
	
	NamesGeneratorType::Pointer namesGenerator = NamesGeneratorType::New();
	namesGenerator->SetOutputDirectory( outputDirectory );
	seriesWriter->SetFileNames( namesGenerator->GetOutputFileNames() );
	
	seriesWriter->SetMetaDataDictionaryArray(reader->GetMetaDataDictionaryArray() );
	
	 try
    {
		seriesWriter->Update();
    }
  catch( itk::ExceptionObject & excp )
    {
		cerr << "Exception thrown while writing the series " << std::endl;
		cerr << excp << std::endl;
		return ;
    }
}
*/
/**
 * @brief Escribe las imagenes de salida
 * @param image : imagen que se guardara en formato DICOM
 * @param outputPath : Directorio donde se guardará la salida.
 * Ejemplo en : http://itk.org/Wiki/ITK/Examples/DICOM/ResampleDICOM
 */
void DICOMIOManage:: writeDicomFile (ImageType::Pointer image,string outputPath){

	string name="";
	
	if ((this->nameOutputFiles=="")) {
		name="Img";
	}
	else {
		name=this->nameOutputFiles;
	}
	
	typedef signed short    OutputPixelType;
	const unsigned int      OutputDimension = 2;
	
	typedef itk::Image< OutputPixelType, OutputDimension >    Image2DType;
	typedef itk::ImageSeriesWriter<ImageType, Image2DType >  SeriesWriterType;

	
	const char * outputDirectory = outputPath.c_str();	
	itksys::SystemTools::MakeDirectory( outputDirectory);
	
	// Generate the file names
	OutputNamesGeneratorType::Pointer outputNames = OutputNamesGeneratorType::New();
	string seriesFormat(outputDirectory);
	seriesFormat = seriesFormat + "/" + name+"%d.dcm";
	outputNames->SetSeriesFormat (seriesFormat.c_str());
	outputNames->SetStartIndex (1);
	outputNames->SetEndIndex (this->GetInputSize());
 
	SeriesWriterType::Pointer seriesWriter = SeriesWriterType::New();
	//seriesWriter->SetInput( image->GetOutput() );
	seriesWriter->SetInput(image);
	ImageIOType::Pointer gdcmIO = ImageIOType::New();
    seriesWriter->SetImageIO( gdcmIO );
    seriesWriter->SetFileNames( outputNames->GetFileNames() );
    seriesWriter->SetMetaDataDictionaryArray( reader->GetMetaDataDictionaryArray() );
  try
    {
		seriesWriter->Update();
    }
  catch( itk::ExceptionObject & excp )
    {
		std::cerr << "Exception thrown while writing the series " << std::endl;
		std::cerr << excp << std::endl;
		return;
    }
}

/**
 * @brief Escribe las imagenes de salida
 * @param image : imagen que se guardara en formato DICOM
 * @param outputPath : Directorio donde se guardará la salida.
 * Ejemplo en : http://itk.org/Wiki/ITK/Examples/DICOM/ResampleDICOM
 */
 
void DICOMIOManage:: writeDicomFile (ImageBinaryType::Pointer image,string outputPath){

	string name="";
	
	if ((this->nameOutputFiles=="")) {
		name="Img";
	}
	else {
		name=this->nameOutputFiles;
	}
	
	typedef signed short    OutputPixelType;
	const unsigned int      OutputDimension = 2;
	
	typedef itk::Image< OutputPixelType, OutputDimension >    Image2DType;
	typedef itk::ImageSeriesWriter<ImageBinaryType, Image2DType >  SeriesWriterType;

	const char * outputDirectory = outputPath.c_str();	
	itksys::SystemTools::MakeDirectory( outputDirectory);
 
	// Generate the file names
	OutputNamesGeneratorType::Pointer outputNames = OutputNamesGeneratorType::New();
	string seriesFormat(outputDirectory);
	seriesFormat = seriesFormat + "/" + name+"%d.dcm";
	outputNames->SetSeriesFormat (seriesFormat.c_str());
	outputNames->SetStartIndex (1);
	outputNames->SetEndIndex (this->GetInputSize());
 
	SeriesWriterType::Pointer seriesWriter = SeriesWriterType::New();
	//seriesWriter->SetInput( image->GetOutput() );
	seriesWriter->SetInput(image);
	ImageIOType::Pointer gdcmIO = ImageIOType::New();
    seriesWriter->SetImageIO( gdcmIO );
    seriesWriter->SetFileNames( outputNames->GetFileNames() );
    seriesWriter->SetMetaDataDictionaryArray( reader->GetMetaDataDictionaryArray() );
  try
    {		
		seriesWriter->Update();
    }
  catch( itk::ExceptionObject & excp )
    {
		std::cerr << "Exception thrown while writing the series " << std::endl;
		std::cerr << excp << std::endl;
		return;
    }
}


/**
 * @brief Define el nombre que tendran los archivos de salida. 
 * @param nameOutputFiles : Nombre que se le dará a los archivos de salida.
 */
void DICOMIOManage:: SetNameOutputFiles(const string& nameOutputFiles)
{
	this->nameOutputFiles = nameOutputFiles;
}
 
/**
 * @brief Retorna el nombre que tienen los archivos de salida
 * @return Nombre de los archivos de salida
 */   
const string& DICOMIOManage::GetNameOutputFiles() const
{
	return nameOutputFiles;
}
/**
 * @brief Define la cantidad de imagenes que habrá a la salida.
 * @param inputSize : Cantidad de imagenes
 */
 void DICOMIOManage::SetInputSize(int inputSize)
{
	this->inputSize = inputSize;
}
/**
 * @brief Retorna la cantidad de imágenes que debe haber a la salida.
 * @return Cantidad de imágenes a la salida.
 */
int DICOMIOManage::GetInputSize() const
{
	return inputSize;
}