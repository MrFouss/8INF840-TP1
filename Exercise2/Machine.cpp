#include "Machine.h"

#include "EventManager.h"

Machine::Machine(float workingTime, float fixingTime, float breakDownOdds) :
	inputQueue(NULL),
	outputQueue(NULL),
	workInProgress(NULL),
	working(false),
	brokenDown(false),
	workingTime(workingTime),
	fixingTime(fixingTime),
	breakDownOdds(breakDownOdds)
{}

void Machine::setInputQueue(Queue<Machineable*>* inputQueue) {
	this->inputQueue = inputQueue;
}

void Machine::setOutputQueue(Queue<Machineable*>* outputQueue) {
	this->outputQueue = outputQueue;
}

void Machine::processNext() {
	assert(inputQueue != NULL);
	if (!inputQueue->isEmpty() && !working && !brokenDown) {
		workInProgress = inputQueue->pop();
		working = true;
		EventManager& em = EventManager::getInstance();
		if (breakDownOdds > (float)std::rand() / RAND_MAX) {
			brokenDown = true;
			em.addEvent(new MachineFixEvent(em.getTime() + fixingTime, this));
			em.addEvent(new MachineFinishWorkEvent(em.getTime() + workingTime + fixingTime, this));
		}
		else {
			em.addEvent(new MachineFinishWorkEvent(em.getTime() + workingTime, this));
		}
	}
}

bool Machine::canProcessNext() {
	return !working && !brokenDown;
}

void Machine::finishProcess() {
	assert(working && workInProgress != NULL && outputQueue != NULL);
	outputQueue->push(workInProgress);
	workInProgress = NULL;
	working = false;
}

void Machine::fixMachine() {
	assert(brokenDown);
	brokenDown = false;
}

Machine::MachineFinishWorkEvent::MachineFinishWorkEvent(float triggerTime, Machine * machine) : 
	Event(triggerTime), 
	machine(machine) 
{}

void Machine::MachineFinishWorkEvent::trigger() const {
	machine->finishProcess();
}

std::string Machine::MachineFinishWorkEvent::log() const {
	return "Finish work";
}

Machine::MachineFixEvent::MachineFixEvent(float triggerTime, Machine * machine) :
	Event(triggerTime),
	machine(machine) 
{}

void Machine::MachineFixEvent::trigger() const {
	machine->fixMachine();
}

std::string Machine::MachineFixEvent::log() const {
	return "Fix machine";
}
