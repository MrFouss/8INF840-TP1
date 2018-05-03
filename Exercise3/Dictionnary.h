#pragma once

#include <string>

using namespace std;

class Dictionnary
{
public:
	Dictionnary();
	Dictionnary(const Dictionnary& dict);
	~Dictionnary();
	const Dictionnary& operator= (const Dictionnary& dict);

	void addWord(std::string word);
	void removeWord(std::string word);
	
	void displayDictionnary();
	bool isContainingWord(std::string word);

	bool isEmpty();

	friend std::ostream& operator<< (std::ostream& stream, const Dictionnary& dict);

private:
	class Node
	{
	public:
		char letter;
		bool isEndOfWord;
		Node* nextLetter;
		Node* alternativeLetter;
		
		Node(char letter, bool isEndOfWord) : letter(letter), isEndOfWord(isEndOfWord), nextLetter(0), alternativeLetter(0) {}
	};

	Node* root;
};

