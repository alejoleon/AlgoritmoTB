//Bibliotecas estandar de C++
#include <iostream>
#include <stdlib.h>

//Para manejo de imagenes.
#include "itkImage.h"

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
//Para realizar operaciones propias del algoritmo
#include "BoumaMethods.h"
//Algunas operaciones útiles de procesamiento de imágenes
#include "ImageProcessingUtils.h"


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

void imprimirImagen(ReaderType::Pointer reader);

int main()

{
	//Se lee el archivo de configuracion
	Configuracion config;
	
	//Se obtiene la ruta donde esta la imagen a la que se le va a hacer el procesamiento.
	string rutaImgIn = config.getRutaImgIn();
	string rutaImgMedian = config.getRutaMedian();
	string rutaImgRegGrow = config.getRutaImgRegGrow();
	string rutaImgRegGrowClosing = config.getRutaImgRegGrowClosing();
	string rutaImgMediastinum = config.getRutaMediastinum();
	string rutaImgInterestReg= config.getRutaInterestRegion();
	
	//Se crea un objeto que obtiene las propiedades que se usaran del header de la imagen DICOM
	DICOMProperties* prop = new DICOMProperties(rutaImgIn);
	double tamPixel = prop->GetPixelValue();
	//prop->printMetadata();
	//cout<<"valor Pixel :  "<<tamPixel<<endl;
	
	//-->Se leen las imagen de entrada (readers)
	DICOMIOManage* imagen=new DICOMIOManage();
	ReaderType::Pointer readerImIn = imagen->readInputImage(rutaImgIn);
	//ReaderType::Pointer readerImMedian = imagen->readInputImage(rutaImgMedian);
	//ReaderBinaryType::Pointer readerRegGrow = imagen->readInputImageBin(rutaImgRegGrow);
	//ReaderBinaryType::Pointer readerRegGrowClosing = imagen->readInputImageBin(rutaImgRegGrowClosing);  
	//ReaderBinaryType::Pointer readerMediastinum = imagen->readInputImageBin(rutaImgMediastinum);
	ReaderBinaryType::Pointer readerInterestRegion = imagen->readInputImageBin(rutaImgInterestReg);
	
	
	//Variables donde se guardaran las imagenes:
	ImageType::Pointer imageIn = ImageType::New();
	//ImageType::Pointer imagenfiltradaMediana = ImageType::New();
	//ImageBinaryType::Pointer lungs = ImageBinaryType::New();
	//ImageBinaryType::Pointer lungsAfterClosing = ImageBinaryType::New();
	//ImageBinaryType::Pointer mediastinum = ImageBinaryType::New();
	ImageBinaryType::Pointer interestRegion = ImageBinaryType::New();
	
	//Se le da valores a las imagenes
	imageIn = readerImIn->GetOutput();
	//imagenfiltradaMediana = readerImMedian->GetOutput();
	//lungs = readerRegGrow->GetOutput();
	//lungsAfterClosing = readerRegGrowClosing->GetOutput();
	//mediastinum = readerMediastinum->GetOutput();
	interestRegion = readerInterestRegion->GetOutput();
	
	//Objetos necesarios.
	ImageFilters* filters = new ImageFilters();
	BinaryFilters* binFilters = new BinaryFilters();
	BoumaMethods* boumaMet = new BoumaMethods();
	ImageProcessingUtils* utils=new ImageProcessingUtils();
	
	
	//imprimirImagen(readerImIn);
	/*
	// 0. Filtro mediana
	// Create and setup a reader
	filters->filtroMediana(readerImIn->GetOutput(),1,imagenfiltradaMediana);
	//-->Se crean las imagenes de salida
	imagen->SetNameOutputFiles("OutMedian");
	imagen->writeDicomFile(imagenfiltradaMediana,rutaImgMedian);
	*/
	
	/*
	//1. Binarizacion por crecimiento de regiones
	//Semillas del pulmon derecho e izquierdo respectivamente
	float seeds[6];
	seeds[0] = 82.8057;//302;
	seeds[1] = 256.587;//167;
	seeds[2] = 140;//3.749;
	seeds[3] = 330.085;//109.684;
	seeds[4] = 201.07;//224.723;
	seeds[5] = 140;//2.49;
	filters->regionGrowing(imagenfiltradaMediana,lungs,seeds);
	//-->Se crean las imagenes de salida
	imagen->SetNameOutputFiles("OutRegGrow");
	imagen->writeDicomFile(lungs,rutaImgRegGrow);
	  */ 
	  
	  /*
	//1.1 Filtro Closing con 2.4 mm de radio
	double radius = (double)2.4/tamPixel;
	binFilters->closingFilter(lungs,lungsAfterClosing,radius);
	//-->Se crean las imagenes de salida
	imagen->SetNameOutputFiles("OutRegGrowClosing");
	imagen->writeDicomFile(lungsAfterClosing,rutaImgRegGrowClosing);
	*/
	
	/*
	//2.Operacion de row-wise para obtener el mediastino y la region de interes.
	boumaMet->rowWiseMethod(lungsAfterClosing,interestRegion, mediastinum);
	//-->Se crean las imagenes de salida
	imagen->SetNameOutputFiles("OutMediastinum");
	imagen->writeDicomFile(mediastinum,rutaImgMediastinum);
	imagen->SetNameOutputFiles("OutInterestReg");
	imagen->writeDicomFile(interestRegion,rutaImgInterestReg);
	*/
	
	/*
	//Para mostrar en VTK
	VTKVisualization* vtkVis= new VTKVisualization();
	vtkVis->SetDir1(rutaImgMedian);
	vtkVis->SetDir2(rutaImgInterestReg);
	//vtkVis->readImages(readerImin->GetOutput());
	//vtkVis->readImages(readerRegGrow->GetOutput());
	
	vtkVis->readImages(imagenfiltradaMediana, interestRegion);
	*/

	//system("PAUSE");
	return 0 ;
}


void imprimirImagen(ReaderType::Pointer reader){
	ImageBinaryType::SizeType sizeLung = reader->GetOutput()->GetLargestPossibleRegion().GetSize();
	
	signed short max=0;
	signed short min=10000;
	
	
	for (int i=0 ; i< sizeLung[0] ; i++)
	{
		for (int j=0; j< sizeLung[1]; j++)
		{
			for (int k=0; k<sizeLung [2]; k++)
			{
				ImageType::IndexType currentIndexLung;
				currentIndexLung[0] = i;
				currentIndexLung[1] = j;
				currentIndexLung[2] = k; 
				ImageType::PixelType currentValueOut = reader->GetOutput()->GetPixel(currentIndexLung);
				//cout<<(int)currentValueOut<<",";
				if (currentValueOut<min){
					min=currentValueOut;
				}
				if (currentValueOut>max){
					max=currentValueOut;
				}
			}	
		}
	}
	
	cout<<" MAXIM "<<max<<endl;
	cout<<" MINIM "<<min<<endl;
}