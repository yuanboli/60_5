#include "blood.h"
#include "bloodRunner.h"
#include "BinaryHeap.h"

/*
	functionality: insert the vessel to vertex edges member.
*/
void Vertex::insertVessel(Vessel vessel)
{
	edges->insert(vessel.dest, vessel.capacity);
}//Vertex::insertVessel


///
/*
	operator < for Vertex
*/
bool Vertex::operator<(Vertex rhs)
{
	if(score < rhs.score)
		return true;
	else
		return false;
}
///
/*
	copy constructor
*/
void Vertex::operator=(Vertex rhs)
{
	rank = rhs.rank;
	ID = rhs.ID;
	*edges = *(rhs.edges);
	known = rhs.known;
	prev = rhs.prev;
	score = rhs.score;
}

///
/*
	constructor of Graph
	parameters:

	Vessel vessels[]: an array of vessels;
	int vesselCount: the number of vessels;
	int cellCount: the number of cells;

	functionality:
	to form the ajacency list representation of graph
	also initialize the Vertex IDs
*/
Graph::Graph(Vessel vessels[], int vesselCount, int cellCount)
{
	vertex = new Vertex[cellCount];
	vertexCount = cellCount;

	//to initialize IDs
	for(int i = 0; i < cellCount; i++)
		vertex[i].ID = i;

	for(int i = 0; i < vesselCount; i++)
	{
		vertex[vessels[i].src].insertVessel(vessels[i]);	
	}
}//Graph::Graph


///
/*
	Graph::calRank
	no parameter

	functionality:
	use a Dijkstra-like algorithm to calculate the rank of each vertex.

*/
void Graph::calRank()
{
	//init
	for(int i = 0; i < vertexCount; i++)
	{
		vertex[i].known = false;
		vertex[i].prev = -1;// represent not a vertex
		vertex[i].rank = 99999;
	}
	//Dijkstra cal
	BinaryHeap* heap = new BinaryHeap;
	vertex[0].rank = 0;
	heap->insert(vertex[0]);
	while(!heap->isEmpty())
	{
		Vertex v = Vertex();
		v = heap->deleteMin();
		vertex[v.ID].known = true;
		ListNode* node = v.edges->root;
		while(node != NULL)
		{
			if(!vertex[node->dest].known)
			{
				if(v.rank + 1 < vertex[node->dest].rank)
				{
					vertex[node->dest].rank = v.rank + 1;
					vertex[node->dest].prev = v.ID;
					heap->insert(vertex[node->dest]);
				}
			}
			node = node->next;
		}
	}
	delete heap;
}//Graph::calRank

///
/*
	constructor of Blood
	parameters:

	Vessel vessels[], an array of vessels
	int vesselCount, the number of vessels
	int cellCount, the number of cells
	int depth, the shortest path depth of the graph.

	functionality:
	This constructor will form a graph of the brain cell system
	find the rank of every cell
*/
Blood::Blood(Vessel vessels[], int vesselCount, int cellCount, int depth)
{
	// form graphes
	network = new Graph(vessels, vesselCount, cellCount);
	
	// calculate rankes
	network->calRank();

} // Blood()


int Blood::calcFlows(int fullFlows[], int emptyFlows[])
{
  return 0;  // to avoid warning for now
} // calcFlows()
