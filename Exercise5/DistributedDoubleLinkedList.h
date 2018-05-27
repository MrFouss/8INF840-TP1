#include <iostream>
#include <thread>
#include <stdio.h>
#include <Windows.h>

#define BUFSIZE 100

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
		Thread(const int& data_item, Thread* next_ptr = 0, Thread* prev_ptr = 0) : id(data_item), next(next_ptr), prev(prev_ptr) 
		{
			stopRun = false;
			getIdRequest = false;
			SECURITY_ATTRIBUTES saAttr;
			CreatePipe(hReadPipe, hWritePipe,&saAttr, 0);
			thread myThread(&Thread::run, this);
			myThread.detach();
		}
		~Thread()
		{
			StopThread();
		}

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

		inline void StopThread() {
			stopRun = true;
		}

		inline int getThreadId() {
			getIdRequest = true;
			return ReadFromPipe();
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

		thread myThread;
		bool stopRun; //bool to stop the thread
		bool getIdRequest; //bool to say to the thread that we need to get its Id;
		PHANDLE hReadPipe = NULL;
		PHANDLE hWritePipe = NULL;

		inline void run(){
			while (!stopRun)
			{
				if (getIdRequest)
				{
					cout << "Thread id :" << this_thread::get_id() << endl;
					//WriteToPipe((CHAR*)id);
					int i = 69;
					WriteToPipe(&i);
				}
			}
		}

		inline void WriteToPipe(int* ch)
		{
			DWORD dwRead = 100, dwWritten;
			//CHAR chBuf[BUFSIZE];
			getIdRequest = false;
			bool succes = true;
			for (;;)
			{
				succes = WriteFile(hWritePipe, ch, dwRead, &dwWritten, NULL);
				if (!succes)
				{
					break;
				}
			}
			CloseHandle(hWritePipe);
		}

		inline int ReadFromPipe()
		{
			DWORD dwRead, dwWritten;
			//CHAR chBuf[BUFSIZE];
			//ReadFile(hReadPipe, chBuf, BUFSIZE, &dwRead, NULL);
			//return chBuf;

			int intBuf[BUFSIZE];
			bool succes = true;
			for (;;)
			{
				succes = ReadFile(hReadPipe, intBuf, BUFSIZE, &dwRead, NULL);
				if (!succes)
				{
					break;
				}
			}
			return intBuf[0];
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

