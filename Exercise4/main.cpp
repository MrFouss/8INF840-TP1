#include "Genealogy.h"

using namespace std;

void printNodeVector(vector<Node>* n)
{
	for (auto it = n->begin(); it != n->end(); ++it)
		cout << (*it).toString(false) << "\n";
}

int main() {

	Genealogy* family = new Genealogy();

	// Load a family tree
	family->loadFromCSV("jon-snow.csv");
	family->printGenealogy(true);

	// ----- sujet de TP -----

	// 1. size of the tree
	//cout << "La famille compte " << family->getSize() << " membres\n";

	// 2. liste des ascendants d'une personne ayant la m�me couleur d'yeux
	//vector<Node>* ancestorsSameEyes = family->getAncestorsByEyes(1);
	//printNodeVector(ancestorsSameEyes);

	// 3. add a member
	//family->addMember("Targaryen", "Jachaerys II", 1922, blue);
	//family->addMember("Targaryen", "Shaera", 1926, blue, 5, false);
	//family->printGenealogy(false);

	// 4. lister les personnes ayant la couleur d'yeux indiqu�e
	//vector<Node>* blue = family->getGenealogyByEyes(EyeColor::blue);
	//cout << "Have blue eyes :\n";
	//for (auto it = blue->begin(); it != blue->end(); ++it)
	//	cout << (*it).toString(false) << "\n";

	// 5. liste les anc�tres ayant la m�me couleur d'yeux que la personne choisie
	//vector<Node>* ancestorsBrown = family->getAncestorsByEyes(5);
	//cout << "Ancestors of " << family->getNode(5)->toString(false) << " that have brown eyes :\n";
	//for (auto it = ancestorsBrown->begin(); it != ancestorsBrown->end(); ++it)
	//	cout << (*it).toString(false) << "\n";

	// 6. moyenne d'�ge de la famille
	cout << "L'age moyen dans la famille est d'environ " << family->meanAge() << " ans.\n";

	// ----- utils -----

	// check if a given node exists
	//cout << "\n" << family->exists(5) << "\n";

	

	system("pause");
	return 0;
}