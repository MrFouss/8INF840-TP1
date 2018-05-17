#include <iostream>
#include <list>
#include <stack>

#include "Dictionary.h"

Dictionary::Dictionary(const Dictionary& dict)
{
	root = copyDictionary(dict);
}

Dictionary::~Dictionary()
{
	erase();
}

const Dictionary& Dictionary::operator=(const Dictionary& dict)
{
	if (this != &dict)
	{
		erase();
		root = copyDictionary(dict);
	}
	return *this;
}

void Dictionary::addWord(const string word)
{
	if (!isContainingWord(word))
	{
		// TODO add word
	}
}

void Dictionary::removeWord(const string word)
{
	if (isContainingWord(word))
	{
		// TODO remove word
	}
}

void Dictionary::displayDictionary() const
{
	cout << this << endl;
}

bool Dictionary::isContainingWord(const string word) const
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

bool Dictionary::isEmpty() const
{
	return root == 0;
}

void Dictionary::erase()
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

Dictionary::Node* Dictionary::copyDictionary(const Dictionary& dict)
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

ostream& operator<<(ostream& stream, const Dictionary& dict)
{
	stack<Dictionary::WordIterator> stack;
	stack.push(Dictionary::WordIterator("", dict.root));

	while (!stack.empty())
	{
		Dictionary::WordIterator iterator = stack.top();
		stack.pop();

		if (iterator.node->isEndOfWord)
		{
			stream << iterator.word << iterator.node->letter << '\n';
		}

		if (iterator.node->nextLetter != 0)
		{
			string newWord = iterator.word + iterator.node->letter;
			stack.push(Dictionary::WordIterator(newWord, iterator.node->nextLetter));
		}

		if (iterator.node->alternativeLetter != 0)
		{
			string newWord = iterator.word;
			newWord.pop_back();
			newWord += iterator.node->letter;
			stack.push(Dictionary::WordIterator(newWord, iterator.node->alternativeLetter));
		}
	}

	return stream;
}

Dictionary::Node::~Node()
{
	nextLetter = 0;
	alternativeLetter = 0;
}

Dictionary::WordIterator::~WordIterator()
{
	node = 0;
}