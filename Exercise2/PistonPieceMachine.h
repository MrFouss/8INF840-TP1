#pragma once

#include "IMachine.h"

#include "PistonPiece.h"
#include "MachineDataLink.h"
#include "LogEvent.h"

// a machine that processes piston pieces (set them as "machined")
template <PistonPieceType type>
class PistonPieceMachine : public IMachine {
public:
	// the piece type this machine processes
	typedef PistonPiece<type> Piece;

	PistonPieceMachine(std::string name, float workTime, float breakProbability, float minRepairTime, float maxRepairTime) :
		IMachine(name, workTime, breakProbability, minRepairTime, maxRepairTime),
		workInProgress(0) {}

	virtual ~PistonPieceMachine() {
		if (workInProgress != 0) {
			delete workInProgress;
		}
	}

	void linkOutput(MachineDataLink<Piece>* output) {
		IMachine::linkOutput(outputLinkName, output);
	}

	void linkInput(MachineDataLink<Piece>* input) {
		IMachine::linkInput(inputLinkName, input);
	}

protected:

	bool canStartNextJob() override { 
		assert(areLinksConnected());
		return !getInputLink()->isEmpty() && workInProgress == 0; 
	}
	void startNextJob() override {
		assert(canStartNextJob());
		workInProgress = getInputLink()->pop();
	}

	void finishCurrentJob() override {
		assert(areLinksConnected() && workInProgress != 0);
		workInProgress->setMachined();
		getOutputLink()->push(workInProgress);
		workInProgress = 0;
		EventManager* em = EventManager::getInstance();
		em->addEvent(new LogEvent(em->getTime(), getName() + " finished processing a piece"));
	}

private:

	MachineDataLink<Piece>* getOutputLink() {
		return IMachine::getOutputLink<Piece>(outputLinkName);
	}

	MachineDataLink<Piece>* getInputLink() {
		return IMachine::getInputLink<Piece>(inputLinkName);
	}

	bool areLinksConnected() {
		return hasInputLink(inputLinkName)
			&& hasOutputLink(outputLinkName);
	}

	// the piece beeing processed
	Piece* workInProgress;

	static const std::string inputLinkName;
	static const std::string outputLinkName;
};

template <PistonPieceType type>
const std::string PistonPieceMachine<type>::inputLinkName = "PistonPieceMachineInput";

template <PistonPieceType type>
const std::string PistonPieceMachine<type>::outputLinkName = "PistonPieceMachineOutput";