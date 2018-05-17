#include <iostream>
#include "Queue.h"
#include <list>
#include <ctime>
#include "EventManager.h"
#include "PistonPiece.h"
#include "MachineLink.h"
#include "MachineDataLink.h"
#include "PistonPieceMachine.h"
#include "PistonAssemblyMachine.h"
#include "SortMachine.h"

using namespace std;

void exec() {

	srand(time(0));

	SortMachine sortMachine("SortMachine", 1, 0, 7);
	MachineDataLink<Machineable> sortInput;
	MachineDataLink<PistonAxe> sortOutputAxe;
	MachineDataLink<PistonJupe> sortOutputJupe;
	MachineDataLink<PistonTete> sortOutputTete;
	sortMachine.linkAxeOutput(&sortOutputAxe);
	sortMachine.linkJupeOutput(&sortOutputJupe);
	sortMachine.linkTeteOutput(&sortOutputTete);
	sortMachine.linkInput(&sortInput);

	for (int i = 0; i < 100; ++i) {
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

	// test linking with a piston piece machine
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

	// piston machine

	PistonAssemblyMachine assemblyMachine("AssemblyMachine", 5, 0, 0);
	MachineDataLink<Piston> pistonOutput;
	assemblyMachine.linkAxeInput(&pieceMachineOutputAxe);
	assemblyMachine.linkJupeInput(&pieceMachineOutputJupe);
	assemblyMachine.linkTeteInput(&pieceMachineOutputTete);
	assemblyMachine.linkOutput(&pistonOutput);


	EventManager::getInstance().clear();
}

int main() {

	exec();
	system("pause");
	return 0;
}