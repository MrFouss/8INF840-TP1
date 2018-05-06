#include "Machineable.h"

Machineable::Machineable() : machined(false) {}

bool Machineable::isMachined() const {
	return machined;
}

void Machineable::setMachined() {
	machined = true;
}