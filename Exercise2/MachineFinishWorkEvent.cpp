#include "MachineFinishWorkEvent.h"

#include "IMachine.h"

MachineFinishWorkEvent::MachineFinishWorkEvent(float triggerTime, IMachine * machine) :
	MachineEvent(triggerTime, machine)
{}

void MachineFinishWorkEvent::trigger() const { 
	machine->endWorkingCycle(); 
}
