#pragma once

#include "IMachine.h"

class GeneratorMachine : public IMachine {
public:
	GeneratorMachine(int maxOutputSize) : maxOutputSize(maxOutputSize), outputLink(NULL) {}
	virtual ~GeneratorMachine() = default;

	void setOutputLink(MachineLink* outputLink) {
		this->outputLink = outputLink;
		outputLink->setInputMachine(this);
	}
	
	virtual void tryProcessNext();

	virtual void onOutputUpdate() {
		tryProcessNext();
	}

private:

	int maxOutputSize;
	MachineLink * outputLink;
};

