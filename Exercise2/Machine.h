#pragma once

#include "Queue.h"
#include "Machineable.h"
#include "Event.h"
#include <iostream>

class Machine {
public:
	Machine(float workingTime, float fixingTime, float breakDownOdds);
	~Machine() = default;

	void setInputQueue(Queue<Machineable*>* inputQueue);
	void setOutputQueue(Queue<Machineable*>* outputQueue);

	void processNext();
	bool canProcessNext();

	class MachineFinishWorkEvent : public Event {
	public:
		MachineFinishWorkEvent(float triggerTime, Machine* machine);
		virtual ~MachineFinishWorkEvent() = default;

		virtual void trigger() const;
		virtual std::string log() const;
	private:
		Machine* machine;
	};

	class MachineFixEvent : public Event {
	public:
		MachineFixEvent(float triggerTime, Machine* machine);
		virtual ~MachineFixEvent() = default;

		virtual void trigger() const;
		virtual std::string log() const;

	private:
		Machine * machine;
	};

private:

	void finishProcess();
	void fixMachine();
	
	Queue<Machineable*>* inputQueue;
	Queue<Machineable*>* outputQueue;

	Machineable* workInProgress;

	bool working;
	bool brokenDown;
	
	const float workingTime;
	const float fixingTime;
	const float breakDownOdds;
};