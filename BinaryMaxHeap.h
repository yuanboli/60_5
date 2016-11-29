#ifndef BinaryMaxHeapH
#define BinaryMaxHeapH
#include "blood.h"

class BinaryMaxHeap
{
public:
	explicit BinaryMaxHeap(int cap = 100)
	{currentSize = 0; capacity = cap; array = new Vertex[capacity];}

	void insert(Vertex x);
	bool isEmpty();
	Vertex deleteMax();

private:
	int currentSize;
	int capacity;
	Vertex* array;
	void percolateDown(int hole);


} ;


#endif
