#include "Piston.h"

#include <assert.h>

Piston::Piston(const PistonTete* tete, const PistonJupe* jupe, const PistonAxe* axe) :
	tete(tete),
	jupe(jupe),
	axe(axe)
{
	assert(tete->isMachined() && jupe->isMachined() && axe->isMachined());
}

Piston::~Piston() {
	delete tete;
	delete jupe;
	delete axe;
}
