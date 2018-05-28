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
		if (outputMachine != 0) {
			outputMachine->onInputLinkUpdated();
		}
	}

	T* pop() {
		return queue.pop();
	}

	bool isEmpty() const { return queue.isEmpty(); }

	int getSize() const { return queue.getElementNbr(); }

private:
	Queue<T*> queue;
};

