#include <iostream>
#include <thread>
#include <mutex>
#include <Windows.h>

using namespace std;

#pragma once
class DistributedDoubleLinkedList
{
private:
	//The Node inside de double chained list
	class Thread {
	public:
		Thread* next;
		Thread* prev;
		Thread(const int& data_item, Thread* next_ptr = 0, Thread* prev_ptr = 0) : /*id(data_item),*/ next(next_ptr), prev(prev_ptr) 
		{
			mySemaphore = CreateSemaphore(NULL, 0, 1, NULL);//the semaphore as 1 max capacity (like a mutex) but it start with 0 token available
			stopRun = false;
			getIdRequest = false;
			tempThreadId = NULL;//temp value for communication between threads 
								//pipe was to complicated on windows, and thread share the shame memory, so no need
			thread myThread(&Thread::run, this, data_item);//we launch a thread with the method run, and an id
														//the id is only knowed by the thread, it's like std::thread::id
														//but it's a custom int id, std::thread::id can't easly be casted in int
			myThread.detach();
		}
		~Thread()
		{
			StopThread();
			//CloseHandle(mySemaphore);
		}

		inline int SommeIds()//Ask for the sum of all ids in the list
		{
			cout << "Thread's Id : " << getThreadId() << " asked for ids sum" << endl;
			int leftSum = SommeIdsLeft();//ask for the sum of the ids on the left
			int rightSum = SommeIdsRight();//ask for the sum of the ids on the right
			int sommeIds = getThreadId() + leftSum + rightSum;
			cout << "Thread's Id : " << getThreadId() << " calcul complet, result = "
				<< sommeIds <<" = " << leftSum <<" (left sum) + " << getThreadId() <<" (my id) + " << rightSum <<" (right sum)"
				<< endl << endl << endl;
			return sommeIds;
		}

		inline void StopThread() {//stop the while in the run fonction of the thread
			stopRun = true;
		}

		inline int getThreadId() {
			tempThreadId = NULL;
			getIdRequest = true; //we ask the the thread its id
			WaitForSingleObject(mySemaphore, INFINITE); //we ask for the acces (acces release only when the thread have updated the value of tempThreadId)
			int idFromThread = tempThreadId;
			return idFromThread;
		}

	private:
		inline int SommeIdsLeft() //recursive function to have the sum of the ids of the predecessors
		{
			cout << "Thread's Id : " << getThreadId() << " asked for ids sum of its left" << endl;
			int valueToReturn = 0;
			if (prev == 0) //no more predecessors, we stop
			{
				valueToReturn = 0;
				cout << "Thread's Id : " << getThreadId() << " left thread Id sum = " << valueToReturn <<" (no predecessor)" << endl;
			}
			else
			{
				cout << "pedecessor Id : " << prev->getThreadId() << endl;
				int prevId = prev->getThreadId();
				int leftSum = prev->SommeIdsLeft();//recursive call
				valueToReturn = prevId + leftSum;
				cout << "Thread's Id : " << getThreadId() << " left thread Id sum = " << valueToReturn 
					<< " = " << prevId << " (predecessor's Id) + " << leftSum <<" (predecessor's left ids sum)"<< endl;
			}
			return valueToReturn;
		}

		inline int SommeIdsRight() //recursive function to have the sum of the ids of the followings
		{
			cout << "Thread's Id : " << getThreadId() << " asked for ids sum of its right" << endl;
			int valueToReturn = 0;
			if (next == 0) // no more followings, we stop
			{
				valueToReturn = 0;
				cout << "Thread's Id : " << getThreadId() << " right thread Id sum = " << valueToReturn << " (no following)" << endl;
			}
			else
			{
				cout << "following Id : " << next->getThreadId() << endl;
				int nextId = next->getThreadId();
				int rightSum = next->SommeIdsRight();//recursive call
				valueToReturn = nextId + rightSum;
				cout << "Thread's Id : " << getThreadId() << " right thread Id sum = " << valueToReturn
					<<" = " << nextId << " (following's Id) + " << rightSum << " (following's right ids sum)" << endl;
			}
			return valueToReturn;
		}

		thread myThread;
		bool stopRun; //bool to stop the thread
		bool getIdRequest; //bool to say to the thread that we need to get its Id;
		int tempThreadId;//temp value for communication between threads 
		HANDLE mySemaphore;//semaphore to bloc acces to tempThreadId when reading / writting

		inline void run(int customThreadId){//method executed by the thread
			while (!stopRun)//like an infinite loop that we can stop
			{
				if (getIdRequest)//request for the thread's id
				{
					getIdRequest = false;
					tempThreadId = customThreadId;
					ReleaseSemaphore(mySemaphore, 1, NULL);//the semaphore as a token available only after writting (1 max capacity).
															//by defaut (semaphore creation) there are no token available
															//and release is done only after writting, so reading is always after writting
				}
				Sleep(10);
			}
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

