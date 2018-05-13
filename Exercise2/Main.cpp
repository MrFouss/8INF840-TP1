#include <iostream>
#include "Queue.h"
#include <list>
#include <ctime>
#include "EventManager.h"
#include "PistonPiece.h"
#include "MachineLink.h"
#include "PistonPieceMachine.h"

using namespace std;

int main() {
	srand(time(NULL));

	PistonPieceMachine<PistonPieceType::AXE> axeMachine("AxeMachine", 2, 1, 4);
	MachineLink<PistonAxe> inputLink, outputLink;
	axeMachine.linkInput(&inputLink);
	axeMachine.linkOutput(&outputLink);
	list<PistonAxe> axes;
	for (int i = 0; i < 10; ++i) {
		axes.push_back(PistonAxe());
		inputLink.push(&axes.back());
	}

	axeMachine.onLinkUpdated();
	EventManager::getInstance().clear(true);

	system("pause");
	return 0;
}