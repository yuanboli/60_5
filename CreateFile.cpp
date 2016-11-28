#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>
using namespace std;

class Vessel
{
 public:
 	int src;
  int dest;
  int capacity;
  Vessel():capacity(0){}
};

class Cell
{
public:
  int count;
  int level;
  Cell(): count(0), level(-1){}
};


void createBrain(int cellCount, int vesselCount, Vessel vessels[], Cell cells[], int *maxLevel)
{
  int lastDest = 0, dest, vesselNum, src, level, count;
  int **adjacent = new int* [cellCount];
  bool OK;



  for(int i = 0; i < cellCount; i++)
  {
    adjacent[i] = new int[11];
    adjacent[i][0] = 0;
  }

	cells[0].count = 1;
	cells[0].level = 0;

	for(*maxLevel = 0; lastDest != cellCount - 1; (*maxLevel)++)
	{
	  do
	  {
	  	dest = rand() % cellCount;
	  } while(cells[dest].count != 0);  // find a new cell

	  vessels[*maxLevel].src = lastDest;
	  vessels[*maxLevel].dest = dest;
    adjacent[lastDest][++adjacent[lastDest][0]] = dest;
    adjacent[dest][++adjacent[dest][0]] = lastDest;
	  cells[dest].level = *maxLevel;
	  cells[dest].count = 2;
	  lastDest = dest;
	}	// create a path from carotid to jugular

	vesselNum = *maxLevel;

	for(int i = 1; i < cellCount; i++)
  {
		if(cells[i].count == 0)
		{
		  do
		  {
		    src = rand() % (cellCount - 1);
		  } while (cells[src].count > 4 || cells[src].count == 0
        || cells[src].level >= *maxLevel - 1);
			// connected but not too connected and not next to last level, or carotid

			cells[i].level = level = cells[src].level + 1;
			vessels[vesselNum].src = src;
			vessels[vesselNum++].dest = i;
      adjacent[src][++adjacent[src][0]] = i;
      adjacent[i][++adjacent[i][0]] = src;
			cells[src].count++;

			do
		  {
		    dest = rand() % cellCount;
		  } while((cells[dest].count > 4 || cells[dest].count == 0 || cells[dest].level <= level)
          && dest != cellCount - 1);
			// connected but not too connected and level > than current level, or jugular

			vessels[vesselNum].src = i;
			vessels[vesselNum++].dest = dest;
      adjacent[i][++adjacent[i][0]] = dest;
      if(dest != cellCount - 1)
        adjacent[dest][++adjacent[dest][0]] = i;

			cells[dest].count++;
			cells[i].count = 2;
		} // if cell not connected yet
  } // for each cell

  for(; vesselNum < vesselCount; vesselNum++)
	{
	  do
	  {
      OK = true;
	    src = rand() % (cellCount - 1);
      if(cells[src].count > 4 || cells[src].level >= *maxLevel - 1)
        OK = false;
      else
        for(int i = 1; i <= adjacent[src][0]; i++)
          if(adjacent[src][i] == cellCount - 1)
            OK = false;
	  } while (!OK);
	  // connected but not too connected and not next to last level, or carotid

	  level = cells[src].level;
    count = 0;
	  do
	  {
      count++;
      OK = true;
	    dest = rand() % (cellCount - 1) + 1; // 1-last
      if ((cells[dest].count > 4 || cells[dest].level <= level) && dest != cellCount - 1)
        OK = false;
      else
        for(int i = 1; i <= adjacent[src][0]; i++)
          if(adjacent[src][i] == dest)
            OK = false;

	  } while(!OK && count < 20);
      // connected but not too connected and level > than current level, or jugular

    if(count == 20)
    {
       --vesselNum;
       continue;
    }
	  vessels[vesselNum].src = src;
	  vessels[vesselNum].dest = dest;
    adjacent[src][++adjacent[src][0]] = dest;
    if(dest != cellCount - 1)
      adjacent[dest][++adjacent[dest][0]] = src;

	  cells[dest].count++;
	  cells[src].count++;
  } // for remaining vessels

  for(int i = 0; i < vesselCount; i++)
			vessels[i].capacity = rand() % (1 + cellCount / 10) + 1;  // guarantee more than a couple of pulses

  for(int i = 0; i < cellCount; i++)
    delete [] adjacent[i];

  delete [] adjacent;
} // createBrain()

void writeFile(const char filename[], int cellCount, int vesselCount,
	const Vessel vessels[], const Cell cells[], int maxLevel)
{
  int *cellIDs, *vesselIDs, i, dest, temp, ID;

  cellIDs = new int[cellCount];
  vesselIDs = new int[vesselCount];

  for(i = 0; i < cellCount; i++)
  	cellIDs[i] = i;

  for(i = 0; i < vesselCount; i++)
  	vesselIDs[i] = i;

  for(i = 1; i < cellCount - 1; i++)
	{
	  dest = rand() % (cellCount - 2) + 1;
	  temp = cellIDs[i];
	  cellIDs[i] = cellIDs[dest];
	  cellIDs[dest] = temp;
	} // for each cell, except first and last

	for(i = 0; i < vesselCount; i++)
	{
	  dest = rand() % vesselCount;
	  temp = vesselIDs[i];
	  vesselIDs[i] = vesselIDs[dest];
	  vesselIDs[dest] = temp;
	}	// for each vessel

	ofstream outf(filename);
	outf << cellCount << ' ' << vesselCount << ' ' << maxLevel << endl;

	for(ID = 0; ID < vesselCount; ID++)
	{
	 	i = vesselIDs[ID];
	  outf << ID << ' ' << cellIDs[vessels[i].src] << ' '
			<< cellIDs[vessels[i].dest] << ' ' << vessels[i].capacity << endl;
	}
	outf.close();

  delete [] cellIDs;
  delete [] vesselIDs;

} // writeFile()
int main()
{
  char filename[80];
	int cellCount, seed, vesselCount, maxLevel;
	Vessel *vessels;
	Cell *cells;

  do
  {
	  cout << "Brain cells (6- ): ";
	  cin >> cellCount;
	} while(cellCount < 6);
	do
	{
		cout << "Blood vessels (brain cells < x < 2.5 * brain cells): ";
		cin >> vesselCount;
  } while(vesselCount < cellCount || vesselCount >= 2.5 * cellCount);

	cout << "Seed: ";
	cin >> seed;
	srand(seed);

  vessels = new Vessel[vesselCount];
	cells = new Cell[cellCount];
 	createBrain(cellCount, vesselCount, vessels, cells, &maxLevel);
 	sprintf(filename, "brain-%d-%d-%d.txt", cellCount, vesselCount, seed);
	writeFile(filename, cellCount, vesselCount, vessels, cells, maxLevel);
 	return 0;
} // main()
