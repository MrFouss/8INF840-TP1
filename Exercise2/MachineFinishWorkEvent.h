#pragma once

#include "MachineEvent.h"

class MachineFinishWorkEvent : public MachineEvent {
public:
	MachineFinishWorkEvent(float triggerTime, IMachine* machine);
	virtual ~MachineFinishWorkEvent() = default;

	void trigger() const override;
};
