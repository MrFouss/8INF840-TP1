#include "PistonAssemblyMachine.h"

#include "EventManager.h"
#include "LogEvent.h"

const std::string PistonAssemblyMachine::jupeInputName = "PistonAssemblyMachineJupeInput";
const std::string PistonAssemblyMachine::axeInputName = "PistonAssemblyMachineAxeInput";
const std::string PistonAssemblyMachine::teteInputName = "PistonAssemblyMachineTeteInput";
const std::string PistonAssemblyMachine::outputName = "PistonAssemblyMachineOutput";

PistonAssemblyMachine::~PistonAssemblyMachine() {
	if (teteInProgress != 0) {
		delete teteInProgress;
	}
	if (jupeInProgress != 0) {
		delete jupeInProgress;
	}
	if (axeInProgress != 0) {
		delete axeInProgress;
	}
}

bool PistonAssemblyMachine::canStartNextJob() {
	return areLinksConnected() 
		&& !getTeteInputLink()->isEmpty() 
		&& !getAxeInputLink()->isEmpty() 
		&& !getJupeInputLink()->isEmpty();
}

void PistonAssemblyMachine::startNextJob() {
	assert(canStartNextJob());
	jupeInProgress = getJupeInputLink()->pop();
	teteInProgress = getTeteInputLink()->pop();
	axeInProgress = getAxeInputLink()->pop();
}

void PistonAssemblyMachine::finishCurrentJob() {
	assert(areLinksConnected() && jupeInProgress != 0 && teteInProgress != 0 && axeInProgress != 0);
	Piston* piston = new Piston(teteInProgress, jupeInProgress, axeInProgress);
	teteInProgress = 0;
	jupeInProgress = 0;
	axeInProgress = 0;
	getOutputLink()->push(piston);
	EventManager& em = EventManager::getInstance();
	em.addEvent(new LogEvent(em.getTime(), getName() + " assembled a piston"));
}

inline MachineDataLink<PistonTete>* PistonAssemblyMachine::getTeteInputLink() {
	return getInputLink<PistonTete>(teteInputName);
}

inline MachineDataLink<PistonJupe>* PistonAssemblyMachine::getJupeInputLink() {
	return getInputLink<PistonJupe>(jupeInputName);
}

inline MachineDataLink<PistonAxe>* PistonAssemblyMachine::getAxeInputLink() {
	return getInputLink<PistonAxe>(axeInputName);
}

inline MachineDataLink<Piston>* PistonAssemblyMachine::getOutputLink() {
	return IMachine::getOutputLink<Piston>(outputName);
}

bool PistonAssemblyMachine::areLinksConnected() {
	return hasOutputLink(outputName)
		&& hasInputLink(jupeInputName)
		&& hasInputLink(teteInputName)
		&& hasInputLink(axeInputName);
}
