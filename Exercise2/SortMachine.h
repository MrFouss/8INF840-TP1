#pragma once

#include "IMachine.h"

#include "PistonPiece.h"

template<typename T>
class MachineDataLink;

// a machine that sorts machinable pieces between axe, jupe and tete piston pieces
class SortMachine : public IMachine {
public:
	SortMachine(std::string name, float workTime, float breakProbability, float repairTime) :
		IMachine(name, workTime, breakProbability, repairTime),
		workInProgress(0)
	{}
	virtual ~SortMachine() = default;

	void linkJupeOutput(MachineDataLink<PistonJupe>& output);
	void linkAxeOutput(MachineDataLink<PistonAxe>& output);
	void linkTeteOutput(MachineDataLink<PistonTete>& output);
	void linkInput(MachineDataLink<Machineable>& input);

protected:

	bool canStartNextJob() override;
	void startNextJob() override;
	void finishCurrentJob() override;

private:

	MachineDataLink<PistonTete>& getTeteOutputLink();
	MachineDataLink<PistonJupe>& getJupeOutputLink();
	MachineDataLink<PistonAxe>& getAxeOutputLink();
	MachineDataLink<Machineable>& getInputLink();
	bool areLinksConnected();
	
	// the machineable object beeing sorted
	Machineable* workInProgress;

	static const std::string jupeOutputName;
	static const std::string axeOutputName;
	static const std::string teteOutputName;
	static const std::string inputName;
};

