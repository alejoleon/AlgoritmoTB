//Bibliotecas estandar de C++
#include <iostream>
#include <stdlib.h>

//Para manejo de imagenes.
#include "itkImage.h"
//#include "itkImageFileReader.h"


//Clases del proyecto:
//Para leer propiedades:
#include "Configuracion.h"
//Para leer datos del Header de las imagenes DICOM
#include "DICOMProperties.h"
//Para leer y escribir imagenes DICOM
#include "DICOMIOManage.h"
//Para hacer todos los filtros
#include "ImageFilters.h"
//Para visualizar con VTK
#include "VTKVisualization.h"


using namespace std;


//Algunos typedef:Asignar un nombre alternativo a tipos existentes, a menudo cuando su declaración normal es aparatosa, potencialmente confusa o probablemente variable de una implementación a otra.
//Para la imagen de entrada que es en escala de grises.
typedef signed short    PixelType;
const unsigned int      DimensionB= 3;
typedef itk::Image< PixelType, DimensionB> ImageType;
typedef itk::ImageSeriesReader< ImageType > ReaderType;

//Imagen de entrada binaria
typedef unsigned char   PixelBinaryType;
typedef itk::Image<PixelBinaryType, DimensionB> ImageBinaryType;
typedef itk::ImageSeriesReader< ImageBinaryType > ReaderBinaryType;


void imprimirImagen(ReaderBinaryType::Pointer reader);

int main()

{
	//Se lee el archivo de configuracion
	Configuracion config;
	
	//Se obtiene la ruta donde esta la imagen a la que se le va a hacer el procesamiento.
	string rutaImgIn = config.getRutaImgIn();
	string rutaImgRegGrow = config.getRutaImgRegGrow();
	
	//Se crea un objeto que obtiene las propiedades que se usaran del header de la imagen DICOM
	DICOMProperties* prop = new DICOMProperties(rutaImgIn);
	cout<<"valor Pixel :  "<<prop->GetPixelValue()<<endl;
	
	//-->Se lee la imagen de entrada.
	DICOMIOManage* imagen=new DICOMIOManage();
	ReaderType::Pointer readerImin = imagen->readInputImage(rutaImgIn);
	ReaderBinaryType::Pointer readerRegGrow = imagen->readInputImageBin(rutaImgRegGrow); 

	
	/*
	// 0. Filtro mediana
	// Create and setup a reader
	ImageFilters* filters=new ImageFilters();
	//ImageType::Pointer imagenfiltradaMediana= ImageType::New();
	//filters->filtroMediana(reader->GetOutput(),1,imagenfiltradaMediana);
	
	 
	 
	//1. Binarizacion por crecimiento de regiones
	ImageBinaryType::Pointer pulmones=ImageBinaryType::New();
	
	//Semillas del pulmon derecho e izquierdo respectivamente
	float seeds[6];
	seeds[0] = 82.8057;//302;
	seeds[1] = 256.587;//167;
	seeds[2] = 0;//3.749;140
	seeds[3] = 330.085;//109.684;
	seeds[4] = 201.07;//224.723;
	seeds[5] = 0;//2.49;140
	
	filters->regionGrowing(readerImin,pulmones,seeds);
	//-->Se crean las imagenes de salida
	
	imagen->SetNameOutputFiles("salida");
	imagen->writeDicomFile(pulmones,"/Users/AlejoMac/Documents/AlgoritmosTG/ImagenesTG/Outputs");
	*/
	
	//cout<<"ruta "<<config.getRutaImgRegGrow();
	
	
	//Para mostrar en VTK
	VTKVisualization* vtkVis= new VTKVisualization();
	vtkVis->SetDir1(config.getRutaImgIn());
	vtkVis->SetDir2(config.getRutaImgRegGrow());
	//vtkVis->readImages(readerImin->GetOutput());
	//vtkVis->readImages(readerRegGrow->GetOutput());
	vtkVis->readImages(readerImin->GetOutput(), readerRegGrow->GetOutput());
	

	//system("PAUSE");
	return 0 ;
}


void imprimirImagen(ReaderBinaryType::Pointer reader){
	ImageBinaryType::SizeType sizeLung = reader->GetOutput()->GetLargestPossibleRegion().GetSize();
	for (int i=0 ; i< sizeLung[0] ; i++)
	{
		for (int j=0; j< sizeLung[1]; j++)
		{
			for (int k=0; k<sizeLung [2]; k++)
			{
				ImageBinaryType::IndexType currentIndexLung;
				currentIndexLung[0] = i;
				currentIndexLung[1] = j;
				currentIndexLung[2] = k; 
				ImageBinaryType::PixelType currentValueOut = reader->GetOutput()->GetPixel(currentIndexLung);
				cout<<(int)currentValueOut<<",";
			}	
		}
	}
}