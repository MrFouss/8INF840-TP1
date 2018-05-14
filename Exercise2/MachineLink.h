#pragma once

#include <iostream>

class IMachine;

class MachineLink {
public:
	MachineLink():
		inputMachine(NULL), outputMachine(NULL) {}

	virtual ~MachineLink() = default;

protected:

	friend IMachine;

	void setInputMachine(IMachine* input) {
		inputMachine = input;
	}

	void setOutputMachine(IMachine* output) {
		outputMachine = output;
	}

	IMachine* inputMachine;
	IMachine* outputMachine;
};

