#include <iostream>
#include "Queue.h"
#include <list>
#include "EventManager.h"
#include "PistonPiece.h"
#include "SimpleMachine.h"
#include "MachineLink.h"

using namespace std;

int main() {

	std::list<PistonAxe> axes;
	for (int i = 0; i < 5; ++i) {
		axes.push_back(PistonAxe());
	}

	MachineLink inLink, outlink;
	SimpleMachine m("m1", 2, 3, 0.5);
	m.setInputLink(&inLink);
	m.setOutputLink(&outlink);

	for (PistonAxe& axe : axes) {
		inLink.push(&axe);
	}

	EventManager::getInstance().clear(true);

	/*Queue<Machineable*> input;
	Queue<Machineable*> output;
	Machine m(2, 3, 0);

	for (PistonAxe& axe : axes) {
		input.push(&axe);
	}

	m.setInputQueue(&input);
	m.setOutputQueue(&output);

	cout << "in " << input << "out" << output;

	EventManager& em = EventManager::getInstance();
	m.processNext();
	while (!input.isEmpty()) {
		if (m.canProcessNext()) {
			m.processNext();
		}
		em.triggerNextEvent(true);
	}

	cout << input << output;*/

	system("pause");
	return 0;
}