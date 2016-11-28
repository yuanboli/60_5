#include "list.h"


void List::insert(int destination, int cap)
{
	root = new ListNode(root, destination, cap);
}
