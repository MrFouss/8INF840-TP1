#include "DistributedDoubleLinkedList.h"

using namespace std;

int main()
{	
	
	//Test Distributed Double Chained List
	DistributedDoubleLinkedList* ddcl = new DistributedDoubleLinkedList();
	ddcl->add(2);
	ddcl->add(7);
	ddcl->add(1);
	ddcl->add(9);
	ddcl->add(4);
	ddcl->add(6);
	ddcl->add(3);

	ddcl->start->SommeIds();
	ddcl->start->next->SommeIds();
	ddcl->end->SommeIds();
	ddcl->end->prev->prev->SommeIds();

	cout << "\n";
	system("pause");

	return 0;
}