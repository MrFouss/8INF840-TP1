#pragma once

#include "IMachine.h"

#include "Piston.h"
#include "PistonPiece.h"
#include "MachineDataLink.h"

class PistonAssemblyMachine : public IMachine {
public:
	PistonAssemblyMachine(std::string name, float workTime, float breakProbability, float repairTime) :
		IMachine(name, workTime, breakProbability, repairTime),
		teteInProgress(0),
		jupeInProgress(0),
		axeInProgress(0)
	{}
	virtual ~PistonAssemblyMachine();

	void linkJupeInput(MachineDataLink<PistonJupe>* input) { linkInput(jupeInputName, input); }
	void linkAxeInput(MachineDataLink<PistonAxe>* input) { linkInput(axeInputName, input); }
	void linkTeteInput(MachineDataLink<PistonTete>* input) { linkInput(teteInputName, input); }
	void linkOutput(MachineDataLink<Piston>* output) { IMachine::linkOutput(outputName, output); }

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

