#pragma once

#include "IMachine.h"

#include "Piston.h"
#include "PistonPiece.h"
#include "MachineDataLink.h"

class PistonAssemblyMachine : public IMachine {
public:
	PistonAssemblyMachine(std::string name, float workTime, float breakProbability, float repairTime);
	virtual ~PistonAssemblyMachine();

	void linkSkirtInput(MachineDataLink<PistonSkirt>* input);
	void linkAxisInput(MachineDataLink<PistonAxis>* input);
	void linkHeadInput(MachineDataLink<PistonHead>* input);
	void linkOutput(MachineDataLink<Piston>* output);

protected:

	bool canStartNextJob() override;
	void startNextJob() override;
	void finishCurrentJob() override;

private:

	MachineDataLink<PistonHead>* getHeadInputLink();
	MachineDataLink<PistonSkirt>* getSkirtInputLink();
	MachineDataLink<PistonAxis>* getAxisInputLink();
	MachineDataLink<Piston>* getOutputLink();
	bool areLinksConnected();

	// pieces beeing assembled
	PistonHead* headInProgress;
	PistonSkirt* skirtInProgress;
	PistonAxis* axisInProgress;

	static const std::string skirtInputName;
	static const std::string axisInputName;
	static const std::string headInputName;
	static const std::string outputName;
};

