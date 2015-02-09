//Bibliotecas estandar de C++
#include <iostream>
#include <stdlib.h>

//Clases del proyecto:
//Para leer propiedades:
#include "Configuracion.h"

using namespace std;

int main()
{
	Configuracion config;
	cout << "se leyo la ruta: " << config.getRuta() << endl;
	system("PAUSE");
	return 0 ;
}

