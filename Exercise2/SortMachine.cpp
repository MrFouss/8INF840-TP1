#include "SortMachine.h"

#include "MachineDataLink.h"
#include "EventManager.h"
#include "LogEvent.h"
#include <iostream>
#include <string>

const std::string SortMachine::skirtOutputName = "SortMachineskirtOutput";
const std::string SortMachine::axisOutputName = "SortMachineAxisOutput";
const std::string SortMachine::headOutputName = "SortMachineHeadOutput";
const std::string SortMachine::inputName = "SortMachineInput";

SortMachine::SortMachine(std::string name, float workTime, float breakProbability, float repairTime) :
	IMachine(name, workTime, breakProbability, repairTime),
	workInProgress(0) 
{}

SortMachine::~SortMachine() {
	if (workInProgress != 0) {
		delete workInProgress;
	}
}

void SortMachine::linkskirtOutput(MachineDataLink<PistonSkirt>* output) { linkOutput(skirtOutputName, output); }

void SortMachine::linkAxisOutput(MachineDataLink<PistonAxis>* output) { linkOutput(axisOutputName, output); }

void SortMachine::linkHeadOutput(MachineDataLink<PistonHead>* output) { linkOutput(headOutputName, output); }

void SortMachine::linkInput(MachineDataLink<Machineable>* input) { IMachine::linkInput(inputName, input); }

bool SortMachine::canStartNextJob() {
	return areLinksConnected() && !getInputLink()->isEmpty() && workInProgress == 0;
}

void SortMachine::startNextJob() {
	assert(canStartNextJob());
	workInProgress = getInputLink()->pop();
}

void SortMachine::finishCurrentJob() {
	assert(areLinksConnected() && workInProgress != 0);

	std::string message = getName() + " sorted a ";

	if (dynamic_cast<PistonAxis*>(workInProgress) != 0) {
		getAxisOutputLink()->push(dynamic_cast<PistonAxis*>(workInProgress));
		message += "axis";
	}
	else if (dynamic_cast<PistonSkirt*>(workInProgress) != 0) {
		getskirtOutputLink()->push(dynamic_cast<PistonSkirt*>(workInProgress));
		message += "skirt";
	}
	else if (dynamic_cast<PistonHead*>(workInProgress) != 0) {
		getHeadOutputLink()->push(dynamic_cast<PistonHead*>(workInProgress));
		message += "head";
	}
	else {
		std::cerr << getName() << " : Unrecognized type" << std::endl;
		std::exit(1);
	}

	EventManager& em = EventManager::getInstance();
	em.addEvent(new LogEvent(em.getTime(), message));
	workInProgress = 0;
}

MachineDataLink<PistonHead>* SortMachine::getHeadOutputLink() {
	return getOutputLink<PistonHead>(headOutputName);
}

MachineDataLink<PistonSkirt>* SortMachine::getskirtOutputLink() {
	return getOutputLink<PistonSkirt>(skirtOutputName);
}

MachineDataLink<PistonAxis>* SortMachine::getAxisOutputLink() {
	return getOutputLink<PistonAxis>(axisOutputName);
}

MachineDataLink<Machineable>* SortMachine::getInputLink() {
	return IMachine::getInputLink<Machineable>(inputName);
}

inline bool SortMachine::areLinksConnected() {
	return hasInputLink(inputName)
		&& hasOutputLink(skirtOutputName)
		&& hasOutputLink(headOutputName)
		&& hasOutputLink(axisOutputName);
}
