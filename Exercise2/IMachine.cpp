#include "IMachine.h"

#include "EventManager.h"
#include <assert.h>

void IMachine::startWorkingCycle() {
	if (!isBroken && !isWorking && canStartNextWork()) {
		EventManager& em = EventManager::getInstance();
		if (breakProbability > (float)std::rand() / (RAND_MAX - 1)) {
			isBroken = true;
			em.addEvent(new MachineIsRepairedEvent(em.getTime() + repairTime, this));
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
}

void IMachine::endWorkingCycle() {
	assert(!isBroken && isWorking);
	isWorking = false;
	finishCurrentWork();
	startWorkingCycle();
}
