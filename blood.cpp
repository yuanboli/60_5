#include "blood.h"
#include "bloodRunner.h"

/*
	functionality: insert the vessel to vertex edges member.
*/
void Vertex::insertVessel(Vessel vessel)
{
	edges.insert(vessel.dest, vessel.capacity);
}//Vertex::insertVessel

///
/*
	constructor of Graph
	parameters:

	Vessel vessels[]: an array of vessels;
	int vesselCount: the number of vessels;
	int cellCount: the number of cells;

	functionality:
	to form the ajacency list representation of graph
*/
Graph::Graph(Vessel vessels[], int vesselCount, int cellCount)
{
	vertex = new Vertex[cellCount];

	for(int i = 0; i < vesselCount; i++)
	{
		vertex[vessels[i].src].insertVessel(vessels[i]);	
	}
}//Graph::Graph

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
	//network = new Graph(vessels, vesselCount, cellCount);
	// find rankes

} // Blood()


int Blood::calcFlows(int fullFlows[], int emptyFlows[])
{
  return 0;  // to avoid warning for now
} // calcFlows()
