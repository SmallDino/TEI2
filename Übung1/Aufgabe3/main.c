#include <stdio.h>
#include <stdlib.h>

#define NUMBER_OF_ELEMENTS 100

int main(int argc, char** argv) {
	int integerArray = malloc(sizeof(int) * NUMBER_OF_ELEMENTS), position = 0;
	int *pointer = NULL;
	pointer = integerArray;

	if (integerArray != NULL) {
		printf("Speicher wurde reserviert\n");
		while (position < NUMBER_OF_ELEMENTS) {
			*pointer = rand() % 1000; // Zahlen zwischen 0 - 999
			printf("%d. Position im Array hat den Wert: %d\n", position + 1, *pointer);

			position++, pointer++;
		}
	}
	else {
		printf("Es wurde kein Speicher reserviert.\n");
	}
	free(integerArray);
	printf(">>> Programm beendet");
	return 0;
}
