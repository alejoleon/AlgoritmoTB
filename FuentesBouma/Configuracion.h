//Bibliotecas de lectura de archivos
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;


class Configuracion
{
private:
	//Ruta donde se encuentra la imagen a leer
	 string ruta_imagenIn;
	 string ruta_regionGrowing;


public:
	Configuracion();
	~Configuracion();
	string getRutaImgIn();
	string getRutaImgRegGrow();
	

};

