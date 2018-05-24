#include "MachineIsRepairedEvent.h"

#include "IMachine.h"

MachineIsRepairedEvent::MachineIsRepairedEvent(float triggerTime, IMachine * machine) :
	MachineEvent(triggerTime, machine) {
}

void MachineIsRepairedEvent::trigger() const { machine->repairMachine(); }
