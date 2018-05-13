#pragma once

#include "IMachine.h"
#include "PistonPieceType.h"
#include "PistonPiece.h"
#include "MachineLink.h"

template <PistonPieceType type>
class PistonPieceMachine : public IMachine {
public:
	typedef PistonPiece<type> Piece;

	PistonPieceMachine(std::string name, float workTime, float breakProbability, float repairTime) :
		IMachine(name, workTime, breakProbability, repairTime),
		workInProgress(NULL),
		inputLink(NULL),
		outputLink(NULL) {}

	virtual ~PistonPieceMachine() = default;

	void linkInput(MachineLink<Piece>* input) {
		assert(input != NULL);
		inputLink = input;
		input->setOutputMachine(this);
	}

	void linkOutput(MachineLink<Piece>* output) {
		assert(output != NULL);
		outputLink = output;
		output->setInputMachine(this);
	}

protected:
	virtual bool canStartNextWork() { 
		assert(inputLink != NULL);
		return !inputLink->isEmpty() && workInProgress == NULL; 
	}

	virtual void startNextWork() {
		assert(canStartNextWork());
		workInProgress = inputLink->pop();
	}

	virtual void finishCurrentWork() {
		assert(outputLink != NULL && workInProgress != NULL);
		workInProgress->setMachined();
		outputLink->push(workInProgress);
		workInProgress = NULL;
	}

private:

	Piece* workInProgress;

	MachineLink<Piece>* inputLink;
	MachineLink<Piece>* outputLink;
};

