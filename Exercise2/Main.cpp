#include <iostream>
#include "Queue.h"
#include <list>
#include "EventManager.h"
#include "Machine.h"
#include "PistonPiece.h"

using namespace std;

int main() {

	std::list<PistonAxe> axes;
	for (int i = 0; i < 5; ++i) {
		axes.push_back(PistonAxe());
	}

	Queue<Machineable*> input;
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

	cout << input << output;

	system("pause");
	return 0;
}