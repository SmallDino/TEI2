#include <stdio.h>
#include <stdlib.h>

#define ARRAY_LENGTH 4

int main(int argc, char** argv)
{
	union {
		unsigned int x;
		unsigned char y[ARRAY_LENGTH];
	}number;
	// Int-Wert zuweisen
	number.x = 0x01020304;

	for (int i = 0; i < ARRAY_LENGTH; i++) {
		printf("%d\n", number.y[i]);
	}
	// Ausgabe Endian
	number.y[0] > number.y[3] ? printf("Little Endian") : printf("Big Endian");

	return 0;
}
