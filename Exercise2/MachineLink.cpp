#include "MachineLink.h"

#include "IMachine.h"

MachineLink::MachineLink() :
	inputMachine(0),
	outputMachine(0)
{}

void MachineLink::setInputMachine(IMachine * input) {
	inputMachine = input;
}

void MachineLink::setOutputMachine(IMachine * output) {
	outputMachine = output;
}
