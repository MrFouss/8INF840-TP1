#include "MachineStartWorkEvent.h"

#include "IMachine.h"

MachineStartWorkEvent::MachineStartWorkEvent(float triggerTime, IMachine * machine) :
	MachineEvent(triggerTime, machine)
{}

void MachineStartWorkEvent::trigger() const { 
	machine->startWorkingCycle(); 
}
