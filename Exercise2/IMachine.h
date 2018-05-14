#pragma once

#include <map>
#include <cassert>
#include "Event.h"
#include "MachineLink.h"

class IMachine {
public:

	IMachine(std::string name, float workTime, float breakProbability, float repairTime) :
		name(name), 
		workTime(workTime),
		breakProbability(breakProbability),
		repairTime(repairTime), 
		isBroken(false), 
		isWorking(false),
		inputLinks(),
		outputLinks() {}

	virtual ~IMachine() = default;

	std::string getName() { return name; }

	void onLinkUpdated() { startWorkingCycle(); }

protected:

	virtual bool canStartNextWork() = 0;
	virtual void startNextWork() = 0;
	virtual void finishCurrentWork() = 0;

	void linkInput(std::string name, MachineLink* link) {
		assert(link != NULL);
		inputLinks[name] = link;
		link->setOutputMachine(this);
	}

	void linkOutput(std::string name, MachineLink* link) {
		assert(link != NULL);
		outputLinks[name] = link;
		link->setInputMachine(this);
	}
	
	bool hasInputLink(std::string name) {
		return inputLinks.find(name) != inputLinks.end();
	}

	bool hasOutputLink(std::string name) {
		return outputLinks.find(name) != outputLinks.end();
	}

	MachineLink* getInputLink(std::string name) {
		assert(hasInputLink(name));
		return inputLinks[name];
	}

	MachineLink* getOutputLink(std::string name) {
		assert(hasOutputLink(name));
		return outputLinks[name];
	}

private:

	class MachineIsRepairedEvent : public Event {
	public:
		MachineIsRepairedEvent(float triggerTime, IMachine* machine) :
			Event(triggerTime), machine(machine) {}

		virtual ~MachineIsRepairedEvent() = default;

		virtual void trigger() const {
			machine->repairMachine();
		}

	private:
		IMachine* machine;
	};

	class MachineFinishWorkEvent : public Event {
	public:
		MachineFinishWorkEvent(float triggerTime, IMachine* machine) :
			Event(triggerTime), machine(machine) {}

		virtual ~MachineFinishWorkEvent() = default;

		virtual void trigger() const {
			machine->endWorkingCycle();
		}

	private:
		IMachine* machine;
	};

	void startWorkingCycle();
	void repairMachine();
	void endWorkingCycle();

	std::string name;
	float workTime;
	float breakProbability;
	float repairTime;
	bool isBroken;
	bool isWorking;

	std::map<std::string, MachineLink*> inputLinks;
	std::map<std::string, MachineLink*> outputLinks;
};

