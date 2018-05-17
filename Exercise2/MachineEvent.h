#pragma once

#include "Event.h"

class IMachine;

class MachineEvent : public Event {
public:
	MachineEvent(const MachineEvent&) = default;
	MachineEvent(float triggerTime, IMachine& machine) :
		Event(triggerTime), machine(machine) {
	}
	virtual ~MachineEvent() = default;

protected:
	IMachine& machine;
};

