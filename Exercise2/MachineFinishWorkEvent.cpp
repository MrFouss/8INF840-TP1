#include "MachineFinishWorkEvent.h"

#include "IMachine.h"

void MachineFinishWorkEvent::trigger() const { machine.endWorkingCycle(); }
