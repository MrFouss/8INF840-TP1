#pragma once

#include "IMachine.h"

#include "PistonPiece.h"

template<typename T>
class MachineDataLink;

// a machine that sorts machinable pieces between axis, skirt and head piston pieces
class SortMachine : public IMachine {
public:
	SortMachine(std::string name, float workTime, float breakProbability, float repairTime);
	virtual ~SortMachine();

	void linkSkirtOutput(MachineDataLink<PistonSkirt>* output);
	void linkAxisOutput(MachineDataLink<PistonAxis>* output);
	void linkHeadOutput(MachineDataLink<PistonHead>* output);
	void linkInput(MachineDataLink<Machineable>* input);

protected:

	bool canStartNextJob() override;
	void startNextJob() override;
	void finishCurrentJob() override;

private:

	MachineDataLink<PistonHead>* getHeadOutputLink();
	MachineDataLink<PistonSkirt>* getSkirtOutputLink();
	MachineDataLink<PistonAxis>* getAxisOutputLink();
	MachineDataLink<Machineable>* getInputLink();
	bool areLinksConnected();
	
	// the machineable object beeing sorted
	Machineable* workInProgress;

	static const std::string skirtOutputName;
	static const std::string axisOutputName;
	static const std::string headOutputName;
	static const std::string inputName;
};

