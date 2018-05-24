#include "PistonAssemblyMachine.h"

#include "EventManager.h"
#include "LogEvent.h"

const std::string PistonAssemblyMachine::jupeInputName = "PistonAssemblyMachineJupeInput";
const std::string PistonAssemblyMachine::axeInputName = "PistonAssemblyMachineAxeInput";
const std::string PistonAssemblyMachine::teteInputName = "PistonAssemblyMachineTeteInput";
const std::string PistonAssemblyMachine::outputName = "PistonAssemblyMachineOutput";

PistonAssemblyMachine::PistonAssemblyMachine(std::string name, float workTime, float breakProbability, float repairTime) :
	IMachine(name, workTime, breakProbability, repairTime),
	teteInProgress(0),
	jupeInProgress(0),
	axeInProgress(0) 
{}

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

void PistonAssemblyMachine::linkJupeInput(MachineDataLink<PistonJupe>* input) {
	linkInput(jupeInputName, input); 
}

void PistonAssemblyMachine::linkAxeInput(MachineDataLink<PistonAxe>* input) { 
	linkInput(axeInputName, input); 
}

void PistonAssemblyMachine::linkTeteInput(MachineDataLink<PistonTete>* input) { 
	linkInput(teteInputName, input);
}

void PistonAssemblyMachine::linkOutput(MachineDataLink<Piston>* output) {
	IMachine::linkOutput(outputName, output);
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

MachineDataLink<PistonTete>* PistonAssemblyMachine::getTeteInputLink() {
	return getInputLink<PistonTete>(teteInputName);
}

MachineDataLink<PistonJupe>* PistonAssemblyMachine::getJupeInputLink() {
	return getInputLink<PistonJupe>(jupeInputName);
}

MachineDataLink<PistonAxe>* PistonAssemblyMachine::getAxeInputLink() {
	return getInputLink<PistonAxe>(axeInputName);
}

MachineDataLink<Piston>* PistonAssemblyMachine::getOutputLink() {
	return IMachine::getOutputLink<Piston>(outputName);
}

bool PistonAssemblyMachine::areLinksConnected() {
	return hasOutputLink(outputName)
		&& hasInputLink(jupeInputName)
		&& hasInputLink(teteInputName)
		&& hasInputLink(axeInputName);
}
