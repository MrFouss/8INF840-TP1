#include "MachineLink.h"

#include "IMachine.h"

MachineLink::MachineLink() :
	objects(),
	inputMachine(NULL),
	outputMachine(NULL) {
}

void MachineLink::push(Machineable* obj) {
	objects.push(obj);
	if (outputMachine != NULL) {
		outputMachine->onInputUpdate();
	}
}

Machineable * MachineLink::pop() {
	Machineable* obj =  objects.pop();
	if (inputMachine != NULL) {
		inputMachine->onOutputUpdate();
	}
	return obj;
}

void MachineLink::setInputMachine(IMachine * inputMachine) {
	this->inputMachine = inputMachine;
}

void MachineLink::setOutputMachine(IMachine * outputMachine) {
	this->outputMachine = outputMachine;
}

int MachineLink::getSize() const {
	return objects.getSize();
}

bool MachineLink::isEmpty() const {
	return objects.isEmpty();
}
