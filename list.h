#ifndef listH
#define listH

///
/*
		ListNode class is for List class

*/
class ListNode
{
friend class List;

public:
	ListNode(ListNode* n, int d, int c): next(n), dest(d), capacity(c){}
	ListNode* next;
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
	void insert(int destination, int cap);
} ;



#endif
