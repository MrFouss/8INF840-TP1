#include <iostream>

#pragma once
class DistributedDoubleLinkedList
{
private:
	//The Node inside de double chained list
	class Thread {
	public:
		int id;
		Thread* next;
		Thread* prev;
		Thread(const int& data_item, Thread* next_ptr = 0, Thread* prev_ptr = 0) : id(data_item), next(next_ptr), prev(prev_ptr) {}
		inline int SommeIds()
		{
			return id + SommeIdsLeft() + SommeIdsRight();
		}
	private:
		inline int SommeIdsLeft() 
		{
			int valueToReturn = 0;
			if (prev == 0)
			{
				valueToReturn = 0;
			}
			else
			{
				valueToReturn = prev->id + prev->SommeIdsLeft();
			}
			return valueToReturn;
		}
		inline int SommeIdsRight()
		{
			int valueToReturn = 0;
			if (next == 0)
			{
				valueToReturn = 0;
			}
			else
			{
				valueToReturn = next->id + next->SommeIdsRight();
			}
			return valueToReturn;
		}
	};

public:
	//Constructors
	DistributedDoubleLinkedList();
	DistributedDoubleLinkedList(const DistributedDoubleLinkedList& dclist);

	//Destructors
	~DistributedDoubleLinkedList();

	//Operators overload
	const DistributedDoubleLinkedList& operator= (const DistributedDoubleLinkedList&);

	//Attributs
	Thread* start;
	Thread* end;
	int cpt;

	//Methods
	void add(const int& toAddData, int pos);
	void add(const int& toAddData); //Add at the end
	void remove(const int& toRemoveData);
	void cust_copy(Thread* toCopy);
	void cust_destroy();//Avoid code duplication

};

