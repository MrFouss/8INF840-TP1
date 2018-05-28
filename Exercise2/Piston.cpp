#include "Piston.h"

#include <assert.h>

Piston::Piston(const PistonHead* head, const PistonSkirt* skirt, const PistonAxis* axis) :
	head(head),
	skirt(skirt),
	axis(axis)
{
	assert(head->isMachined() && skirt->isMachined() && axis->isMachined());
}

Piston::~Piston() {
	delete head;
	delete skirt;
	delete axis;
}
