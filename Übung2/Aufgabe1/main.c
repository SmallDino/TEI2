// BEI MELDUNG _CRT_SECURE_NO_WARNINGS: Menüleiste Projekt -> C/C++ -> Präprozessor -> Präprozessordefinitionen -> Bearbeiten -> _CRT_SECURE_NO_WARNINGS in eine neue Zeile einfügen

#include <stdio.h>
#include <stdlib.h>

// WICHTIG: Programm ist nur ausgelegt für binäre PPMs
int main(int argc, char** argv)
{
	// Variablen deklarieren
	int width, height, max_colour;
	// Files öffnen
	FILE* convertedFile = fopen("./Pictures/lenaConverted.ppm", "wb");
	FILE* originalFile = fopen("./Pictures/lena.ppm", "rb");

	if (originalFile != NULL) {

		// Kopf der eingelesenen Datei abfragen & speichern
		fscanf(originalFile, "P6\n %d %d %d", &width, &height, &max_colour);

		// Kopf in die neue Datei schreiben
		fprintf(convertedFile, "P6\n%d %d\n%d\n", width, height, max_colour);

		// Schleife zum schreiben "grauer" einzelner Pixel in die neue Datei

		for (int j = 0; j < width; ++j) {
			for (int i = 0; i < height; ++i) {
				unsigned char color[3];
				unsigned int grey = 0;
				// Pixel besteht aus 3 x 255 (RGB, binär) in einer binären Datei
				// Diese 3 eingelesenen Werte wird im Color[]-Array gespeichert:  [0] = rot, [1] = grün, [2] = blau
				fread(color, 1, 3, originalFile);

				grey += 299u * color[0];  // rot	R
				grey += 586u * color[1];  // grün	G
				grey += 114u * color[2];  // blau	B
				grey /= 1000;

				// Grauwerte zuweisen (RGB)
				color[0] = grey, color[1] = grey, color[2] = grey;
				// Grauwerte schreiben
				fwrite(color, 1, 3, convertedFile);
			}
		}
		printf("Konvertrieren erfolgreich.");
		// File schließen
		fclose(originalFile);
	}
	else {
		printf("Einzulesende Datei kann nicht gefunden werden.\nKontrollieren sie den Dateipfad.");
	}
	// File schließen
	fclose(convertedFile);

	return 0;
}
