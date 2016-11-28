// Author: Sean Davis
#ifndef bloodH
#define bloodH

#include "bloodRunner.h"
#include "list.h"



///
/*
	this Vertex class represent a brain cell as a vertex
	in this class, it contains a list a vessels it can connect to.
*/
class Vertex
{
public:
	int ID;
	List edges;
  void insertVessel(Vessel vessel);
} ;


///
/*
	this Graph class represent a graph consist of brain cells and vessels.
	To represent the graph, we use the adjacency list.

*/
class Graph
{
	Vertex* vertex;
	Graph(Vessel vessels[], int vesselCount, int cellCount);
} ;


class Blood
{
	Graph* network;
	Graph* residualGraph;
	int* cellRanks;	// this is an array to store the rank of each cell.
	//int* sortedVertices;				// this is a sorted vertices array to help blood to gain a reference
	
public:
  Blood(Vessel vessels[], int vesselCount, int cellCount, int depth);
  int calcFlows(int fullFlows[], int emptyFlows[]);
}; // class Blood





#endif
