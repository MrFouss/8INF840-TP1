#include "IMachine.h"

#include "EventManager.h"
#include "LogEvent.h"
#include "MachineDataLink.h"

IMachine::IMachine(std::string name, float workTime, float breakProbability, float minRepairTime, float maxRepairTime) :
	name(name),
	workTime(workTime),
	breakProbability(breakProbability),
	minRepairTime(minRepairTime),
	maxRepairTime(maxRepairTime),
	isBroken(false),
	isWorking(false),
	inputLinks(),
	outputLinks() 
{}

std::string IMachine::getName() {
	return name;
}

void IMachine::onInputLinkUpdated() {
	// if the machine is asleep (waiting for new inputs)
	if (!isWorking && !isBroken) {
		EventManager* em = EventManager::getInstance();
		em->addEvent(new MachineStartWorkEvent(em->getTime(), this));
	}
}

void IMachine::linkInput(std::string name, MachineLink* link) {
	inputLinks[name] = link;
	link->setOutputMachine(this);
}

void IMachine::linkOutput(std::string name, MachineLink* link) {
	outputLinks[name] = link;
	link->setInputMachine(this);
}

bool IMachine::hasInputLink(std::string name) {
	return inputLinks.find(name) != inputLinks.end();
}

bool IMachine::hasOutputLink(std::string name) {
	return outputLinks.find(name) != outputLinks.end();
}

void IMachine::startWorkingCycle() {
	// if not already in a working cycle and can start a new job
	if (!isBroken && !isWorking && canStartNextJob()) {
		EventManager* em = EventManager::getInstance();
		// check if the machine breaks before executing the job
		if (breakProbability > (float)std::rand() / (RAND_MAX - 1)) {
			// the machine breaks, it will execute its job after its repair
			isBroken = true;
			float repairTime = minRepairTime + ((float)(std::rand() / RAND_MAX)) * (maxRepairTime - minRepairTime);
			em->addEvent(new LogEvent(em->getTime(), getName() + " broke"));
			em->addEvent(new MachineIsRepairedEvent(em->getTime() + repairTime, this));
		}
		else {
			// the machine does not break, it executes its job
			isWorking = true; 
			startNextJob();
			em->addEvent(new MachineFinishWorkEvent(em->getTime() + workTime, this));
		}
	}
}

void IMachine::repairMachine() {
	assert(isBroken && !isWorking && canStartNextJob());
	isBroken = false;
	isWorking = true;
	startNextJob();
	EventManager* em = EventManager::getInstance();
	em->addEvent(new LogEvent(em->getTime(), getName() + " was repaired"));
	em->addEvent(new MachineFinishWorkEvent(em->getTime() + workTime, this));
}

void IMachine::endWorkingCycle() {
	assert(!isBroken && isWorking);
	isWorking = false;
	finishCurrentJob();
	EventManager* em = EventManager::getInstance();
	em->addEvent(new MachineStartWorkEvent(em->getTime(), this));
}
