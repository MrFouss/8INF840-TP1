#include <iostream>

#pragma once

template<typename T>
class DoubleLinkedList
{
private:
	//The Node inside de double chained list
	class Node{
	public:
		T data;
		Node* next;
		Node* prev;
		Node(const T& data_item, Node* next_ptr = 0, Node* prev_ptr = 0) : data(data_item), next(next_ptr), prev(prev_ptr) {}
	};

public:
	//Constructors
	DoubleLinkedList();
	DoubleLinkedList(const DoubleLinkedList& dclist);

	//Destructors
	~DoubleLinkedList();

	//Operators overload
	const DoubleLinkedList<T>& operator= (const DoubleLinkedList<T>&);

	//Attributs
	Node* start;
	Node* end;
	int cpt;

	//Methods
	void add(const T& toAddData, int pos);
	void add(const T& toAddData); //Add at the end
	void remove(const T& toRemoveData);
	void cust_copy(Node* toCopy);
	void cust_destroy();//Avoid code duplication


};

