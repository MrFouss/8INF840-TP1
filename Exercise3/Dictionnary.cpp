#include <iostream>
#include <stack>

#include "Dictionnary.h"

Dictionnary::Dictionnary(const Dictionnary& dict)
{
	root = copyDictionnary(dict);
}

Dictionnary::~Dictionnary()
{
	erase();
}

const Dictionnary& Dictionnary::operator=(const Dictionnary& dict)
{
	if (this != &dict)
	{
		erase();
		root = copyDictionnary(dict);
	}
	return *this;
}

void Dictionnary::addWord(const string word)
{

}

void Dictionnary::removeWord(const string word)
{

}

void Dictionnary::displayDictionnary() const
{
	cout << this << endl;
}

bool Dictionnary::isContainingWord(const string word) const
{
	if (isEmpty())
	{
		return false;
	}

	Node* iterator = root;
	Node* lastIterator = iterator;

	for (char letter : word)
	{
		while (iterator != 0 && iterator->letter < letter)
		{
			iterator = iterator->alternativeLetter;
		}

		if (iterator != 0 && iterator->letter == letter)
		{
			lastIterator = iterator;
			iterator = iterator->nextLetter;
		}
		else
		{
			return false;
		}
	}

	return lastIterator->isEndOfWord;
}

bool Dictionnary::isEmpty() const
{
	return root == 0;
}

void Dictionnary::erase()
{
	stack<Node*> nodeStack;

	if (!isEmpty())
	{
		nodeStack.push(root);
		root = 0;
	}

	while (!nodeStack.empty())
	{
		Node* node = nodeStack.top();
		nodeStack.pop();

		if (node->nextLetter != 0)
		{
			nodeStack.push(node->nextLetter);
		}

		if (node->alternativeLetter != 0)
		{
			nodeStack.push(node->alternativeLetter);
		}

		delete node;
	}
}

Dictionnary::Node* Dictionnary::copyDictionnary(const Dictionnary& dict)
{
	if (dict.isEmpty())
	{
		return 0;
	}

	stack<Node*> oldNodeStack;
	oldNodeStack.push(dict.root);

	stack<Node*> newNodeStack;
	Node* newRoot = new Node(*dict.root);
	newNodeStack.push(newRoot);

	while (!oldNodeStack.empty())
	{
		Node* oldNode = oldNodeStack.top();
		oldNodeStack.pop();

		Node* newNode = newNodeStack.top();
		newNodeStack.pop();

		if (oldNode->nextLetter != 0)
		{
			oldNodeStack.push(oldNode->nextLetter);
			newNode->nextLetter = new Node(*oldNode->nextLetter);
			newNodeStack.push(newNode->nextLetter);
		}

		if (oldNode->alternativeLetter != 0)
		{
			oldNodeStack.push(oldNode->alternativeLetter);
			newNode->alternativeLetter = new Node(*oldNode->alternativeLetter);
			newNodeStack.push(newNode->alternativeLetter);
		}
	}

	return newRoot;
}

ostream& operator<<(ostream& stream, const Dictionnary& dict)
{
	return stream;
}

Dictionnary::Node::~Node()
{
	nextLetter = 0;
	alternativeLetter = 0;
}
