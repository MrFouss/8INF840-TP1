#pragma once

#include "MachineLink.h"
#include "Queue.h"
#include "IMachine.h"

template <typename T>
class MachineDataLink : public MachineLink {
public:
	MachineDataLink() :
		queue() {}

	virtual ~MachineDataLink() = default;

	void push(T* obj) {
		queue.push(obj);
		if (outputMachine != NULL) {
			outputMachine->onLinkUpdated();
		}
	}

	T* pop() {
		T* obj = queue.pop();
		if (inputMachine != NULL) {
			inputMachine->onLinkUpdated();
		}
		return obj;
	}

	bool isEmpty() const { return queue.isEmpty(); }

private:
	Queue<T*> queue;
};

