#pragma once

#include <string>

using namespace std;

class Dictionary
{
public:
	Dictionary() = default;
	Dictionary(const Dictionary& dict);
	~Dictionary();
	const Dictionary& operator= (const Dictionary& dict);

	void addWord(const string word);
	void removeWord(const string word);
	
	void displayDictionary() const;
	bool isContainingWord(const string word) const;

	bool isEmpty() const;
	void erase();

	friend ostream& operator<< (ostream& stream, const Dictionary& dict);

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

	struct WordIterator
	{
		string word;
		Node* node;

		WordIterator(string word, Node* node) : word(word), node(node) {}

		~WordIterator();
	};

	Node* root = 0;

	Node* copyDictionary(const Dictionary& dict);
};

