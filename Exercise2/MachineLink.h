#pragma once

class IMachine;

class MachineLink {
public:
	MachineLink():
		inputMachine(0), outputMachine(0) {}

	virtual ~MachineLink() = default;

protected:

	friend IMachine;

	void setInputMachine(IMachine& input) {
		inputMachine = &input;
	}

	void setOutputMachine(IMachine& output) {
		outputMachine = &output;
	}

	IMachine* inputMachine;
	IMachine* outputMachine;
};

