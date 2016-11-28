#ifndef BinaryHeapH
#define BinaryHeaph
#include "blood.h"

class BinaryHeap
{
public:
	explicit BinaryHeap(int cap = 100)
	{currentSize = 0; capacity = cap; array = new Vertex[capacity];}

	void insert(Vertex x);
	bool isEmpty();
	Vertex deleteMin();

private:
	int currentSize;
	int capacity;
	Vertex* array;
	void percolateDown(int hole);


} ;


#endif
