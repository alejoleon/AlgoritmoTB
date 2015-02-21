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
	 string ruta_MedianFilter;
	 string ruta_regionGrowing;
	 string ruta_regGrowClosing;
	 string ruta_mediastinum;
	 string ruta_interestRegion;
	 


public:
	Configuracion();
	~Configuracion();
	string getRutaImgIn();
	string getRutaMedian();
	string getRutaImgRegGrow();
	string getRutaImgRegGrowClosing();
	string getRutaMediastinum();
	string getRutaInterestRegion();

};

