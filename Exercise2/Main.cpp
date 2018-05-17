#include <iostream>
#include "Queue.h"
#include <list>
#include <ctime>
#include "EventManager.h"
#include "PistonPiece.h"
#include "MachineLink.h"
#include "PistonPieceMachine.h"
#include "SortMachine.h"

using namespace std;

int main() {

	srand(time(0));

	// test piston machine

	//PistonPieceMachine<PistonPieceType::AXE> axeMachine("AxeMachine", 2, 0.5, 4);
	//MachineDataLink<PistonAxe> inputLink, outputLink;
	//axeMachine.linkInput(&inputLink);
	//axeMachine.linkOutput(&outputLink);
	//list<PistonAxe> axes;
	//for (int i = 0; i < 10; ++i) {
	//	axes.push_back(PistonAxe());
	//	inputLink.push(&axes.back());
	//}
	//axeMachine.onInputLinkUpdated();
	//EventManager::getInstance().clear();

	// test sort machine

	SortMachine sortMachine("SortMachine", 1, 0, 7);
	MachineDataLink<Machineable> sortInput;
	MachineDataLink<PistonAxe> sortOutputAxe;
	MachineDataLink<PistonJupe> sortOutputJupe;
	MachineDataLink<PistonTete> sortOutputTete;
	sortMachine.linkAxeOutput(sortOutputAxe);
	sortMachine.linkJupeOutput(sortOutputJupe);
	sortMachine.linkTeteOutput(sortOutputTete);
	sortMachine.linkInput(sortInput);
	list<Machineable*> unknownObjects;
	for (int i = 0; i < 100; ++i) {
		switch (rand() % 3) {
		case 0:
			unknownObjects.push_back(new PistonAxe());
			break;
		case 1:
			unknownObjects.push_back(new PistonJupe());
			break;
		case 2:
			unknownObjects.push_back(new PistonTete());
			break;
		}
		sortInput.push(*unknownObjects.back());
	}

	//sortMachine.onInputLinkUpdated();
	//EventManager::getInstance().clear();

	//cout << "axes : " << sortOutputAxe.getSize() << endl;
	//cout << "jupes : " << sortOutputJupe.getSize() << endl;
	//cout << "tete : " << sortOutputTete.getSize() << endl;

	// test linking with a piston piece machine
	PistonPieceMachine<PistonPieceType::TETE> teteMachine("TeteMachine", 2, 0, 0);
	MachineDataLink<PistonTete> pieceMachineOutputTete;
	teteMachine.linkInput(sortOutputTete);
	teteMachine.linkOutput(pieceMachineOutputTete);
	
	teteMachine.onInputLinkUpdated();
	EventManager::getInstance().clear();

	cout << "tete in : " << sortOutputTete.getSize() << endl;
	cout << "tete out : " << pieceMachineOutputTete.getSize() << endl;

	// clean

	for (Machineable* m : unknownObjects) {
		delete m;
	}

	system("pause");
	return 0;
}