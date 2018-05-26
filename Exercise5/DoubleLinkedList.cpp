#include "DoubleLinkedList.h"

using namespace std;

template<typename T>
DoubleLinkedList<T>::DoubleLinkedList()
{
	start = NULL;
	end = NULL;
	cpt = 0;
}

template<typename T>
DoubleLinkedList<T>::DoubleLinkedList(const DoubleLinkedList & dclist)
{
	if (dclist.start == NULL)
		start = NULL; //The initial list is empty
	else
		cust_copy(dclist.start);
}

template<typename T>
DoubleLinkedList<T>::~DoubleLinkedList()
{
	cust_destroy();
}

template<typename T>
const DoubleLinkedList<T>& DoubleLinkedList<T>::operator=(const DoubleLinkedList<T>& dcList)
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


template<typename T>
void DoubleLinkedList<T>::add(const T & toAddData, int pos)
{
	Node* current;
	Node* newNode;
	int tempCpt = 1;

	newNode = new Node(toAddData);
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

template<typename T>
void DoubleLinkedList<T>::add(const T & toAddData)
{
	add(toAddData, cpt + 1);
}

template<typename T>
void DoubleLinkedList<T>::remove(const T & toRemoveData)
{
	Node* current = start;
	
	while (current->data != toRemoveData && current != 0)
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

template<typename T>
void DoubleLinkedList<T>::cust_copy(Node* toCopy)
{
	try {
		start = new Node(toCopy->data);
		Node* newNode = start;
		for (Node* temp = toCopy; temp != 0; temp = temp->next) {
			newNode->next = new Node(temp->data);
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

template<typename T>
void DoubleLinkedList<T>::cust_destroy()
{
	Node* current = start;
	while (current != 0) {
		start = current->next;
		delete(current);
		current = start;
		current->prev = 0;
	}
}


