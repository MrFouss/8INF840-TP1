#include "SortMachine.h"

#include "MachineDataLink.h"
#include "EventManager.h"
#include "LogEvent.h"
#include <iostream>
#include <string>

const std::string SortMachine::jupeOutputName = "SortMachineJupeOutput";
const std::string SortMachine::axeOutputName = "SortMachineAxeOutput";
const std::string SortMachine::teteOutputName = "SortMachineTeteOutput";
const std::string SortMachine::inputName = "SortMachineInput";

void SortMachine::linkJupeOutput(MachineDataLink<PistonJupe>& output) { linkOutput(jupeOutputName, output); }

void SortMachine::linkAxeOutput(MachineDataLink<PistonAxe>& output) { linkOutput(axeOutputName, output); }

void SortMachine::linkTeteOutput(MachineDataLink<PistonTete>& output) { linkOutput(teteOutputName, output); }

void SortMachine::linkInput(MachineDataLink<Machineable>& input) { IMachine::linkInput(inputName, input); }

bool SortMachine::canStartNextJob() {
	return areLinksConnected() && !getInputLink().isEmpty() && workInProgress == NULL;
}

void SortMachine::startNextJob() {
	assert(canStartNextJob());
	workInProgress = &getInputLink().pop();
}

void SortMachine::finishCurrentJob() {
	assert(areLinksConnected() && workInProgress != NULL);

	std::string message = getName() + " sorted a ";

	if (dynamic_cast<PistonAxe*>(workInProgress) != NULL) {
		getAxeOutputLink().push(dynamic_cast<PistonAxe&>(*workInProgress));
		message += "axe";
	}
	else if (dynamic_cast<PistonJupe*>(workInProgress) != NULL) {
		getJupeOutputLink().push(dynamic_cast<PistonJupe&>(*workInProgress));
		message += "jupe";
	}
	else if (dynamic_cast<PistonTete*>(workInProgress) != NULL) {
		getTeteOutputLink().push(dynamic_cast<PistonTete&>(*workInProgress));
		message += "tete";
	}
	else {
		std::cerr << getName() << " : Unrecognized type" << std::endl;
		std::exit(1);
	}

	EventManager& em = EventManager::getInstance();
	em.addEvent(LogEvent(em.getTime(), message));
	workInProgress = NULL;
}

MachineDataLink<PistonTete>& SortMachine::getTeteOutputLink() {
	return getOutputLink<PistonTete>(teteOutputName);
}

MachineDataLink<PistonJupe>& SortMachine::getJupeOutputLink() {
	return getOutputLink<PistonJupe>(jupeOutputName);
}

MachineDataLink<PistonAxe>& SortMachine::getAxeOutputLink() {
	return getOutputLink<PistonAxe>(axeOutputName);
}

MachineDataLink<Machineable>& SortMachine::getInputLink() {
	return IMachine::getInputLink<Machineable>(inputName);
}

inline bool SortMachine::areLinksConnected() {
	return hasInputLink(inputName)
		&& hasOutputLink(jupeOutputName)
		&& hasOutputLink(teteOutputName)
		&& hasOutputLink(axeOutputName);
}
