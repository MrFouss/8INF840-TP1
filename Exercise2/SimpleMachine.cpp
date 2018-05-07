#include "SimpleMachine.h"

#include "EventManager.h"
#include "MachineLink.h"

SimpleMachine::SimpleMachine(std::string name, float workingTime, float fixingTime, float breakDownOdds) :
	IMachine(name),
	inputLink(NULL),
	outputLink(NULL),
	workInProgress(NULL),
	working(false),
	brokenDown(false),
	workingTime(workingTime),
	fixingTime(fixingTime),
	breakDownOdds(breakDownOdds) {
}

void SimpleMachine::tryProcessNext() {
	if (!inputLink->isEmpty() && !working && !brokenDown) {
		workInProgress = inputLink->pop();
		working = true;
		EventManager& em = EventManager::getInstance();
		if (breakDownOdds > (float)std::rand() / RAND_MAX) {
			brokenDown = true;
			em.addEvent(new MachineFixEvent(em.getTime() + fixingTime, this));
		}
		else {
			em.addEvent(new MachineFinishWorkEvent(em.getTime() + workingTime, this));
		}
	}
}

void SimpleMachine::setInputLink(MachineLink * inputLink) {
	this->inputLink = inputLink;
	inputLink->setOutputMachine(this);
}

void SimpleMachine::setOutputLink(MachineLink * outputLink) {
	this->outputLink = outputLink;
	outputLink->setInputMachine(this);
}

void SimpleMachine::onInputUpdate() {
	tryProcessNext();
}

void SimpleMachine::onOutputUpdate() {}

void SimpleMachine::finishProcess() {
	if (working) {
		outputLink->push(this->workInProgress);
		workInProgress = NULL;
		working = false;

		tryProcessNext();
	}
}

void SimpleMachine::fixMachine() {
	if (brokenDown) {
		brokenDown = false;
		if (working) {
			EventManager& em = EventManager::getInstance();
			em.addEvent(new MachineFinishWorkEvent(em.getTime() + workingTime, this));
		}
	}
}
