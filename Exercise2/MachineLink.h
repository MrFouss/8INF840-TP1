#pragma once

#include "Queue.h"
#include "IMachine.h"

template <typename T>
class MachineLink {
public:
	MachineLink():
		queue(), inputMachine(NULL), outputMachine(NULL) {}

	virtual ~MachineLink() = default;

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

	void setInputMachine(IMachine* input) {
		inputMachine = input;
	}

	void setOutputMachine(IMachine* output) {
		outputMachine = output;
	}

private:

	IMachine* inputMachine;
	IMachine* outputMachine;
	Queue<T*> queue;
};

