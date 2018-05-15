#pragma once

#include <string>

using namespace std;

class Dictionnary
{
public:
	Dictionnary() = default;
	Dictionnary(const Dictionnary& dict);
	~Dictionnary();
	const Dictionnary& operator= (const Dictionnary& dict);

	void addWord(const string word);
	void removeWord(const string word);
	
	void displayDictionnary() const;
	bool isContainingWord(const string word) const;

	bool isEmpty() const;
	void erase();

	friend ostream& operator<< (ostream& stream, const Dictionnary& dict);

private:
	class Node
	{
	public:
		char letter;
		bool isEndOfWord;
		Node* nextLetter = 0;
		Node* alternativeLetter = 0;
		
		Node(char letter, bool isEndOfWord) : letter(letter), isEndOfWord(isEndOfWord) {}
		Node(const Node& node) : letter(node.letter), isEndOfWord(node.isEndOfWord) {}

		~Node();
	};

	Node* root = 0;

	Node* copyDictionnary(const Dictionnary& dict);
};

