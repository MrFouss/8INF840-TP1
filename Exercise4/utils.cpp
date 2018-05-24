#include "utils.h"


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

int getChosenColor()
{
	int cn;
	bool flag = false;

	do
	{
		cout << "Entrer la couleur d'yeux recherchee :\n"
			<< "0 pour bleus\n"
			<< "1 pour verts\n"
			<< "2 pour marrons\n"
			<< "3 pour noirs\n"
			<< "Couleur choisie > ";
		cin >> (int)cn;
	} while (cn < 0 || cn > 3);

	return cn;
}

int getChosenMemberId(Genealogy* family)
{
	int cn;
	bool flag = false;

	do
	{
		cin >> (int)cn;
	} while (!family->exists(cn));

	return cn;
}
