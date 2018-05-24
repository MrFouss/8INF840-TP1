#pragma once

#include "Machineable.h"

enum PistonPieceType { HEAD, SKIRT, AXIS };

template<PistonPieceType type>
class PistonPiece : public Machineable {
public:
	PistonPiece() = default;
	virtual ~PistonPiece() = default;
};

typedef PistonPiece<PistonPieceType::HEAD> PistonHead;
typedef PistonPiece<PistonPieceType::SKIRT> PistonSkirt;
typedef PistonPiece<PistonPieceType::AXIS> PistonAxis;
