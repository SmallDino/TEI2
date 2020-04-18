// BEI MELDUNG _CRT_SECURE_NO_WARNINGS: Menüleiste Projekt -> C/C++ -> Präprozessor -> Präprozessordefinitionen -> Bearbeiten -> _CRT_SECURE_NO_WARNINGS in eine neue Zeile einfügen

#include <stdio.h>
#include <string.h>
#include <iostream>
#include "DynamicContainer.h"
#include "Ringbuffer.h"

// http://soundfile.sapp.org/doc/WaveFormat/

int main(int argc, char const* argv[]) {
	//Aufgabe 2
	// Samples initialisieren
	Sample sampleWav, sampleBuffered;
	// Variablen deklarieren
	int indexInContainer = 0;
	Container<unsigned char> wavfile(1);
	// Original Datei öffnen
	FILE* inputFile = fopen("./Soundfiles/originalWav.wav", "rb");

	if (inputFile != NULL)
	{
		std::cout << "Datei wird konvertiert. Bitte warten.\n";
		while (!feof(inputFile))
		{
			wavfile[indexInContainer] = fgetc(inputFile);
			//std::cout << wavfile[i++];
			indexInContainer++;
		}
	}
	else {
		std::cout << "Keine Datei im Dateipfad gefunden. Kontrollieren Sie den Dateipfad.";
	}
	fclose(inputFile);
	
	// Aufgabe 3
	RingBuffer<unsigned int> buffer(20000); // Je höher der Wert, desto größer ist die Verzögerung (Echo) des Songs
	// Den kompletten Buffer mit 0 initialisieren
	for (int i = 0; i < buffer.getSize(); i++)
	{
		buffer[i] = 0;
	}

	// Initialisiert mit 44, da das Headerfile 44 Byte groß ist. Pro Durchlauf 4 Bytes in Sample schreiben, danach in den Container
	for (int i = 44; i < wavfile.getSize() - 4; i += 4)
	{
		sampleBuffered.integer = buffer.get();

		sampleWav.characters[0] = wavfile[i];
		sampleWav.characters[1] = wavfile[i + 1];
		sampleWav.characters[2] = wavfile[i + 2];
		sampleWav.characters[3] = wavfile[i + 3];

		buffer.put(sampleWav.integer);

		// Samples aufaddieren
		sampleWav.integer += sampleBuffered.integer;
		sampleWav.integer += sampleBuffered.integer;

		// Werte in den Container schreiben
		wavfile[i] = sampleWav.characters[0];
		wavfile[i + 1] = sampleWav.characters[1];
		wavfile[i + 2] = sampleWav.characters[2];
		wavfile[i + 3] = sampleWav.characters[3];
	}
	// In ein neues File schreiben.
	FILE* outputFile = fopen("./Soundfiles/modifiedWav.wav", "wb");
	// Dateien vom Container in die Zieldatei schreiben
	for (int i = 0; i < wavfile.getSize(); i++)
	{
		fputc(wavfile[i], outputFile);
	}
	fclose(outputFile);
	std::cout << "Konvertiertung erfolgreich.\n\n"; 
	std::cout << ">>> Programm beendet.\n";	
	return 0;
}
