#include "list.h"
using namespace std;

int main()
{
	List* a = new List;
	a->insert(1, 1);
	a->insert(2, 2);
	a->insert(3, 3);
	List b = *a;
	if(b.root)
	{	
		cout << "b.root " << b.root;
		cout << "b.root content " << b.root->next << " " << b.root->dest << " " << b.root->capacity;
	}	
}
