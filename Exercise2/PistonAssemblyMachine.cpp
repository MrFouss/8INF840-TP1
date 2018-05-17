#include "PistonAssemblyMachine.h"

#include "MachineDataLink.h"

const std::string PistonAssemblyMachine::jupeInputName = "PistonAssemblyMachineJupeInput";
const std::string PistonAssemblyMachine::axeInputName = "PistonAssemblyMachineAxeInput";
const std::string PistonAssemblyMachine::teteInputName = "PistonAssemblyMachineTeteInput";
const std::string PistonAssemblyMachine::outputName = "PistonAssemblyMachineOutput";

inline void PistonAssemblyMachine::linkJupeInput(MachineDataLink<PistonJupe>& input) { linkInput(jupeInputName, input); }

inline void PistonAssemblyMachine::linkAxeInput(MachineDataLink<PistonAxe>& input) { linkInput(axeInputName, input); }

inline void PistonAssemblyMachine::linkTeteInput(MachineDataLink<PistonTete>& input) { linkInput(teteInputName, input); }

inline void PistonAssemblyMachine::linkOutput(MachineDataLink<Piston>& output) { IMachine::linkOutput(outputName, output); }

bool PistonAssemblyMachine::canStartNextJob() {
	return areLinksConnected() 
		&& !getTeteInputLink().isEmpty() 
		&& !getAxeInputLink().isEmpty() 
		&& !getJupeInputLink().isEmpty();
}

void PistonAssemblyMachine::startNextJob() {
	assert(canStartNextJob());
	jupeInProgress = &getJupeInputLink().pop();
	teteInProgress = &getTeteInputLink().pop();
	axeInProgress = &getAxeInputLink().pop();
}

void PistonAssemblyMachine::finishCurrentJob() {
	//assert(areLinksConnected() && jupeInProgress != 0 && teteInProgress != 0 && axeInProgress != 0);
	//Piston piston = new Piston(teteInProgress, jupeInProgress, axeInProgress);
	//teteInProgress = 0;
	//jupeInProgress = 0;
	//axeInProgress = 0;
	//getOutputLink().push(*piston);
}

inline MachineDataLink<PistonTete>& PistonAssemblyMachine::getTeteInputLink() {
	return getInputLink<PistonTete>(teteInputName);
}

inline MachineDataLink<PistonJupe>& PistonAssemblyMachine::getJupeInputLink() {
	return getInputLink<PistonJupe>(jupeInputName);
}

inline MachineDataLink<PistonAxe>& PistonAssemblyMachine::getAxeInputLink() {
	return getInputLink<PistonAxe>(axeInputName);
}

inline MachineDataLink<Piston>& PistonAssemblyMachine::getOutputLink() {
	return IMachine::getOutputLink<Piston>(outputName);
}

bool PistonAssemblyMachine::areLinksConnected() {
	return hasOutputLink(outputName)
		&& hasInputLink(jupeInputName)
		&& hasInputLink(teteInputName)
		&& hasInputLink(axeInputName);
}
