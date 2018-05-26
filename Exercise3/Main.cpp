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
		cout << endl;

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
			break;
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

void addWordToDictionary(Dictionary& dict)
{
	string newWord;
	cout << "New word to add: ";
	cin >> newWord;
	if (dict.addWord(newWord))
	{
		cout << "The word \""<< newWord << "\" has been successfully added." << endl << endl;
	}
	else
	{
		cout << "This word is already in the dictionary!" << endl << endl;
	}
}

void removeWordInDictionary(Dictionary& dict)
{
	string word;
	cout << "Word to remove: ";
	cin >> word;
	if (dict.removeWord(word))
	{
		cout << "The word \"" << word << "\" has been successfully removed." << endl << endl;
	}
	else
	{
		cout << "This word could not be removed!" << endl << endl;
	}
}

void checkWordInDictionary(Dictionary& dict)
{
	string word;
	cout << "Word to check: ";
	cin >> word;
	if (dict.isContainingWord(word))
	{
		cout << "The word \"" << word << "\" is in the dictionary." << endl << endl;
	}
	else
	{
		cout << "The word \"" << word << "\" is not in the dictionary." << endl << endl;
	}
}

int main()
{
	Dictionary dict;

	cout << "Welcome to this dictionary manager" << endl << endl;

	loadDictionary(dict);

	int choice;

	do
	{
		cout << endl << "----------------------------------" << endl;
		cout << "Please select what you want to do:" << endl;
		cout << "| [1] Add a word" << endl;
		cout << "| [2] Remove a word" << endl;
		cout << "| [3] Check if a word is in the dictionary" << endl;
		cout << "| [4] Display the dictionary" << endl;
		cout << "| [0] Exit the program" << endl;
		cout << "Choice: ";
		cin >> choice;
		cout << endl;

		switch (choice)
		{
		case 0:
			break;
		case 1:
			addWordToDictionary(dict);
			break;
		case 2:
			removeWordInDictionary(dict);
			break;
		case 3:
			checkWordInDictionary(dict);
			break;
		case 4:
			dict.displayDictionary();
			break;
		default:
			cout << "Wrong input! Try again." << endl << endl;
			break;
		}
	} while (choice != 0);

	return 0;
}