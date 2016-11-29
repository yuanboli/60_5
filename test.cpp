#include "list.h"
using namespace std;

int main()
{
	List* a = new List;
	a->insert(1, 1);
	a->insert(2, 2);
	a->insert(3, 3);
	a->deleteNode(3);
	a->deleteNode(1);
}
