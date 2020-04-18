#include "PPM.h"
#include "ImageProcessing.h"

#include <iostream>

int main(int argc, char const *argv[])
{
	// PPM Objekt deklarieren
	PPM inputPicture;
	// Datei einlesen
	inputPicture.readFile("./Pictures/lena.ppm");
	// Dateiinformationen einlesen
	ImageProcessing process(inputPicture.getPictureData(), inputPicture.getLength(), inputPicture.getWidth());
	// Datei in ein Graustufenbild umwandeln
	process.convertToGray();
	// Ecken der Graubilddatei bearbeiten
	process.edgeDetection();
	// Graubild mit verdeutlichten Ecken in eine neue Datei schreiben
	inputPicture.writeFile("./Pictures/lena2.ppm");

	std::cout << "Konvertierung erfolgreich.";

	return 0;
}
