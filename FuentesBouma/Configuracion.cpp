#include "Configuracion.h"

/**
 * @brief Lee el archivo de configuración y agrega las propiedades al objeto de la clase Configuracion
 * @return Objeto de la clase Configuracion
 */
Configuracion::Configuracion()
{
	ifstream entrada;
	stringstream linea;

	//entrada.open("C:\\Users\\Alejandro\\Dropbox\\Universidad\\TrabajoGrado2015\\9_CodigoFuenteProyecto\\AlgoritmoTB\\FuentesBouma\\ArchivoConfig.txt", ios::in);
	entrada.open("../AlgoritmoTB/FuentesBouma/ArchivoConfig.txt", ios::in);//Se lee la ruta relativa del archivo de configuracion
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
			
			if ((string)cad=="DirImgIn:")
			{
				parametro.getline(cad, 200, ' ');//Se lee el valor del parametro
				this->ruta_imagenIn = cad;
				
			}else if ((string)cad=="DirImgMedianOut:") {
	
				parametro.getline(cad, 200, ' ');//Se lee el valor del parametro
				this->ruta_MedianFilter=cad;
				
			}else if ((string)cad=="DirImgRegGrowOut:") {
				
				parametro.getline(cad, 200, ' ');//Se lee el valor del parametro
				this->ruta_regionGrowing=cad;
				
			}else if ((string)cad=="DirImgRegGrowClosingOut:") {
				
				parametro.getline(cad, 200, ' ');//Se lee el valor del parametro
				this->ruta_regGrowClosing=cad;
				
			}else if ((string)cad=="DirImgMediastinumOut:") {
				
				parametro.getline(cad, 200, ' ');//Se lee el valor del parametro
				this->ruta_mediastinum=cad;
				
			}else if ((string)cad=="DirImgInterestRegOut:") {
				
				parametro.getline(cad, 200, ' ');//Se lee el valor del parametro
				this->ruta_interestRegion=cad;
				
			}
			
			
			
		} while (!entrada.eof());
	}
}

/**
 * @brief Destructor de la clase Configuracion
 * @return 
 */
Configuracion::~Configuracion()
{
	
}

/**
 * @brief Retorna la dirección o path donde se encuentra la imagen de entrada.
 * @return Ruta donde esta la imagen de entrada.
 */
string Configuracion:: getRutaImgIn()
{
	return this->ruta_imagenIn;
}

/**
 * @brief Retorna la dirección o path donde se encuentra la imagen con filtro de mediana (salida).
 * @return Ruta donde esta la imagen de salida.
 */
string Configuracion:: getRutaMedian()
{
	return this->ruta_MedianFilter;
}


/**
 * @brief Retorna la direccion o path donde se encuentra la imagen que ya fue pasada por el crecimiento de regiones.
 * @return Ruta donde esta la imagen de regionGrowing.
 */
string Configuracion:: getRutaImgRegGrow()
{
	return this->ruta_regionGrowing;
}

/**
 * @brief Retorna la direccion o path donde se encuentra la imagen que ya fue pasada por el crecimiento de regiones y un closing.
 * @return Ruta donde esta la imagen de regionGrowing luego de haberse hecho un Closing.
 */
string Configuracion:: getRutaImgRegGrowClosing()
{
	return this->ruta_regGrowClosing;
}

/**
 * @brief Retorna la direccion o path donde se encuentra la imagen correspondiente al mediastino.
 * @return Ruta donde esta la imagen del mediastino.
 */
string Configuracion:: getRutaMediastinum()
{
	return this->ruta_mediastinum;
}

/**
 * @brief Retorna la direccion o path donde se encuentra la imagen correspondiente a la region de interes.
 * @return Ruta donde esta la imagen de la region de interes.
 */
string Configuracion:: getRutaInterestRegion()
{
	return this->ruta_interestRegion;
}