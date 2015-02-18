#ifndef DICOMPROPERTIES_H
#define DICOMPROPERTIES_H

#include <string>
#include <vector>

// Para leer imagenes dicom
#include "itkGDCMImageIO.h"
#include "itkGDCMSeriesFileNames.h"
#include "itkImageSeriesReader.h"
#include "itkImageSeriesWriter.h"

#include "itkImage.h"
#include "itkMetaDataObject.h"

using namespace std;

class DICOMProperties
{
private:
    double pixelValue;
    string path;


public:
    DICOMProperties();
    DICOMProperties(string direccion);
    ~DICOMProperties();

    void printMetadata();

	void SetPath(const string& path);
	const string& GetPath() const;
	
    void SetPixelValue(double pixelValue);
    double GetPixelValue() const;
	
	
};

#endif //DICOMPROPERTIES_H