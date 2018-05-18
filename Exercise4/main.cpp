#include "Genealogy.h"

using namespace std;

int main() {

	Genealogy* family = new Genealogy();

	// TESTS
	family->loadFromCSV("jon-snow.csv");
	//family->addMember("Targaryen", "Jachaerys II", 1922, blue);
	family->printGenealogy(true);
	//cout << "\n" << family->exists(5) << "\n";
	//cout << family->getIndex(5);
	//family->addMember("Targaryen", "Shaera", 1926, blue, 5, false);
	//cout << family->getSize()

	system("pause");
	return 0;
}