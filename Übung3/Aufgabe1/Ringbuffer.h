#ifndef readWAV
#define readWAV

#include "DynamicContainer.h"
// Aufgabe 2
template <class T>
class RingBuffer
{
private:
	int arraySize, currentPosition;
	Container<T>* ringbufferArray;

public:
	// Konstruktor
	RingBuffer(int bufferSize)
	{
		this->arraySize = bufferSize;
		ringbufferArray = new Container<T>(bufferSize);
	}

	// Operator [] überladen
	T& operator[](int i)
	{
		return (*ringbufferArray)[i % arraySize];
	}

	// Gibt die Größe des Ringbuffers zurück
	int getSize()
	{
		return this->arraySize;
	}

	// Füge einen neuen Wert dem Ringbuffer hinzu und überschreibt den letzten Wert.
	void put(T value)
	{
		(*ringbufferArray)[currentPosition % arraySize] = value;
		currentPosition = ++currentPosition % arraySize;
	}

	// Gibt den letzten Wert zurück
	T get()
	{
		return (*ringbufferArray)[currentPosition % arraySize];
	}
};

// Sample formen
union Sample {
	unsigned int integer;
	unsigned char characters[4];
};
#endif
