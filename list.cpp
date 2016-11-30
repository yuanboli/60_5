#include "list.h"


void List::insert(int ID, int destination, int cap)
{
	root = new ListNode(root, ID, destination, cap);
}


//will only get a reverse vessel but it does not matter
void List::operator=(List& rhs)
{
	
	
	ListNode* rhsnode = rhs.root;
	if(rhsnode == NULL)
	{
		root = NULL;
		return;
	}
	root = new ListNode(NULL, rhsnode->ID, rhsnode->dest, rhsnode->capacity);
	ListNode* node = root;
	rhsnode = rhsnode->next;
	while(rhsnode != NULL)
	{
		node->next = new ListNode(NULL,rhsnode->ID, rhsnode->dest, rhsnode->capacity);
		rhsnode = rhsnode->next;
		node = node->next;
	}
}


int List::findCapacity(int destID)
{
	ListNode* node = root;
	while(node != NULL)
	{
		if(destID == node->dest)
			return node->capacity;

		node = node->next;
	}
	return -1;
}
int List::findID(int destID)
{
	ListNode* node = root;
	while(node != NULL)
	{
		if(destID == node->dest)
			return node->ID;

		node = node->next;
	}
	return -1;
}

void List::reduceCapacity(int destID, int flow)
{
	ListNode* node = root;
	while(node != NULL)
	{
		if(destID == node->dest)
		{
			node->capacity -= flow;
			if(node->capacity == 0)
				deleteNode(destID);
		}
		node = node->next;
	}
}


// we assume that the destID exist
void List::deleteNode(int destID)
{
	ListNode* node, *prev = root;
	for(node = root; node && node->dest != destID; node = node->next)
	{
		prev = node;
	}
	if(node == root)
		root = node->next;
	else
		prev->next = node->next;
}

