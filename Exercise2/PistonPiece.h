#pragma once

#include "Machineable.h"

enum PistonPieceType { TETE, JUPE, AXE };

template<PistonPieceType type>
class PistonPiece : public Machineable {
public:
	PistonPiece() = default;
	virtual ~PistonPiece() = default;
};

typedef PistonPiece<PistonPieceType::TETE> PistonTete;
typedef PistonPiece<PistonPieceType::JUPE> PistonJupe;
typedef PistonPiece<PistonPieceType::AXE> PistonAxe;
