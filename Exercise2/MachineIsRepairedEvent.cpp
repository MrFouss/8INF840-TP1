#include "MachineIsRepairedEvent.h"

#include "IMachine.h"

void MachineIsRepairedEvent::trigger() const { machine.repairMachine(); }
