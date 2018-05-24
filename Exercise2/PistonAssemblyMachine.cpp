#include "PistonAssemblyMachine.h"

#include "EventManager.h"
#include "LogEvent.h"

const std::string PistonAssemblyMachine::skirtInputName = "PistonAssemblyMachineskirtInput";
const std::string PistonAssemblyMachine::axisInputName = "PistonAssemblyMachineAxisInput";
const std::string PistonAssemblyMachine::headInputName = "PistonAssemblyMachineHeadInput";
const std::string PistonAssemblyMachine::outputName = "PistonAssemblyMachineOutput";

PistonAssemblyMachine::PistonAssemblyMachine(std::string name, float workTime, float breakProbability, float repairTime) :
	IMachine(name, workTime, breakProbability, repairTime),
	headInProgress(0),
	skirtInProgress(0),
	axisInProgress(0) 
{}

PistonAssemblyMachine::~PistonAssemblyMachine() {
	if (headInProgress != 0) {
		delete headInProgress;
	}
	if (skirtInProgress != 0) {
		delete skirtInProgress;
	}
	if (axisInProgress != 0) {
		delete axisInProgress;
	}
}

void PistonAssemblyMachine::linkskirtInput(MachineDataLink<PistonSkirt>* input) {
	linkInput(skirtInputName, input); 
}

void PistonAssemblyMachine::linkAxisInput(MachineDataLink<PistonAxis>* input) { 
	linkInput(axisInputName, input); 
}

void PistonAssemblyMachine::linkHeadInput(MachineDataLink<PistonHead>* input) { 
	linkInput(headInputName, input);
}

void PistonAssemblyMachine::linkOutput(MachineDataLink<Piston>* output) {
	IMachine::linkOutput(outputName, output);
}

bool PistonAssemblyMachine::canStartNextJob() {
	return areLinksConnected() 
		&& !getHeadInputLink()->isEmpty() 
		&& !getAxisInputLink()->isEmpty()
		&& !getskirtInputLink()->isEmpty();
}

void PistonAssemblyMachine::startNextJob() {
	assert(canStartNextJob());
	skirtInProgress = getskirtInputLink()->pop();
	headInProgress = getHeadInputLink()->pop();
	axisInProgress = getAxisInputLink()->pop();
}

void PistonAssemblyMachine::finishCurrentJob() {
	assert(areLinksConnected() && skirtInProgress != 0 && headInProgress != 0 && axisInProgress != 0);
	Piston* piston = new Piston(headInProgress, skirtInProgress, axisInProgress);
	headInProgress = 0;
	skirtInProgress = 0;
	axisInProgress = 0;
	getOutputLink()->push(piston);
	EventManager& em = EventManager::getInstance();
	em.addEvent(new LogEvent(em.getTime(), getName() + " assembled a piston"));
}

MachineDataLink<PistonHead>* PistonAssemblyMachine::getHeadInputLink() {
	return getInputLink<PistonHead>(headInputName);
}

MachineDataLink<PistonSkirt>* PistonAssemblyMachine::getskirtInputLink() {
	return getInputLink<PistonSkirt>(skirtInputName);
}

MachineDataLink<PistonAxis>* PistonAssemblyMachine::getAxisInputLink() {
	return getInputLink<PistonAxis>(axisInputName);
}

MachineDataLink<Piston>* PistonAssemblyMachine::getOutputLink() {
	return IMachine::getOutputLink<Piston>(outputName);
}

bool PistonAssemblyMachine::areLinksConnected() {
	return hasOutputLink(outputName)
		&& hasInputLink(skirtInputName)
		&& hasInputLink(headInputName)
		&& hasInputLink(axisInputName);
}
