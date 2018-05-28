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
	int outputPistonNumber;

	cout << "How many output pistons ? ";

	cin >> outputPistonNumber;

	// keep track of the input repartition
	int skirtNbr = 0;
	int axisNbr = 0;
	int headNbr = 0;

	// init RNG
	srand(time(0));

	// setup sort machine

	SortMachine sortMachine("SortMachine", 0, 0, 0, 0);
	MachineDataLink<Machineable> sortInput;
	MachineDataLink<PistonAxis> sortOutputAxis;
	MachineDataLink<PistonSkirt> sortOutputskirt;
	MachineDataLink<PistonHead> sortOutputHead;
	sortMachine.linkAxisOutput(&sortOutputAxis);
	sortMachine.linkSkirtOutput(&sortOutputskirt);
	sortMachine.linkHeadOutput(&sortOutputHead);
	sortMachine.linkInput(&sortInput);

	// setup individual piston piece machines

	PistonPieceMachine<PistonPieceType::HEAD> headMachine("HeadMachine", 2, 0.25, 5, 10);
	MachineDataLink<PistonHead> pieceMachineOutputHead;
	headMachine.linkInput(&sortOutputHead);
	headMachine.linkOutput(&pieceMachineOutputHead);

	PistonPieceMachine<PistonPieceType::AXIS> axisMachine("AxisMachine", 2.5, 0.25, 5, 10);
	MachineDataLink<PistonAxis> pieceMachineOutputAxis;
	axisMachine.linkInput(&sortOutputAxis);
	axisMachine.linkOutput(&pieceMachineOutputAxis);

	PistonPieceMachine<PistonPieceType::SKIRT> skirtMachine("SkirtMachine", 3, 0.25, 5, 10);
	MachineDataLink<PistonSkirt> pieceMachineOutputskirt;
	skirtMachine.linkInput(&sortOutputskirt);
	skirtMachine.linkOutput(&pieceMachineOutputskirt);

	// setup piston assembly machine

	PistonAssemblyMachine assemblyMachine("AssemblyMachine", 10, 0.25, 5, 10);
	MachineDataLink<Piston> pistonOutput;
	assemblyMachine.linkAxisInput(&pieceMachineOutputAxis);
	assemblyMachine.linkSkirtInput(&pieceMachineOutputskirt);
	assemblyMachine.linkHeadInput(&pieceMachineOutputHead);
	assemblyMachine.linkOutput(&pistonOutput);

	// execute the simulation

	EventManager* em = EventManager::getInstance();
	em->setPrintLog(true);

	do {

		// make sur to add inputs if there is no piece of a certain type in the system
		if (sortInput.isEmpty() && !sortMachine.isMachineWorking() 
				&& (
					(sortOutputAxis.isEmpty() && pieceMachineOutputAxis.isEmpty() && !axisMachine.isMachineWorking()) 
					|| (sortOutputHead.isEmpty() && pieceMachineOutputHead.isEmpty() && !headMachine.isMachineWorking())
					|| (sortOutputskirt.isEmpty() && pieceMachineOutputskirt.isEmpty() && !skirtMachine.isMachineWorking())
				)) {

			// equiprobability to push any type of piece in the system
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
		
		em->triggerNextEvent();
	} while (!em->isEmpty() && (dynamic_cast<LogEvent*>(em->nextEvent()) != 0 || pistonOutput.getSize() < outputPistonNumber));

	// print stats

	cout << pistonOutput.getSize() << " piston(s) produced in " 
		<< em->getTime() << " min, out of "
		<< skirtNbr << " skirt(s), "
		<< axisNbr << " axis, " 
		<< headNbr << " head(s)" << endl;

	system("pause");
	return 0;
}