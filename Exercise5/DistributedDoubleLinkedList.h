#include <iostream>

using namespace std;

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
			cout << "Thread's Id : " << id << " asked for ids sum" << endl;
			int leftSum = SommeIdsLeft();
			int rightSum = SommeIdsRight();
			int sommeIds = id + leftSum + rightSum;
			cout << "Thread's Id : " << id << " calcul complet, result = " 
				<< sommeIds <<" = " << leftSum <<" (left sum) + " << id <<" (my id) + " << rightSum <<" (right sum)"
				<< endl << endl << endl;
			return sommeIds;
		}

	private:
		inline int SommeIdsLeft() 
		{
			cout << "Thread's Id : " << id << " asked for ids sum of its left" << endl;
			int valueToReturn = 0;
			if (prev == 0)
			{
				valueToReturn = 0;
				cout << "Thread's Id : " << id << " left thread Id sum = " << valueToReturn <<" (no predecessor)" << endl;
			}
			else
			{
				cout << "pedecessor Id : " << prev->id << endl;
				int prevId = prev->id;
				int leftSum = prev->SommeIdsLeft();
				valueToReturn = prevId + leftSum;
				cout << "Thread's Id : " << id << " left thread Id sum = " << valueToReturn << " = " << prevId << " (predecessor's Id) + " << leftSum <<" (predecessor's left ids sum)"<< endl;
			}
			return valueToReturn;
		}

		inline int SommeIdsRight()
		{
			cout << "Thread's Id : " << id << " asked for ids sum of its right" << endl;
			int valueToReturn = 0;
			if (next == 0)
			{
				valueToReturn = 0;
				cout << "Thread's Id : " << id << " right thread Id sum = " << valueToReturn << " (no following)" << endl;
			}
			else
			{
				cout << "following Id : " << next->id << endl;
				int nextId = next->id;
				int rightSum = next->SommeIdsRight();
				valueToReturn = nextId + rightSum;
				cout << "Thread's Id : " << id << " right thread Id sum = " << valueToReturn <<" = " << nextId << " (following's Id) + " << rightSum << " (following's right ids sum)" << endl;
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

