#include "Genealogy.h"

using namespace std;

int main() {

	Genealogy* family = new Genealogy();
	family->loadFromCSV("jon-snow.csv");

	system("pause");
	return 0;
}