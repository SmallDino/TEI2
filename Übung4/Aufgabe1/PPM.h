#ifndef PPMHeader
#define PPMHeader

#include "DynamicContainer.h"
#include <iostream>

class PPM
{
private:
	// Variablen deklarieren
	FILE* inputFile, * outputFile;

	int(*pictureData)[3];
	int pictureWidth, pictureLength, pictureBrightness, index = 0;

	Container <char> header = Container<char>(2);

	// Methode - Länge des Bildes auslesen
	int readLength() {
		int length = 0;

		while (header[index] != ' ') {
			length *= 10;
			length += header[index] - '0';

			index++;
			header[index] = fgetc(inputFile);
		}

		return length;
	};

	// Methode - Breite des Bildes auslesen
	int readWidth() {
		int width = 0;
		index++;
		header[index] = fgetc(inputFile);

		while (header[index] != 0x0A) {
			width *= 10;
			width += header[index] - '0';

			index++;
			header[index] = fgetc(inputFile);
		}

		return width;
	};

	// Methode - Helligkeit des Bildes auslesen
	int readBrightness() {
		int brightness = 0;
		index++;
		header[index] = fgetc(inputFile);

		while (header[index] != 0x0A) {
			brightness *= 10;
			brightness += header[index] - '0';

			index++;
			header[index] = fgetc(inputFile);
		}

		return brightness;
	};

public:
	// Konstruktor
	PPM()
	{

	};

	// Destruktor
	~PPM()
	{
		delete[] pictureData;
	};

	// Methode - Bild einlesen
	void readFile(const char* fileName) {
		inputFile = fopen(fileName, "rb");

		if (inputFile != NULL) {
			header[index] = fgetc(inputFile);

			do {
				while (header[index] != 0x0A) {
					index++;
					header[index] = fgetc(inputFile);
				};
				index++;
				header[index] = fgetc(inputFile);

			} while (header[index] > '9' || header[index] < '0');

			pictureLength = readLength();
			pictureWidth = readWidth();
			pictureBrightness = readBrightness();

			this->pictureData = new int[pictureLength * pictureWidth][3];

			for (int i = 0; i < pictureLength * pictureWidth; i++) {
				pictureData[i][0] = fgetc(inputFile);
				pictureData[i][1] = fgetc(inputFile);
				pictureData[i][2] = fgetc(inputFile);
			}

			fclose(inputFile);
		}
	};

	// Methode - Bild schreiben
	void writeFile(const char* outName) {
		outputFile = fopen(outName, "wb");

		for (int i = 0; i <= index; i++) {
			fputc(header[i], outputFile);
		}

		for (int i = 0; i < pictureWidth * pictureLength; i++) {
			fputc(pictureData[i][0], outputFile);
			fputc(pictureData[i][1], outputFile);
			fputc(pictureData[i][2], outputFile);
		}

		fclose(outputFile);
	};

	// Bilddateien als Mehrdimensionales Array zurückgeben
	int(*getPictureData())[3]{
		return this->pictureData;
	};

	// Bildlänge zurückgeben
	int getLength() {
		return this->pictureLength;
	}

	// Bildbereite zurückgeben
	int getWidth() {
		return this->pictureWidth;
	}
};
#endif
