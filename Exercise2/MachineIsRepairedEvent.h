#pragma once

#include "MachineEvent.h"

class IMachine;

class MachineIsRepairedEvent : public MachineEvent {
public:
	MachineIsRepairedEvent(const MachineIsRepairedEvent&) = default;
	MachineIsRepairedEvent(float triggerTime, IMachine& machine) :
		MachineEvent(triggerTime, machine) 
	{}
	virtual ~MachineIsRepairedEvent() = default;

	void trigger() const override;
	Event* clone() const override { return new MachineIsRepairedEvent(*this); }
};

