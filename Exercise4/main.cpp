#include "Genealogy.h"

using namespace std;

void printNodeVector(vector<Node>* n)
{
	for (auto it = n->begin(); it != n->end(); ++it)
		cout << (*it).toString(false) << "\n";
}
void printNodePtrVector(vector<Node*>* n)
{
	for (auto it = n->begin(); it != n->end(); ++it)
		cout << (**it).toString(false) << "\n";
}

int main() {

	Genealogy* family = new Genealogy();

	// Load a family tree
	family->loadFromCSV("jon-snow.csv");
	cout << "Arbre genealogique :";
	family->printGenealogy(true);

	// ----- sujet de TP -----

	// 1. size of the tree
	cout << "\nLa famille compte " << family->getSize() << " membres\n";

	// 2. liste les ancetres d'une personne (IN/PRE/POST orders)
	vector<Node*>* ancestorsIN = family->getAncestors(1, INORDER);
	cout << "\nAncetres de " << family->getNode(1)->toString(false) << " (INORDER) :\n";
	printNodePtrVector(ancestorsIN);

	vector<Node*>* ancestorsPRE = family->getAncestors(1, PREORDER);
	cout << "\nAncetres de " << family->getNode(1)->toString(false) << " (INORDER) :\n";
	printNodePtrVector(ancestorsPRE);

	vector<Node*>* ancestorsPOST = family->getAncestors(1, POSTORDER);
	cout << "\nAncetres de " << family->getNode(1)->toString(false) << " (INORDER) :\n";
	printNodePtrVector(ancestorsPOST);

	// 3. add a member
	family->addMember("Targaryen", "Shaera", 1926, blue, 5, false);
	cout << "\nAjout de Shaera Targaryen\n";
	cout << "\nNouvel arbre genealogique :";
	family->printGenealogy(true);

	// 4. lister les personnes ayant la couleur d'yeux indiquée
	vector<Node>* blue = family->getGenealogyByEyes(EyeColor::blue);
	cout << "\nPersonnes ayant les yeux bleus :\n";
	printNodeVector(blue);

	// 5. liste les ancêtres ayant la même couleur d'yeux que la personne choisie
	vector<Node>* ancestorsBrown = family->getAncestorsByEyes(5);
	cout << "\nAncetres de " << family->getNode(5)->toString(false) << " ayant les memes yeux :\n";
	printNodeVector(ancestorsBrown);

	// 6. moyenne d'âge de la famille
	cout << "\nL'age moyen dans la famille est d'environ " << family->meanAge() << " ans.\n";

	// 7. Lister les descendants d'une personne donnée
	vector<Node*>* n = family->getDescendants(5);
	cout << "\nListe des descendants de " << family->getNode(5)->toString(false);
	printNodePtrVector(n);

	system("pause");
	return 0;
}