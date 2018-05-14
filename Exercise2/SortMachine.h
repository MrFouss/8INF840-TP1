#pragma once
#include "IMachine.h"
#include "MachineDataLink.h"
#include "PistonPiece.h"

#include <iostream>

class SortMachine : public IMachine {
public:
	SortMachine(std::string name, float workTime, float breakProbability, float repairTime) :
		IMachine(name, workTime, breakProbability, repairTime),
		workInProgress(NULL)
	{}

	virtual ~SortMachine() = default;

	void linkJupeOutput(MachineDataLink<PistonJupe>* output) {
		linkOutput(jupeOutputName, output);
	}

	void linkAxeOutput(MachineDataLink<PistonAxe>* output) {
		linkOutput(axeOutputName, output);
	}

	void linkTeteOutput(MachineDataLink<PistonTete>* output) {
		linkOutput(teteOutputName, output);
	}
	
	void linkInput(MachineDataLink<Machineable>* input) {
		IMachine::linkInput(inputName, input);
	}

protected:
	virtual bool canStartNextWork() {
		return areLinksConnected() && !getInputLink()->isEmpty() && workInProgress == NULL;
	}

	virtual void startNextWork() {
		assert(canStartNextWork());
		workInProgress = getInputLink()->pop();
	}

	virtual void finishCurrentWork() {
		assert(areLinksConnected() && workInProgress != NULL);
		if ((PistonAxe*)workInProgress != NULL) {
			getAxeOutputLink()->push((PistonAxe*)workInProgress);
		} else if ((PistonJupe*)workInProgress != NULL) {
			getJupeOutputLink()->push((PistonJupe*)workInProgress);
		} else if ((PistonTete*)workInProgress != NULL) {
			getTeteOutputLink()->push((PistonTete*)workInProgress);
		} else {
			std::cerr << getName() << " : Unrecognized type" << std::endl;
			std::exit(1);
		}
		workInProgress = NULL;
	}

private:

	MachineDataLink<PistonTete>* getTeteOutputLink() {
		return (MachineDataLink<PistonTete>*)getOutputLink(teteOutputName);
	}
	
	MachineDataLink<PistonJupe>* getJupeOutputLink() {
		return (MachineDataLink<PistonJupe>*)getOutputLink(jupeOutputName);
	}
	
	MachineDataLink<PistonAxe>* getAxeOutputLink() {
		return (MachineDataLink<PistonAxe>*)getOutputLink(axeOutputName);
	}

	MachineDataLink<Machineable>* getInputLink() {
		return (MachineDataLink<Machineable>*)IMachine::getInputLink(inputName);
	}

	bool areLinksConnected() {
		return hasInputLink(inputName) 
			&& hasOutputLink(jupeOutputName) 
			&& hasOutputLink(teteOutputName) 
			&& hasOutputLink(axeOutputName);
	}
	
	Machineable* workInProgress;

	static const std::string jupeOutputName;
	static const std::string axeOutputName;
	static const std::string teteOutputName;

	static const std::string inputName;

};

