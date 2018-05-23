#include <fstream>
#include <iostream>

#include "Dictionary.h"

using namespace std;

int main()
{
	Dictionary dict;

	fstream inputFile("resources/test.dico");
	string line;
	while (getline(inputFile, line))
	{
		dict.addWord(line);
	}
	inputFile.close();

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