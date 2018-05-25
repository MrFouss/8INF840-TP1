#include <fstream>
#include <iostream>

#include "Dictionary.h"

using namespace std;

void loadDictionary(Dictionary& dict)
{
	int choice;
	string filePath;

	do
	{
		cout << "Please select a dictionary to load:" << endl;
		cout << "| [1] alain.dico" << endl;
		cout << "| [2] g.dico" << endl;
		cout << "| [3] g1.dico" << endl;
		cout << "| [4] guillaume.dico" << endl;
		cout << "| [5] test.dico" << endl;
		cout << "Choice: ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			filePath = "resources/alain.dico";
			cout << "Loading file alain.dico..." << endl << endl;
			break;
		case 2:
			filePath = "resources/g.dico";
			cout << "Loading file g.dico..." << endl << endl;
			break;
		case 3:
			filePath = "resources/g1.dico";
			cout << "Loading file g1.dico..." << endl << endl;
			break;
		case 4:
			filePath = "resources/guillaume.dico";
			cout << "Loading file guillaume.dico..." << endl << endl;
			break;
		case 5:
			filePath = "resources/test.dico";
			cout << "Loading file test.dico..." << endl << endl;
			break;
		default:
			cout << "Wrong input! Try again." << endl << endl;
		}
	} while (choice < 1 || choice > 5);

	fstream inputFile(filePath);
	string line;
	while (getline(inputFile, line))
	{
		dict.addWord(line);
	}
	inputFile.close();
}

int main()
{
	Dictionary dict;

	cout << "Welcome to this dictionary manager" << endl << endl;

	loadDictionary(dict);

	dict.displayDictionary();
	cout << endl;
	dict.removeWord("arbre");
	dict.displayDictionary();
	cout << endl;
	dict.removeWord("le");
	dict.displayDictionary();
	cout << endl;
	dict.removeWord("abasse");
	dict.displayDictionary();
	cout << endl;

	system("pause");
	return 0;
}