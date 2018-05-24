#pragma once

#include "PistonPiece.h"

class Piston {
public:
	Piston(const PistonHead* head, const PistonSkirt* skirt, const PistonAxis* axis);
	virtual ~Piston();

private:

	const PistonHead* head;
	const PistonSkirt* skirt;
	const PistonAxis* axis;
};

