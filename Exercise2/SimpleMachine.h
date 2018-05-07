#pragma once

#include "IMachine.h"
#include "Event.h"

class MachineLink;
class Machineable;

class SimpleMachine : public IMachine {
public:
	SimpleMachine(std::string name, float workingTime, float fixingTime, float breakDownOdds);

	virtual ~SimpleMachine() = default;

	virtual void tryProcessNext();

	void setInputLink(MachineLink*);
	void setOutputLink(MachineLink*);

	virtual void onInputUpdate();
	virtual void onOutputUpdate();

	class MachineFinishWorkEvent : public Event {
	public:
		MachineFinishWorkEvent(float triggerTime, SimpleMachine* machine) :
			Event(triggerTime),
			machine(machine) 
		{}

		virtual ~MachineFinishWorkEvent() = default;

		virtual void trigger() const {
			machine->finishProcess();
		}

		virtual std::string log() const {
			return "Finished work on machine " + machine->getName();
		}

	private:
		SimpleMachine * machine;
	};

	class MachineFixEvent : public Event {
	public:
		MachineFixEvent(float triggerTime, SimpleMachine* machine) :
			Event(triggerTime),
			machine(machine) {
		}

		virtual ~MachineFixEvent() = default;

		virtual void trigger() const {
			machine->fixMachine();
		}

		virtual std::string log() const {
			return "Fixed machine " + machine->getName();
		}

	private:
		SimpleMachine * machine;
	};

private:

	void finishProcess();
	void fixMachine();

	MachineLink* outputLink;
	MachineLink* inputLink;

	Machineable* workInProgress;

	bool working;
	bool brokenDown;

	const float workingTime;
	const float fixingTime;
	const float breakDownOdds;
};

