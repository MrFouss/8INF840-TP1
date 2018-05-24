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
	int inputSize = 9;

	// keep track of the input repartition
	int skirtNbr = 0;
	int axisNbr = 0;
	int headNbr = 0;

	// init RNG
	srand(time(0));

	// setup sort machine

	SortMachine sortMachine("SortMachine", 1, 0, 7);
	MachineDataLink<Machineable> sortInput;
	MachineDataLink<PistonAxis> sortOutputAxis;
	MachineDataLink<PistonSkirt> sortOutputskirt;
	MachineDataLink<PistonHead> sortOutputHead;
	sortMachine.linkAxisOutput(&sortOutputAxis);
	sortMachine.linkSkirtOutput(&sortOutputskirt);
	sortMachine.linkHeadOutput(&sortOutputHead);
	sortMachine.linkInput(&sortInput);

	// setup individual piston piece machines

	PistonPieceMachine<PistonPieceType::HEAD> headMachine("HeadMachine", 2, 0, 0);
	MachineDataLink<PistonHead> pieceMachineOutputHead;
	headMachine.linkInput(&sortOutputHead);
	headMachine.linkOutput(&pieceMachineOutputHead);

	PistonPieceMachine<PistonPieceType::AXIS> axisMachine("AxisMachine", 2, 0, 0);
	MachineDataLink<PistonAxis> pieceMachineOutputAxis;
	axisMachine.linkInput(&sortOutputAxis);
	axisMachine.linkOutput(&pieceMachineOutputAxis);

	PistonPieceMachine<PistonPieceType::SKIRT> skirtMachine("SkirtMachine", 2, 0, 0);
	MachineDataLink<PistonSkirt> pieceMachineOutputskirt;
	skirtMachine.linkInput(&sortOutputskirt);
	skirtMachine.linkOutput(&pieceMachineOutputskirt);

	// setup piston assembly machine

	PistonAssemblyMachine assemblyMachine("AssemblyMachine", 5, 0, 0);
	MachineDataLink<Piston> pistonOutput;
	assemblyMachine.linkAxisInput(&pieceMachineOutputAxis);
	assemblyMachine.linkSkirtInput(&pieceMachineOutputskirt);
	assemblyMachine.linkHeadInput(&pieceMachineOutputHead);
	assemblyMachine.linkOutput(&pistonOutput);

	// fill input link

	for (int i = 0; i < inputSize; ++i) {
		switch (rand() % 3) {
		case 0:
			sortInput.push(new PistonAxis());
			axisNbr++;
			break;
		case 1:
			sortInput.push(new PistonSkirt());
			skirtNbr++;
			break;
		case 2:
			sortInput.push(new PistonHead());
			headNbr++;
			break;
		}
	}

	// execute the simulation

	EventManager::getInstance().setPrintLog(true);
	EventManager::getInstance().triggerAllEvents();

	// print stats

	cout << pistonOutput.getSize() << " piston(s) produced out of " 
		<< skirtNbr << " skirt(s), "
		<< axisNbr << " axis, " 
		<< headNbr << " head(s)" << endl;

	system("pause");
	return 0;
}