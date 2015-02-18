#include "DICOMProperties.h"

/**
*Constructor por defecto
*/
DICOMProperties::DICOMProperties()
{
}

/**
 * @brief Contructor con el parametro de la dirección o path donde se encuentra la imagen DICOM de entrada.
 * @param direccion
 * @return Objeto de la clase DICOMProperties
 */

DICOMProperties::DICOMProperties(string path)
{
	this->path=path;
	
	// Se declara el tipo de imagen seleccionando un tipo de pixel y de dimension
	typedef signed short PixelType;
	const unsigned int   Dimension = 3;
	typedef itk::Image< PixelType, Dimension > ImageType;
	typedef itk::ImageSeriesReader<ImageType> ReaderType;
	
	ReaderType::Pointer reader = ReaderType::New();

	typedef itk::GDCMImageIO       ImageIOType;
	ImageIOType::Pointer dicomIO = ImageIOType::New();

	reader->SetImageIO(dicomIO);

	typedef itk::GDCMSeriesFileNames     NamesGeneratorType;
	NamesGeneratorType::Pointer nameGenerator = NamesGeneratorType::New();
	nameGenerator->SetInputDirectory(path);

	typedef std::vector<std::string>    FileNamesContainer;
	FileNamesContainer fileNames = nameGenerator->GetInputFileNames();

	reader->SetFileNames(fileNames);

	try
	{
		reader->Update();
	}
	catch (itk::ExceptionObject &ex)
	{
		std::cout << ex << std::endl;
		return;
	}

	typedef itk::MetaDataDictionary   DictionaryType;
	const  DictionaryType & dictionary = dicomIO->GetMetaDataDictionary();
	typedef itk::MetaDataObject< std::string > MetaDataStringType;

	DictionaryType::ConstIterator itr = dictionary.Begin();
	//Tag correspondiente al Valor de espaciado del pixel en milimetros.
	string entryId = "0028|0030";

	//Se definen dos iteradores para el diccionario
	DictionaryType::ConstIterator tagItr = dictionary.Find( entryId );
	DictionaryType::ConstIterator end = dictionary.End();

	//Si no se encuentra el TAG entonces se deja el valor del pixel en -1
	if( tagItr == end )
    {
		std::cerr << "Tag " << entryId;
		std::cerr << " not found in the DICOM header" << std::endl;
		this->pixelValue=-1;
    }
	else{
		//Se obtiene el valor del tag deseado.
		MetaDataStringType::ConstPointer entryvalue =
		dynamic_cast<const MetaDataStringType *>( tagItr->second.GetPointer() );

		//Si es posible leer el apuntador de entryvalue, entonces se obtiene el valor del pixel.
		//
		 if( entryvalue )
		{
			string tagvalue = entryvalue->GetMetaDataObjectValue();
			this->pixelValue=atof(tagvalue.c_str());
		}

		else
		{
			cerr << "Entry was not of string type" << std::endl;
			this->pixelValue = -1;
		}
	}
	
}

/**
 * @brief Destructor de la case PropiedadesDICOM
 * @return 
 */
DICOMProperties::~DICOMProperties()
{
}

/**
 * @brief Se imprimen por consola todas las propiedades que existan en el encabezado de las imagenes. 
 * Ejemplo en : https://github.com/InsightSoftwareConsortium/ITK/blob/master/Examples/IO/DicomSeriesReadPrintTags.cxx
 */
void DICOMProperties::printMetadata()
{
	
	string direccion=this->path;
	
	// Se declara el tipo de imagen seleccionando un tipo de pixel y de dimension
	typedef signed short PixelType;
	const unsigned int   Dimension = 3;
	typedef itk::Image< PixelType, Dimension > ImageType;
	typedef itk::ImageSeriesReader<ImageType> ReaderType;
	
	ReaderType::Pointer reader = ReaderType::New();

	typedef itk::GDCMImageIO       ImageIOType;
	ImageIOType::Pointer dicomIO = ImageIOType::New();

	reader->SetImageIO(dicomIO);

	typedef itk::GDCMSeriesFileNames     NamesGeneratorType;
	NamesGeneratorType::Pointer nameGenerator = NamesGeneratorType::New();
	nameGenerator->SetInputDirectory(direccion);

	typedef std::vector<std::string>    FileNamesContainer;
	FileNamesContainer fileNames = nameGenerator->GetInputFileNames();

	reader->SetFileNames(fileNames);

	try
	{
		reader->Update();
	}
	catch (itk::ExceptionObject &ex)
	{
		std::cout << ex << std::endl;
		return;
	}

	typedef itk::MetaDataDictionary   DictionaryType;
	const  DictionaryType & dictionary = dicomIO->GetMetaDataDictionary();
	typedef itk::MetaDataObject< std::string > MetaDataStringType;

	DictionaryType::ConstIterator itr = dictionary.Begin();
	DictionaryType::ConstIterator end = dictionary.End();


	cout << endl << endl << "---VALORES DEL METADATA---" << endl;
	while (itr != end)
	{
		itk::MetaDataObjectBase::Pointer  entry = itr->second;
		MetaDataStringType::Pointer entryvalue =
			dynamic_cast<MetaDataStringType *>(entry.GetPointer());
		if (entryvalue)
		{
			std::string tagkey = itr->first;
			std::string tagvalue = entryvalue->GetMetaDataObjectValue();
			std::cout << tagkey << " = " << tagvalue << std::endl;
		}
		++itr;
	}
}

/**
 * @brief Agrega el valor de la ruta donde esta la imagen DICOM que pasa por parametro
 * @param Path donde se encuentra la imagen.
 */
void DICOMProperties::SetPath(const string& path)
{
	this->path = path;
}

/**
 * @brief retorna el path donde se encuentra el directorio con las imagenes DICOM 
 * @return Path donde esta la imagen DICOM.
 */
const string& DICOMProperties::GetPath() const
{
	return this->path;
}

/**
 * @brief Establece el valor en mm al que corresponde un pixel 
 * @param Valor en mm de lo que deberia corresponder un pixel.
 */
void DICOMProperties:: SetPixelValue(double pixelValue)
{
	this->pixelValue = pixelValue;
}

/**
 * @brief Retorna el valor en mm correspondiente a un pixel. 
 * @return Valor en mm correspondiente a un pixel.
 */
double DICOMProperties:: GetPixelValue() const
{
	return pixelValue;
}





