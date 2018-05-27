#include "DistributedDoubleLinkedList.h"

using namespace std;

DistributedDoubleLinkedList::DistributedDoubleLinkedList()
{
	start = NULL;
	end = NULL;
	cpt = 0;
}

DistributedDoubleLinkedList::DistributedDoubleLinkedList(const DistributedDoubleLinkedList & dclist)
{
	if (dclist.start == NULL)
		start = NULL; //The initial list is empty
	else
		cust_copy(dclist.start);
}

DistributedDoubleLinkedList::~DistributedDoubleLinkedList()
{
	cust_destroy();
}

const DistributedDoubleLinkedList& DistributedDoubleLinkedList::operator=(const DistributedDoubleLinkedList& dcList)
{
	if (start != 0) // We clean the list
	{
		cust_destroy();
	}
	if (dcList.start != 0)
	{
		cust_copy(dcList.start);
	}
	return (*this);
}


void DistributedDoubleLinkedList::add(const int& toAddData, int pos)
{
	Thread* current;
	Thread* newNode;
	int tempCpt = 1;

	newNode = new Thread(toAddData);
	if (start == 0) //Si la list est vide
	{
		start = newNode;
		end = newNode;
		//cpt++;
		//return;
	}
	else if (pos == 1) {//Add at the beginning
		newNode->next = start;
		start->prev = newNode;
		start = newNode;
		newNode->prev = NULL;
		//cpt++;
		//return;
	}
	else if (pos > cpt) //Add at the end
	{
		end->next = newNode;
		newNode->prev = end;
		end = newNode;
		newNode->next = NULL;
		//cpt++;
		//return;
	}
	else {
		current = start;
		while (tempCpt < pos) {
			current = current->next;
			tempCpt++;
		}
		current->prev->next = newNode;
		newNode->prev = current->prev;
		newNode->next = current;
		current->prev = newNode;
	}
	cpt++;
}

void DistributedDoubleLinkedList::add(const int & toAddData)
{
	add(toAddData, cpt + 1);
}

void DistributedDoubleLinkedList::remove(const int & toRemoveData)
{
	Thread* current = start;

	while (current->getThreadId() != toRemoveData && current != 0)
	{
		current = current->next;
	}

	if (current == 0)
	{
		throw logic_error("The element is not in the list, can't remove it");
	}
	else {
		if (current == start)
		{
			start->next->prev = NULL;
			start = start->next;
		}
		else if (current == end)
		{
			end->prev->next = NULL;
			end = end->prev;
		}
		else {
			current->prev->next = current->next;
			current->next->prev = current->prev;
		}
		current->next = NULL;
		current->prev = NULL;
		delete(current);
		cpt--;
	}
}

void DistributedDoubleLinkedList::cust_copy(Thread* toCopy)
{
	try {
		start = new Thread(toCopy->getThreadId());
		Thread* newNode = start;
		for (Thread* temp = toCopy; temp != 0; temp = temp->next) {
			newNode->next = new Thread(temp->getThreadId());
			newNode->next->prev = newNode;
			newNode = newNode->next;
			cpt++;
		}
		end = newNode;
	}
	catch (exception&) {
		cust_destroy();
		cout << "Error occcured during cust_copy";
		throw;
	}
}

void DistributedDoubleLinkedList::cust_destroy()
{
	Thread* current = start;
	while (current != 0) {
		start = current->next;
		current->~Thread();
		current = start;
		if (current != 0)
		{
			current->prev = 0;
		}
	}
	delete(current);
}

