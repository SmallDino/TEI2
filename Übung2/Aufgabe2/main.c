#include <stdio.h>
#include <stdlib.h>

// Strukt deklarieren
struct Wav {
	int chunk_id;
	int chunk_size;
	int format;
	int subchunk1_id;
	int subchunk1_size;
	short audio_format;
	short num_channels;
	int sample_rate;
	int byte_rate;
	short block_align;
	short bits_per_sample;
	int subchunk2_id;
	int subchunk2_size;
};

// Union deklarieren
union ReadWav {
	struct Wav header;
	char bytes[44];
}wav_header;

// Methode um den Header der WAV Datei auszugeben
void printWavHeader(union ReadWav* that) {
	printf("Chunk Descriptor: %c%c%c%c\n", that->bytes[0], that->bytes[1], that->bytes[2], that->bytes[3]);
	printf("Chunk-Size: %d\n", that->header.chunk_size);
	printf("Format: %c%c%c%c\n", that->bytes[8], that->bytes[9], that->bytes[10], that->bytes[11]);
	printf("Subchunk1-ID: %c%c%c%c\n", that->bytes[12], that->bytes[13], that->bytes[14], that->bytes[15]);
	printf("Subchunk1-Size: %d\n", that->header.subchunk1_size);
	printf("Audio-Format: %d%d\n", that->bytes[19], that->bytes[20]);
	printf("Num-Channels: %d%d\n", that->bytes[21], that->bytes[22]);
	printf("Sample-Rate: %d\n", that->header.sample_rate);
	printf("Byte-Rate: %d\n", that->header.byte_rate);
	printf("Block-Align: %d%d\n", that->bytes[31], that->bytes[32]);
	printf("Bits-Per_Sample: %d%d\n", that->bytes[33], that->bytes[34]);
	printf("Subchunk2-ID: %c%c%c%c\n", that->bytes[35], that->bytes[36], that->bytes[37], that->bytes[38]);
	printf("Subchunk2-Size: %d\n", that->header.subchunk2_size);
};

int main(int argc, char const* argv[]) {
	// File öffnen
	FILE* wav_File = fopen("./SoundFiles/WaveFile.wav", "rb");
	// Union instanziieren
	if (wav_File != NULL) {
		// Überprüfen ob beide Header 44Bytes "groß" sind, wenn nicht dann handelt es sich womöglich um unterschiedliche Header und somit um unterschiedliche Dateien
		if (fread(wav_header.bytes, sizeof(char), sizeof(struct Wav), wav_File) != sizeof(struct Wav)) {
			fprintf(stderr, "FILE \"%s\" seems to be corrupted or wrong format\n", "./SoundFiles/WaveFile.wav");
			return EXIT_FAILURE;
		}
		// Header ausgeben
		printWavHeader(&wav_header);
	}
	else {
		printf("Datei kann im angegebenen Dateipfad nicht gefunden werden.\nKontrollieren Sie den Dateipfad.");
	}

	return 0;
}
