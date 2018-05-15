#pragma once
#include "IMachine.h"
#include "MachineDataLink.h"
#include "PistonPiece.h"
#include "EventManager.h"
#include "LogEvent.h"
#include <iostream>

class SortMachine : public IMachine {
public:
	SortMachine(std::string name, float workTime, float breakProbability, float repairTime) :
		IMachine(name, workTime, breakProbability, repairTime),
		workInProgress(0)
	{}
	virtual ~SortMachine() = default;

	void linkJupeOutput(MachineDataLink<PistonJupe>& output) { linkOutput(jupeOutputName, output); }
	void linkAxeOutput(MachineDataLink<PistonAxe>& output) { linkOutput(axeOutputName, output);	}
	void linkTeteOutput(MachineDataLink<PistonTete>& output) { linkOutput(teteOutputName, output); }
	void linkInput(MachineDataLink<Machineable>& input) { IMachine::linkInput(inputName, input); }

protected:

	virtual bool canStartNextWork();
	virtual void startNextWork();
	virtual void finishCurrentWork();

private:

	MachineDataLink<PistonTete>& getTeteOutputLink();
	MachineDataLink<PistonJupe>& getJupeOutputLink();
	MachineDataLink<PistonAxe>& getAxeOutputLink();
	MachineDataLink<Machineable>& getInputLink();
	bool areLinksConnected();
	
	Machineable* workInProgress;

	static const std::string jupeOutputName;
	static const std::string axeOutputName;
	static const std::string teteOutputName;
	static const std::string inputName;

};

