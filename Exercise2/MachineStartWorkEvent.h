#pragma once

#include "MachineEvent.h"

class MachineStartWorkEvent : public MachineEvent {
public:
	MachineStartWorkEvent(float triggerTime, IMachine* machine);
	virtual ~MachineStartWorkEvent() = default;

	void trigger() const override;
};

