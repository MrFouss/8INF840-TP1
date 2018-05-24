#pragma once

#include "PistonPiece.h"

class Piston {
public:
	Piston(const PistonTete* tete, const PistonJupe* jupe, const PistonAxe* axe);
	virtual ~Piston();

private:

	const PistonTete* tete;
	const PistonJupe* jupe;
	const PistonAxe* axe;
};

