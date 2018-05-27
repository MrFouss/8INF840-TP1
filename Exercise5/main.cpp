//#include "DoubleLinkedList.cpp"
#include "DistributedDoubleLinkedList.h"

using namespace std;

int main()
{	
	/*
	//Test Template Double Chained List
	DoubleLinkedList<int>* dcl = new DoubleLinkedList<int>();

	dcl->add(10);
	cout << "Start : " << dcl->start->data << "\n";
	cout << "End : " << dcl->end->data << "\n";
	cout << "Nb elem :" << dcl->cpt << "\n";
	cout << "\n";

	dcl->add(12);
	cout << "Start : " << dcl->start->data << "\n";
	cout << "End : " << dcl->end->data << "\n";
	cout << "Nb elem :" << dcl->cpt << "\n";
	cout << "\n";

	dcl->add(115,2);
	cout <<"Start : "<< dcl->start->data <<"\n";
	cout <<"End : "<< dcl->end->data << "\n";
	cout <<"Nb elem :" <<dcl->cpt << "\n";
	cout << "\n";

	dcl->remove(10);
	cout << "Start : " << dcl->start->data << "\n";
	cout << "End : " << dcl->end->data << "\n";
	cout << "Nb elem :" << dcl->cpt << "\n";
	cout << "\n";

	dcl->remove(12);
	cout << "Start : " << dcl->start->data << "\n";
	cout << "End : " << dcl->end->data << "\n";
	cout << "Nb elem :" << dcl->cpt << "\n";
	cout << "\n";
	*/

	
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