#include "IMachine.h"

#include "EventManager.h"
#include <assert.h>
#include "LogEvent.h"

#include "MachineDataLink.h"
#include "MachineLink.h"

IMachine::IMachine(std::string name, float workTime, float breakProbability, float repairTime) :
	name(name),
	workTime(workTime),
	breakProbability(breakProbability),
	repairTime(repairTime),
	isBroken(false),
	isWorking(false),
	inputLinks(),
	outputLinks() {
}

void IMachine::linkInput(std::string name, MachineLink& link) {
	inputLinks[name] = &link;
	link.setOutputMachine(this);
}

void IMachine::linkOutput(std::string name, MachineLink& link) {
	outputLinks[name] = &link;
	link.setInputMachine(this);
}

bool IMachine::hasInputLink(std::string name) {
	return inputLinks.find(name) != inputLinks.end();
}

bool IMachine::hasOutputLink(std::string name) {
	return outputLinks.find(name) != outputLinks.end();
}

void IMachine::startWorkingCycle() {
	if (!isBroken && !isWorking && canStartNextWork()) {
		EventManager& em = EventManager::getInstance();
		if (breakProbability > (float)std::rand() / (RAND_MAX - 1)) {
			isBroken = true;
			em.addEvent(new MachineIsRepairedEvent(em.getTime() + repairTime, this));
			em.addEvent(new LogEvent(em.getTime(), getName() + " broke"));
		}
		else {
			isWorking = true; 
			startNextWork();
			em.addEvent(new MachineFinishWorkEvent(em.getTime() + workTime, this));
		}
	}
}

void IMachine::repairMachine() {
	assert(isBroken && !isWorking && canStartNextWork());
	isBroken = false;
	isWorking = true;
	startNextWork();
	EventManager& em = EventManager::getInstance();
	em.addEvent(new MachineFinishWorkEvent(em.getTime() + workTime, this));
	em.addEvent(new LogEvent(em.getTime(), getName() + " was repaired"));
}

void IMachine::endWorkingCycle() {
	assert(!isBroken && isWorking);
	isWorking = false;
	finishCurrentWork();
	// TODO send an event instead
	startWorkingCycle();
}
