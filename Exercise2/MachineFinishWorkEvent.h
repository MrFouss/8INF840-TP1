#pragma once

#include "MachineEvent.h"

class IMachine;

class MachineFinishWorkEvent : public MachineEvent {
public:
	MachineFinishWorkEvent(const MachineFinishWorkEvent&) = default;
	MachineFinishWorkEvent(float triggerTime, IMachine& machine) :
		MachineEvent(triggerTime, machine)
	{}
	virtual ~MachineFinishWorkEvent() = default;

	void trigger() const override;
	Event* clone() const override { return new MachineFinishWorkEvent(*this); }
};
