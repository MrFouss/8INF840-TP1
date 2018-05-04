#include <iostream>
#include "Queue.h"

using namespace std;

int main() {

	Queue<int> q;

	for (int i = 0; i < 10; ++i) {
		q.push(i);
		cout << q;
	}
	for (int i = 0; i < 10; ++i) {
		cout << q.pop();
		cout << q;
	}



	system("pause");
	return 0;
}