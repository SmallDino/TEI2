#ifndef arrayContainer
#define arrayContainer

// Aufgabe 1
template <typename T>
class Container {
private:
	// Variablen deklarieren
	int arraySize;
	T* dynamicArray;

public:
	// Konstruktor
	Container(int arraySize) {
		this->dynamicArray = new T[arraySize];
		this->arraySize = arraySize;
	}
	// Destruktor
	~Container() {
		delete[] this->dynamicArray;
	}
	// Gibt die Größe des Arrays zurück
	int getSize() {
		return this->arraySize;
	}
	// Operator [] überladen
	T& operator[](int index) {
		// Erweitert das vorhandene Array nur dann, wenn auf einen Index zugegriffen wird, der im Originalen Array nicht vorhanden ist
		if (index >= this->arraySize) {
			int newSize = (index * 2) + 1;
			T* newDynamicArray = new T[newSize];
			// Daten kopieren
			for (int i = 0; i < this->arraySize; i++) {
				newDynamicArray[i] = dynamicArray[i];
			}
			// Daten aktualisieren
			this->arraySize = newSize;
			// Altes Array freigeben
			delete[] this->dynamicArray;
			// Neues Array übertragen und als Standard festlegen
			this->dynamicArray = newDynamicArray;
		}
		return dynamicArray[index];
	}
};
#endif
