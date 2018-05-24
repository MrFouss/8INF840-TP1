#pragma once

#include "IMachine.h"

#include "Piston.h"
#include "PistonPiece.h"
#include "MachineDataLink.h"

class PistonAssemblyMachine : public IMachine {
public:
	PistonAssemblyMachine(std::string name, float workTime, float breakProbability, float repairTime);
	virtual ~PistonAssemblyMachine();

	void linkJupeInput(MachineDataLink<PistonJupe>* input);
	void linkAxeInput(MachineDataLink<PistonAxe>* input);
	void linkTeteInput(MachineDataLink<PistonTete>* input);
	void linkOutput(MachineDataLink<Piston>* output);

protected:

	bool canStartNextJob() override;
	void startNextJob() override;
	void finishCurrentJob() override;

private:

	MachineDataLink<PistonTete>* getTeteInputLink();
	MachineDataLink<PistonJupe>* getJupeInputLink();
	MachineDataLink<PistonAxe>* getAxeInputLink();
	MachineDataLink<Piston>* getOutputLink();
	bool areLinksConnected();

	// pieces beeing assembled
	PistonTete* teteInProgress;
	PistonJupe* jupeInProgress;
	PistonAxe* axeInProgress;

	static const std::string jupeInputName;
	static const std::string axeInputName;
	static const std::string teteInputName;
	static const std::string outputName;
};

