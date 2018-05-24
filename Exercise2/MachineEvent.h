#pragma once

#include "Event.h"

class IMachine;

class MachineEvent : public Event {
public:
	MachineEvent(float triggerTime, IMachine* machine);
	virtual ~MachineEvent() = default;

protected:
	IMachine* machine;
};

