#include "blood.h"
#include "bloodRunner.h"
#include "BinaryHeap.h"
#include "BinaryMaxHeap.h"

/*
	functionality: insert the vessel to vertex edges member.
*/
void Vertex::insertVessel(int vesselID, Vessel vessel)
{
	edges->insert(vesselID, vessel.dest, vessel.capacity);
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
	fed = rhs.fed;
	fedNumber = rhs.fedNumber;
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
	also initialize the Vertex IDs and feds.
*/
Graph::Graph(Vessel vessels[], int vesselCount, int cellCount)
{
	vertex = new Vertex[cellCount];
	vertexCount = cellCount;

	//to initialize IDs, feds
	for(int i = 0; i < cellCount; i++)
	{
		vertex[i].fed = false;
		vertex[i].ID = i;
	}

	
	vertex[vessels[vesselCount - 1].src].insertVessel(vesselCount - 1, vessels[vesselCount - 1]);	

	for(int i = 0; i < vesselCount - 1; i++)
	{
		vertex[vessels[i].src].insertVessel(i, vessels[i]);	
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

Graph::Graph(Graph* rhs)
{
	vertexCount = rhs->vertexCount;
	vertex = new Vertex[vertexCount];

	for(int i = 0; i < vertexCount; i++)
		vertex[i] = rhs->vertex[i];
}
///
/*
		copy constructor for Graph
*/
void Graph::operator=(Graph rhs)
{
	vertexCount = rhs.vertexCount;
	vertex = new Vertex[vertexCount];

	for(int i = 0; i < vertexCount; i++)
	{
		vertex[i] = rhs.vertex[i];
	}
}//Graph::operator=

	
	
///add reverse edge for residualGraph
void Graph::addReverseEdge(int flow, int newEdgeStart, int newEdgeEnd)
{
	Vessel v = Vessel();
	v.src = newEdgeStart;
	v.dest = newEdgeEnd;
	v.capacity = flow;
	vertex[newEdgeStart].insertVessel(-1, v);

}//Graph::addReverseEdge




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

	//care about residualGraph;
	residualGraph = NULL;
	vesselC = vesselCount;
	totalFed = 0;

} // Blood()

///
/*
		This function should find the flow for a pulse;
*/
int Blood::calcFlows(int fullFlows[], int emptyFlows[])
{
	for(int i = 0; i < vesselC; i++)
	{
		fullFlows[i] = emptyFlows[i] = 0;
	}
	//init residualGraph vertex.
	residualGraph = new Graph(network);//need copy constructor;

	//a loop to find the flow for each time
		//find a max flow
	while(newFlow(fullFlows, emptyFlows))
	{
	
	}
		//update information
		//form residual graph

  return totalFed;  // to avoid warning for now
} // calcFlows()


///
/*
		Blood::newFlow
		Functionality:
		
		calculate a new flow we want to have in a pulse
		update the information, including residualGraph, network, and fullFlows[], emptyFlows[]
		return whether there is a new flow formed.
*/
bool Blood::newFlow( int fullFlows[], int emptyFlows[])
{
	//init
	for(int i = 0; i < residualGraph->vertexCount; i++)
	{
		residualGraph->vertex[i].known = false;
		residualGraph->vertex[i].score = -1;
		residualGraph->vertex[i].fedNumber = -1;
	}
	//use Dijkstra to find a flow
	BinaryMaxHeap* heap = new BinaryMaxHeap();	
	residualGraph->vertex[0].score = 0;
	residualGraph->vertex[0].fedNumber = 0;
	heap->insert(residualGraph->vertex[0]);
	while(!heap->isEmpty())
	{
		Vertex v = Vertex();
		v = heap->deleteMax();
		if(residualGraph->vertex[v.ID].known == false && v.ID != residualGraph->vertexCount - 1)
		{
			residualGraph->vertex[v.ID].known = true;
			ListNode* node = v.edges->root;
			while(node != NULL)
			{
				if(residualGraph->vertex[node->dest].known == false)
				{
					double newScore;
					if(residualGraph->vertex[node->dest].fed == true)
						newScore = v.score;
					else
					{
						newScore = v.score + residualGraph->vertex[node->dest].rank * residualGraph->vertex[node->dest].rank * 5 / (v.fedNumber + 1);
					}

					if(newScore > residualGraph->vertex[node->dest].score)
					{
						residualGraph->vertex[node->dest].score = newScore;
						residualGraph->vertex[node->dest].prev = v.ID;
						residualGraph->vertex[node->dest].fedNumber = v.fedNumber + 1;
						heap->insert(residualGraph->vertex[node->dest]);
					}
				}
				node = node->next;
			}
		}
	}
	//update information related to the flow, including residual graph, fullFlows, emptyFlows, fed, capacity.
	
	

	//calculate the flow and find the path
	int srcVertexID = residualGraph->vertex[residualGraph->vertexCount - 1].prev;
	int destVertexID = residualGraph->vertexCount - 1;
	if(residualGraph->vertex[destVertexID].score == -1 || residualGraph->vertex[destVertexID].score == 0)
		return false;
	int flow = residualGraph->vertex[srcVertexID].edges->findCapacity(destVertexID);
	int pathSize = residualGraph->vertex[destVertexID].fedNumber + 1;
	int path[pathSize];
	int flowNeeded = 0;
	for (int i = 0; srcVertexID != -1; srcVertexID = residualGraph->vertex[srcVertexID].prev, destVertexID = residualGraph->vertex[destVertexID].prev, i++)
	{
		path[pathSize - i -1] = destVertexID;
		int thisFlow = residualGraph->vertex[srcVertexID].edges->findCapacity(destVertexID);
		if(residualGraph->vertex[destVertexID].fed == false)
			flowNeeded ++;
		if (flow > thisFlow)
			flow = thisFlow;
	}
	if(residualGraph->vertex[0].fed == false)
		flowNeeded++;
	if(flow > flowNeeded)
		flow = flowNeeded;
	path[0] = 0;
	
	
	//update residualGraphi, network and fullFlows EmptyFlows
	int temp_flow = flow, reducedFlow = 0; //which is used for flow, which will be decrease.
	for(int i = 0; i < pathSize; i++)
	{
		if(i < pathSize - 1)
		{
			
			//deal with totalFed, network/residualGraph->fed
			if(residualGraph->vertex[path[i]].fed == false)
			{
				if(temp_flow > 0)// if there is still full flows
				{
					temp_flow --;
					reducedFlow++;
					totalFed++;
					network->vertex[path[i]].fed = true;
					residualGraph->vertex[path[i]].fed = true;
				}
			}
			int vesselid = residualGraph->vertex[path[i]].edges->findID(path[i+1]);
			
			//deal with full/emptyFlows
			if(vesselid == -1)//reverse path
			{
				vesselid = network->vertex[path[i+1]].edges->findID(path[i]);
				fullFlows[vesselid] -= temp_flow;
				emptyFlows[vesselid] -= reducedFlow;
			}
			else//normal path
			{
				fullFlows[vesselid] += temp_flow;
				emptyFlows[vesselid] += reducedFlow;
			}


			//reverse path
			if(i != 0 && i < pathSize - 2)//starting path does not need reverse.
				residualGraph->addReverseEdge(flow, path[i+1], path[i]);
			
			
			//update network, residualGraph, including fed, capacity
				//capacity
			residualGraph->vertex[path[i]].edges->reduceCapacity(path[i+1], flow);
			
			
		}
		else// for the last cell of the path
		{
			if(residualGraph->vertex[path[i]].fed == false)
			{
				if(temp_flow > 0)
				{
					temp_flow --;
					reducedFlow++;
					totalFed++;
					network->vertex[path[i]].fed = true;
					residualGraph->vertex[path[i]].fed = true;
				}
			}
			
		}
	}

	

	if(flow == 0)
		return false;
	else 
		return true;
}
