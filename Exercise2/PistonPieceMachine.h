#pragma once

#include "IMachine.h"
#include "PistonPieceType.h"
#include "PistonPiece.h"
#include "MachineDataLink.h"

template <PistonPieceType type>
class PistonPieceMachine : public IMachine {
public:
	typedef PistonPiece<type> Piece;

	PistonPieceMachine(std::string name, float workTime, float breakProbability, float repairTime) :
		IMachine(name, workTime, breakProbability, repairTime),
		workInProgress(NULL) {}

	virtual ~PistonPieceMachine() = default;

	void linkOutput(MachineDataLink<Piece>* output) {
		IMachine::linkOutput(outputLinkName, output);
	}

	void linkInput(MachineDataLink<Piece>* input) {
		IMachine::linkInput(inputLinkName, input);
	}

protected:
	virtual bool canStartNextWork() { 
		assert(areLinksConnected());
		return !getInputLink()->isEmpty() && workInProgress == NULL; 
	}

	virtual void startNextWork() {
		assert(canStartNextWork());
		workInProgress = getInputLink()->pop();
	}

	virtual void finishCurrentWork() {
		assert(areLinksConnected() && workInProgress != NULL);
		workInProgress->setMachined();
		getOutputLink()->push(workInProgress);
		workInProgress = NULL;
	}

private:

	MachineDataLink<Piece>* getOutputLink() {
		return (MachineDataLink<Piece>*)IMachine::getOutputLink(outputLinkName);
	}

	MachineDataLink<Piece>* getInputLink() {
		return (MachineDataLink<Piece>*)IMachine::getInputLink(inputLinkName);
	}

	bool areLinksConnected() {
		return hasInputLink(inputLinkName)
			&& hasOutputLink(outputLinkName);
	}

	Piece* workInProgress;

	static const std::string inputLinkName;
	static const std::string outputLinkName;
};

template <PistonPieceType type>
const std::string PistonPieceMachine<type>::inputLinkName = "PistonPieceMachineInput";

template <PistonPieceType type>
const std::string PistonPieceMachine<type>::outputLinkName = "PistonPieceMachineOutput";