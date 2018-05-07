#pragma once

#include "Queue.h"

class IMachine;
class Machineable;

class MachineLink {
public:
	MachineLink();

	virtual ~MachineLink() = default;

	void push(Machineable* obj);
	Machineable* pop();

	void setInputMachine(IMachine* inputMachine);

	void setOutputMachine(IMachine* outputMachine);

	int getSize() const;

	bool isEmpty() const;

private:

	IMachine* inputMachine;
	IMachine* outputMachine;
	Queue<Machineable*> objects;
};

