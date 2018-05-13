#pragma once

#include "Event.h"

class IMachine {
public:

	IMachine(std::string name, float workTime, float breakProbability, float repairTime) :
		name(name), 
		workTime(workTime),
		breakProbability(breakProbability),
		repairTime(repairTime), 
		isBroken(false), 
		isWorking(false) {}

	virtual ~IMachine() = default;

	std::string getName() { return name; }

	void onLinkUpdated() { startWorkingCycle(); }

protected:

	virtual bool canStartNextWork() = 0;
	virtual void startNextWork() = 0;
	virtual void finishCurrentWork() = 0;

private:

	class MachineIsRepairedEvent : public Event {
	public:
		MachineIsRepairedEvent(float triggerTime, IMachine* machine) :
			Event(triggerTime), machine(machine) {}

		virtual ~MachineIsRepairedEvent() = default;

		virtual void trigger() const {
			machine->repairMachine();
		}

		virtual std::string log() const {
			return "Repaired machine " + machine->getName() + '\n';
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

		virtual std::string log() const {
			return "Finished work on machine " + machine->getName() + '\n';
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
};

