#include "Configuracion.h"

Configuracion::Configuracion()
{
	ifstream entrada;
	stringstream linea;

	entrada.open("C:\\Users\\Alejandro\\Dropbox\\Universidad\\TrabajoGrado2015\\9_CodigoFuenteProyecto\\AlgoritmoTB\\FuentesBouma\\ArchivoConfig.txt", ios::in);
	if (!entrada)
	{
		cout << "No se pudo cargar archivo"<<endl;
	}
	else
	{
		//cout << "Si se leyo" << endl;

		char cad[200];
		string cad1;
		stringstream parametro;
		
		entrada.getline(cad, 200, '\n');//se lee el titulo
		do
		{
			entrada.getline(cad, 200, '\n');//se lee la propiedad
			cad1 = cad;
			
			parametro.clear(); //Se hace para borrar lo que pueda haber en el flujo
			parametro << cad1; //Se convierte a SS para poder usar los tokens

			parametro.getline(cad, 200, ' '); //Se lee subtitulo
			
			if ((string)cad=="DirImgEnt:")
			{
				parametro.getline(cad, 200, ' ');//Se lee el valor del parametro
				this->ruta_imagen = cad;
			}
		} while (!entrada.eof());
	}
}


Configuracion::~Configuracion()
{
}


string Configuracion:: getRuta()
{
	return this->ruta_imagen;
}