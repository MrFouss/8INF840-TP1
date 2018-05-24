#include <iostream>
#include <ctime>

#include "EventManager.h"
#include "PistonPiece.h"
#include "MachineDataLink.h"
#include "PistonPieceMachine.h"
#include "PistonAssemblyMachine.h"
#include "SortMachine.h"

using namespace std;

int main() { 

	// the number of raw piston pieces initially as input
	int inputSize = 100;

	// init RNG
	srand(time(0));

	// setup sort machine

	SortMachine sortMachine("SortMachine", 1, 0, 7);
	MachineDataLink<Machineable> sortInput;
	MachineDataLink<PistonAxe> sortOutputAxe;
	MachineDataLink<PistonJupe> sortOutputJupe;
	MachineDataLink<PistonTete> sortOutputTete;
	sortMachine.linkAxeOutput(&sortOutputAxe);
	sortMachine.linkJupeOutput(&sortOutputJupe);
	sortMachine.linkTeteOutput(&sortOutputTete);
	sortMachine.linkInput(&sortInput);

	// setup individual piston piece machines

	PistonPieceMachine<PistonPieceType::TETE> teteMachine("TeteMachine", 2, 0, 0);
	MachineDataLink<PistonTete> pieceMachineOutputTete;
	teteMachine.linkInput(&sortOutputTete);
	teteMachine.linkOutput(&pieceMachineOutputTete);

	PistonPieceMachine<PistonPieceType::AXE> axeMachine("AxeMachine", 2, 0, 0);
	MachineDataLink<PistonAxe> pieceMachineOutputAxe;
	axeMachine.linkInput(&sortOutputAxe);
	axeMachine.linkOutput(&pieceMachineOutputAxe);

	PistonPieceMachine<PistonPieceType::JUPE> jupeMachine("JupeMachine", 2, 0, 0);
	MachineDataLink<PistonJupe> pieceMachineOutputJupe;
	jupeMachine.linkInput(&sortOutputJupe);
	jupeMachine.linkOutput(&pieceMachineOutputJupe);

	// setup piston assembly machine

	PistonAssemblyMachine assemblyMachine("AssemblyMachine", 5, 0, 0);
	MachineDataLink<Piston> pistonOutput;
	assemblyMachine.linkAxeInput(&pieceMachineOutputAxe);
	assemblyMachine.linkJupeInput(&pieceMachineOutputJupe);
	assemblyMachine.linkTeteInput(&pieceMachineOutputTete);
	assemblyMachine.linkOutput(&pistonOutput);

	// fill input link

	for (int i = 0; i < inputSize; ++i) {
		switch (rand() % 3) {
		case 0:
			sortInput.push(new PistonAxe());
			break;
		case 1:
			sortInput.push(new PistonJupe());
			break;
		case 2:
			sortInput.push(new PistonTete());
			break;
		}
	}

	// execute the simulation

	EventManager::getInstance().setPrintLog(true);
	EventManager::getInstance().triggerAllEvents();

	// print stats

	cout << pistonOutput.getSize() << " pistons produced out of " << inputSize << " random pieces" << endl;

	system("pause");
	return 0;
}