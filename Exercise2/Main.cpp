#include <iostream>
#include "Queue.h"
#include <list>

using namespace std;

int main() {

	Queue<int> q;

	for (int i = 0; i < 10; ++i) {
		q.push(i);
		cout << q << q.getSize() << endl;
		cout << q.getHead() << " " << q.getTail() << endl;
	}

	Queue<int> qCopy(q);

	cout << qCopy;

	for (int i = 0; i < 9; ++i) {
		cout << q.pop();
		cout << q << q.getSize() << endl;
		cout << q.getHead() << " " << q.getTail() << endl;
	}

	qCopy = q;

	cout << qCopy << q;

	q.pop();

	qCopy = q;

	cout << qCopy << q;


	system("pause");
	return 0;
}