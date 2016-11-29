#ifndef listH
#define listH
#include <iostream>

///
/*
		ListNode class is for List class

*/
class ListNode
{
friend class List;

public:
	ListNode(ListNode* n,int i, int d, int c): next(n), ID(i), dest(d), capacity(c){}
	ListNode* next;
	int ID;
	int dest;
	int capacity;
} ;
///
/*
		this List class is a linked list for int
*/
class List
{
public:
	ListNode* root;
	void insert(int ID, int destination, int cap);
	List(){root = NULL;}
	int findCapacity(int destID);
	int findID(int destID);
	void reduceCapacity(int destID, int flow);
	void operator= (List& rhs);
	void deleteNode(int destID);
} ;



#endif
