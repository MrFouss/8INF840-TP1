#include "MachineStartWorkEvent.h"

#include "IMachine.h"

void MachineStartWorkEvent::trigger() const { machine.startWorkingCycle(); }
