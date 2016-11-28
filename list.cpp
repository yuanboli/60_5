#include "list.h"


void List::insert(int destination, int cap)
{
	root = new ListNode(root, destination, cap);
}


//will only get a reverse vessel but it does not matter
void List::operator=(List& rhs)
{
	
	
	ListNode* rhsnode = rhs.root;
	if(rhsnode == NULL)
		return;
	root = new ListNode(NULL, rhsnode->dest, rhsnode->capacity);
	ListNode* node = root;
	rhsnode = rhsnode->next;
	while(rhsnode != NULL)
	{
		node->next = new ListNode(NULL, rhsnode->dest, rhsnode->capacity);
		rhsnode = rhsnode->next;
		node = node->next;
	}
}
