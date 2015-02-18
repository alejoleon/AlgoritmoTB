#ifndef VTKVISUALIZATION_H
#define VTKVISUALIZATION_H

#include <string>
#include <sstream>

// some standard vtk headers
#include <vtkSmartPointer.h>
#include <vtkObjectFactory.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkActor.h>
// headers needed for this example
#include <vtkImageViewer2.h>
#include <vtkDICOMImageReader.h>
#include <vtkInteractorStyleImage.h>
#include <vtkActor2D.h>
#include <vtkTextProperty.h>
#include <vtkTextMapper.h>

// Ejemplo de onLeftButtomDown
#include <vtkAbstractPicker.h>
#include <vtkRendererCollection.h>

// Para manejo de imagenes.
#include "itkImage.h"

// Definición del tipo de imagen.
typedef signed short PixelType;
const unsigned int DimensionV = 3;
typedef itk::Image<PixelType, DimensionV> ImageType;

// Definición de Imagen de entrada binaria
typedef unsigned char PixelBinaryType;
typedef itk::Image<PixelBinaryType, DimensionV> ImageBinaryType;

using namespace std;

class VTKVisualization
{
private:
    string dir1;
    string dir2;

public:
    VTKVisualization();
    ~VTKVisualization();

	void SetDir1(const string& dir1);
	void SetDir2(const string& dir2);
	const string& GetDir1() const;
	const string& GetDir2() const;
	void readImages(ImageType::Pointer img1,ImageBinaryType::Pointer img2);
	void readImages(ImageType::Pointer img1);
	void readImages(ImageBinaryType::Pointer img2);
};

#endif // VTKVISUALIZATION_H
