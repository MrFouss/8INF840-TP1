#include "utils.h"

using namespace std;

int main() {

	Genealogy* family = new Genealogy();
	int choice;

	cout << "------------------------------------------------------------------------------------------------\n"
		<< "Bienvenue dans le gestionnaire d'arbre genealogique !";

	do {
		choice = 0;
		cout << "\n------------------------------------------------------------------------------------------------\n"
		<< "Que voulez-vous faire ?\n"
		<< "\t1 pour charger un arbre depuis un fichier CSV\n"
		<< "\t2 pour afficher l'arbre genealogique\n"
		<< "\t3 pour connaitre la taille de la famille\n"
		<< "\t41 pour connaitre l'ascendance d'une personne (inorder)\n"
		<< "\t42 pour connaitre l'ascendance d'une personne (preorder)\n"
		<< "\t43 pour connaitre l'ascendance d'une personne (postorder)\n"
		<< "\t5 pour ajouter un membre a la famille\n"
		<< "\t6 pour connaitre tous les membres de la famille ayant la couleur d'yeux choisie\n"
		<< "\t7 pour connaitre tous les membres de la famille ayant les memes yeux qu'une personne choisie\n"
		<< "\t8 pour connaitre la moyenne d'age de la famille\n"
		<< "\t9 pour connaitre les descendants d'une personne donnee\n"
		<< "\t0 pour quitter l'application\n"
		<< "------------------------------------------------------------------------------------------------\n\n"
		<< "Votre choix > ";
		cin >> choice;

		string input, name, firstname;
		bool boolChoice, isFather;
		int chosenId, birthyear, eyecolorint, childId;
		vector<Node>* vectorNode;
		vector<Node*> *ancestorsIN, *ancestorsPRE, *ancestorsPOST;
		EyeColor eyeColorChoice;

		switch (choice)
		{
			// Quitter l'application
			case 0: 
				break;

			// Charge un arbre généalogique précédemment enregistré
			case 1 :
				cout << "\nNom du fichier a charger (ex: jon-snow.csv) > ";
				cin >> input;
				family->loadFromCSV(input.c_str());
				cout << "Arbre familial charge.\n";
				break;

			// Afficher l'arbre généalogique actuel
			case 2 :
				cout << "\nAfficher les details des membres ? (1 pour oui, 0 pour non) > ";
				cin >> (bool) boolChoice;
				family->printGenealogy(boolChoice);
				break;

			// Afficher la taille de la famille
			case 3 : 
				cout << "\nLa famille compte " << family->getSize() << " membres\n";
				break;

			// Ascendance (inorder)
			case 41 :
				cout << "Afficher l'ascendance (inorder) de [entrer l'ID de la personne] > ";
				cin >> chosenId;
				ancestorsIN = family->getAncestors(chosenId, INORDER);
				cout << "\nAncetres de " << family->getNode(chosenId)->toString(false) << " (INORDER) :\n";
				printNodeVector(ancestorsIN);
				break;

			// Ascendance (preorder)
			case 42 :
				cout << "Afficher l'ascendance (preorder) de [entrer l'ID de la personne] > ";
				cin >> chosenId;
				ancestorsPRE = family->getAncestors(chosenId, PREORDER);
				cout << "\nAncetres de " << family->getNode(chosenId)->toString(false) << " (PREORDER) :\n";
				printNodeVector(ancestorsPRE);
				break;

			// Ascendance (postorder)
			case 43 :
				cout << "Afficher l'ascendance (postorder) de [entrer l'ID de la personne] > ";
				cin >> chosenId;
				ancestorsPOST = family->getAncestors(chosenId, POSTORDER);
				cout << "\nAncetres de " << family->getNode(chosenId)->toString(false) << " (POSTORDER) :\n";
				printNodeVector(ancestorsPOST);
				break;

			// Ajouter un membre à la famille
			case 5 :
				cout << "Nom  > ";
				cin >> name;
				cout << "Prenom > ";
				cin >> firstname;
				cout << "Annee de naissance > ";
				cin >> (int)birthyear;
				cout << "Couleur des yeux [0=bleu, 1=vert, 2=marron, 3=noir] > ";
				eyeColorChoice = itoEyeColor(getChosenColor());
				cout << "ID du descendant > ";
				cin >> (int)childId;
				cout << "De quel ancetre s'agit-il ? [0 pour la mere, 1 pour le pere] > ";
				cin >> (bool) boolChoice;
				family->addMember(name.c_str(), firstname.c_str(), birthyear, eyeColorChoice, childId, boolChoice);
				cout << "\nNouveau membre " << firstname << " " << name << " ajoute.\n";
				break;

			// Afficher les membres de la famille ayant la couleur d'yeux specifiee
			case 6 :
				eyeColorChoice = itoEyeColor(getChosenColor());
				cout << "\nPersonnes ayant les yeux " << eyeColorToString(eyeColorChoice) << " :\n";
				printNodeVector(family->getGenealogyByEyes(eyeColorChoice));

				break;

			// Afficher les membres de la famille ayant les mêmes yeux qu'une personne choisie
			case 7 :
				cout << "Afficher les membres de la famille ayant les memes yeux que [entrer l'ID de la personne] > ";
				chosenId = getChosenMemberId(family);
				cout << "\nAncetres de " << family->getNode(chosenId)->toString(false) << " ayant les memes yeux :\n";
				printNodeVector(family->getAncestorsByEyes(chosenId));
				break;

			// Afficher la moyenne d'âge de la famille
			case 8 :
				cout << "\nL'age moyen dans la famille est d'environ " << family->meanAge() << " ans.\n";
				break;

			// Afficher les descendants d'une personne donnée
			case 9 :
				cout << "Afficher les descendants de [entrer l'ID de la personne] > ";
				chosenId = getChosenMemberId(family);
				cout << "\nListe des descendants de " << family->getNode(chosenId)->toString(false) << ":\n";
				printNodeVector(family->getDescendants(chosenId));
				break;

			// ERREUR : commande non reconnue
			default :
				cout << "\nCommande incorrecte.\n";

		}

	} while (choice != 0);

	return 0;
}