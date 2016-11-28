#ifndef BLOODRUNNER_H
	#define BLOODRUNNER_H
	
class Vessel
{
 public:
 	int src;
  int dest;
  int capacity;
};  // class Vessel

class Cell
{
public:
  int inFullCount;
  int outFullCount;
  int inEmptyCount;
  int outEmptyCount;
  bool fed;
  Cell(): fed(false){}
}; // class Cell

#endif

