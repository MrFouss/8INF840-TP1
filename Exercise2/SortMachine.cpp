#include "SortMachine.h"


const std::string SortMachine::jupeOutputName = "SortMachineJupeOutput";
const std::string SortMachine::axeOutputName = "SortMachineAxeOutput";
const std::string SortMachine::teteOutputName = "SortMachineTeteOutput";
const std::string SortMachine::inputName = "SortMachineInput";

bool SortMachine::canStartNextWork() {
	return areLinksConnected() && !getInputLink().isEmpty() && workInProgress == NULL;
}

void SortMachine::startNextWork() {
	assert(canStartNextWork());
	workInProgress = &getInputLink().pop();
}

void SortMachine::finishCurrentWork() {
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
	em.addEvent(new LogEvent(em.getTime(), message));
	workInProgress = NULL;
}

inline MachineDataLink<PistonTete>& SortMachine::getTeteOutputLink() {
	return getOutputLink<PistonTete>(teteOutputName);
}

inline MachineDataLink<PistonJupe>& SortMachine::getJupeOutputLink() {
	return getOutputLink<PistonJupe>(jupeOutputName);
}

inline MachineDataLink<PistonAxe>& SortMachine::getAxeOutputLink() {
	return getOutputLink<PistonAxe>(axeOutputName);
}

inline MachineDataLink<Machineable>& SortMachine::getInputLink() {
	return IMachine::getInputLink<Machineable>(inputName);
}

inline bool SortMachine::areLinksConnected() {
	return hasInputLink(inputName)
		&& hasOutputLink(jupeOutputName)
		&& hasOutputLink(teteOutputName)
		&& hasOutputLink(axeOutputName);
}
