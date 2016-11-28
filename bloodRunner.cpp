// Author: Sean Davis
#include <fstream>
#include <iostream>
#include "bloodRunner.h"
#include "CPUTimer.h"
#include "blood.h"

using namespace std;

void readFile(const char filename[], Vessel **vessels, Vessel **vessels2,
	int *vesselCount, int *cellCount, int *depth)
{
  int ID;
  Vessel *ves, *ves2;
	ifstream inf(filename);
  inf >> *cellCount >> *vesselCount >> *depth;
  ves = new Vessel[*vesselCount];
  ves2 = new Vessel[*vesselCount];
  for(int i = 0; i < *vesselCount; i++)
  {
    inf >> ID;
  	inf >> ves[ID].src >> ves[ID].dest >> ves[ID].capacity;
    ves2[ID] = ves[ID];
  } // for i

  inf.close();
  *vessels2 = ves2;
  *vessels = ves;
} // readFile()

void checkFlows(Vessel vessels[], int fullFlows[], int emptyFlows[],
  Cell cells[], int vesselCount,  int cellCount, int pulses, int *totalFed)
{
  int netFlow, cellCount1 = cellCount - 1, i;

  for(int i = 0; i < cellCount; i++)
      cells[i].inFullCount = cells[i].outFullCount
        = cells[i].inEmptyCount = cells[i].outEmptyCount = 0;

  for(int i = 0; i < vesselCount; i++)
  {
    cells[vessels[i].src].outFullCount += fullFlows[i];
    cells[vessels[i].dest].inFullCount += fullFlows[i];
    cells[vessels[i].src].outEmptyCount += emptyFlows[i];
    cells[vessels[i].dest].inEmptyCount += emptyFlows[i];
    if (fullFlows[i] + emptyFlows[i] > vessels[i].capacity)
      cout << "Vessel #" << i << " at pulse #" << pulses 
        << " has a total flow of " << fullFlows[i] + emptyFlows[i]
        << " which exceeds its capacity of " << vessels[i].capacity << endl; 
  } // for each vessel

  cells[0].inFullCount = cells[0].outFullCount;
  if(!cells[0].fed)
    cells[0].inFullCount++;

  for(i = 0; i < cellCount1; i++)
  {
    if(cells[i].inFullCount != 0 && !cells[i].fed)
    {
      if(!cells[i].fed)
      {
        (*totalFed)++;
        cells[i].fed = true;
      }
      if(cells[i].inFullCount != cells[i].outFullCount + 1
        || cells[i].inEmptyCount != cells[i].outEmptyCount - 1)
        cout << "Cell #" << i  << " at pulse #" << pulses
          << " does not properly eat a full cell.\n";
    } // if cell not full and a flow past

    netFlow = cells[i].inFullCount + cells[i].inEmptyCount -
      cells[i].outFullCount - cells[i].outEmptyCount;
    if(netFlow != 0 && i != cellCount - 1)
      cout << "Cell #" << i << " at pulse #" << pulses << " has net flow of "
        << netFlow << endl;
  } // for each cell before last

  if(cells[cellCount1].inFullCount > 0 && !cells[cellCount1].fed)
  {
    cells[cellCount1].fed = true;
    (*totalFed)++;
  }  // if last cell is getting first fed


} // checkFlows


int main(int argc, char *argv[])
{
  int vesselCount, cellCount, depth, *emptyFlows, *fullFlows, 
    pulses = 0, totalFed = 0, theirTotalFed;
  Vessel *vessels, *vessels2;
  Cell *cells;
  CPUTimer ct;

  if(argc != 2)
  {
    cout << "Usage: blood.out filename\n";
    return 1;
  } // if wrong number of arguments

  readFile(argv[1], &vessels, &vessels2, &vesselCount, &cellCount, &depth);
  cells = new Cell[cellCount];
  emptyFlows = new int[vesselCount];
  fullFlows = new int[vesselCount];
  ct.reset();
  Blood *blood = new Blood(vessels2, vesselCount, cellCount, depth);
  delete [] vessels2;

  do{
    theirTotalFed = blood->calcFlows(fullFlows, emptyFlows);
    checkFlows(vessels, fullFlows, emptyFlows, cells, vesselCount, cellCount,
      pulses, &totalFed);
    if(theirTotalFed != totalFed)
      cout << "At pulse #" << pulses << " your number fed, " << theirTotalFed
        << ", does not match ours, " << totalFed << endl;
  } while(++pulses < 10000  && totalFed < cellCount);

  cout << "Time: " << ct.cur_CPUTime() << " Pulses: " << pulses << endl;

  for(int i = 0; i < cellCount; i++)
    if(!cells[i].fed)
      cout << "Cell #" << i << " has not been fed.\n";

  delete blood;
  delete [] vessels;
  delete [] cells;
  delete [] emptyFlows;
  delete [] fullFlows;
  return 0;
}  // main()
