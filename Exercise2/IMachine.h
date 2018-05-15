#pragma once

#include <map>
#include <cassert>
#include "Event.h"
#include "MachineLink.h"

template <typename T>
class MachineDataLink;

class IMachine {
public:

	IMachine(std::string name, float workTime, float breakProbability, float repairTime);
	virtual ~IMachine() = default;

	std::string getName() { return name; }

	void onLinkUpdated() { startWorkingCycle(); }

protected:

	virtual bool canStartNextWork() = 0;
	virtual void startNextWork() = 0;
	virtual void finishCurrentWork() = 0;

	void linkInput(std::string name, MachineLink& link);
	void linkOutput(std::string name, MachineLink& link);
	
	bool hasInputLink(std::string name);
	bool hasOutputLink(std::string name);

	template <class T>
	MachineDataLink<T>& getInputLink(const std::string name) {
		assert(hasInputLink(name));
		return dynamic_cast<MachineDataLink<T>&>(*inputLinks[name]);
	}

	template <class T>
	MachineDataLink<T>& getOutputLink(const std::string name) {
		assert(hasOutputLink(name));
		return dynamic_cast<MachineDataLink<T>&>(*outputLinks[name]);
	}

private:

	class MachineIsRepairedEvent : public Event {
	public:
		MachineIsRepairedEvent(float triggerTime, IMachine* machine) :
			Event(triggerTime), machine(machine) {}

		virtual ~MachineIsRepairedEvent() = default;

		virtual void trigger() const { machine->repairMachine();}

	private:
		IMachine* machine;
	};

	class MachineFinishWorkEvent : public Event {
	public:
		MachineFinishWorkEvent(float triggerTime, IMachine* machine) :
			Event(triggerTime), machine(machine) {}

		virtual ~MachineFinishWorkEvent() = default;

		virtual void trigger() const { machine->endWorkingCycle(); }

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

