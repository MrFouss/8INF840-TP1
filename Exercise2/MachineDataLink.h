#pragma once

#include "MachineLink.h"
#include "Queue.h"
#include "IMachine.h"

template <typename T>
class MachineDataLink : public MachineLink {
public:
	MachineDataLink() :
		queue() {}

	virtual ~MachineDataLink() {
		while (!queue.isEmpty()) {
			delete queue.pop();
		}
	}

	void push(T* obj) {
		queue.push(obj);
		if (outputMachine != NULL) {
			outputMachine->onInputLinkUpdated();
		}
	}

	T* pop() {
		T* obj = queue.pop();
		return obj;
	}

	bool isEmpty() const { return queue.isEmpty(); }

	int getSize() const { return queue.getSize(); }

private:
	Queue<T*> queue;
};

