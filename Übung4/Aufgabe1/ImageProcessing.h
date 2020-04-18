#ifndef ImageProcessingHeader
#define ImageProcessingHeader

#include <stdlib.h>

class ImageProcessing
{
private:
	int(*pictureData)[3], pictureLength, pictureWidth;

public:
	// Konstruktor
	ImageProcessing(int(*pictureData)[3], int length, int width) :pictureData(pictureData), pictureWidth(width), pictureLength(length)
	{

	};
	// Destruktor
	~ImageProcessing()
	{

	};

	// Methode - Bild in Graustufen konvertieren
	void convertToGray() {
		// Wandle die einzelnen Bildpunkte (Pixel) RGB in Graustufen um
		for (int i = 0; i < pictureLength * pictureWidth; i++) {
			// Die einzelnen Werte für Rot, Grün, Blau durch 3 teilen für einen Grauwert des jeweiligen Pixels
			int gray = ((this->pictureData)[i][0] + (this->pictureData)[i][1] + (this->pictureData)[i][2]) / 3;

			// Graustufe der einzelnen Pixel schreiben
			for (int j = 0; j < 3; j++) {
				this->pictureData[i][j] = gray;
			}
		}
	}

	// Methode - Kanten im Bild erkennen
	void edgeDetection() {
		int(*newGrayPicture)[3] = new int[pictureWidth * pictureLength][3];

		for (int x = 1; x < pictureWidth - 1; x++) {
			for (int i = 1 + (x * pictureLength); i < pictureLength - 1 + (x * pictureLength); i++) {
				for (int j = 0; j < 3; j++) {
					newGrayPicture[i][j] = -pictureData[i - pictureLength - 1][j] - pictureData[i - pictureLength][j] - pictureData[i - pictureLength][j] - pictureData[i - 1][j] + 8 * pictureData[i][j] - pictureData[i + 1][j] - pictureData[i + pictureLength - 1][j] - pictureData[i + pictureLength][j] - pictureData[i + pictureLength + 1][j];
				}
			}
		}

		for (int i = 0; i < pictureWidth * pictureLength; i++) {
			for (int j = 0; j < 3; j++) {
				if (newGrayPicture[i][j] > 0) {
					pictureData[i][j] = newGrayPicture[i][j];
				}
				else {
					pictureData[i][j] = 0;
				}

			}
		}
		delete[] newGrayPicture;
	}
};
#endif
