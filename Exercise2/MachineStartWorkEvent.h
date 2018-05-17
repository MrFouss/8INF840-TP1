#pragma once

#include "MachineEvent.h"

class IMachine;

class MachineStartWorkEvent : public MachineEvent {

public:
	MachineStartWorkEvent(const MachineStartWorkEvent&) = default;
	MachineStartWorkEvent(float triggerTime, IMachine& machine) :
		MachineEvent(triggerTime, machine) 
	{}
	virtual ~MachineStartWorkEvent() = default;

	void trigger() const override;
	Event* clone() const override { return new MachineStartWorkEvent(*this); }
};

