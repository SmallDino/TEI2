#include <iostream>

const int ARRAY_LENGTH = 100;

int main(int argc, char** argv[]) {
	int* integerArray = new int[ARRAY_LENGTH];
	int* pointer;
	pointer = integerArray;

	for (int i = 0; i < ARRAY_LENGTH; i++) {
		*pointer = rand() % 1000;

		std::cout << i+1 << ". Zahl im Array: " << *pointer << "\n";

		pointer++;
	}

	delete[] integerArray;
	
	std::cout << ">>> Programm beendet";
}
