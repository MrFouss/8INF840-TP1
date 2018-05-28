#pragma once

#include "MachineEvent.h"

class MachineIsRepairedEvent : public MachineEvent {
public:
	MachineIsRepairedEvent(float triggerTime, IMachine* machine);
	virtual ~MachineIsRepairedEvent() = default;

	void trigger() const override;
};

