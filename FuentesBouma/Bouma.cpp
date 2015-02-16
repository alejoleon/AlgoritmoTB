
//Bibliotecas estandar de C++

#include <iostream>

#include <stdlib.h>



//Clases del proyecto:

//Para leer propiedades:

#include "Configuracion.h"
#include "DICOMProperties.h"

using namespace std;


int main()

{
	//Se lee el archivo de configuracion
	Configuracion config;
	
	//Se obtiene la ruta donde esta la imagen a la que se le va a hacer el procesamiento.
	string ruta = config.getRuta();
	
	//Se crea un objeto que obtiene las propiedades que se usaran del header de la imagen DICOM
	DICOMProperties* prop = new DICOMProperties(ruta);
	cout<<"valor Pixel :  "<<prop->GetPixelValue()<<endl;
	//system("PAUSE");

	return 0 ;

}


