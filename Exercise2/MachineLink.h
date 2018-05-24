#pragma once

class IMachine;

class MachineLink {
public:
	MachineLink();
	virtual ~MachineLink() = default;

protected:

	friend IMachine;

	void setInputMachine(IMachine* input);
	void setOutputMachine(IMachine* output);

	IMachine* inputMachine;
	IMachine* outputMachine;
};

