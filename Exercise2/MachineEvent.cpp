#include "MachineEvent.h"

#include <cassert>

#include "IMachine.h"

MachineEvent::MachineEvent(float triggerTime, IMachine * machine) : 
	Event(triggerTime),
	machine(machine) 
{
	assert(machine != 0);
}
