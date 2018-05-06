#pragma once

#include "PistonPiece.h"
#include "Machineable.h"

class Piston : public Machineable {
public:
	Piston(const PistonTete&, const PistonJupe&, const PistonAxe&);
	virtual ~Piston() = default;

private:

	const PistonTete& tete;
	const PistonJupe& jupe;
	const PistonAxe& axe;
};

