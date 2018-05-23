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
	if (word.size() == 0 || isContainingWord(word))
	{
		return;
	}

	Node* parent = 0;
	Node* previous = 0;
	Node* current = root;

	for (char letter : word)
	{
		while (current != 0 && current->letter < letter)
		{
			previous = current;
			current = current->alternativeLetter;
		}

		// if the node corresponding to the letter doesn't exist
		if (current == 0 || current->letter > letter)
		{
			// Create a new node
			Node* newNode = new Node(letter, false);

			// if current is the new root
			if (parent == 0 && previous == 0)
			{
				root = newNode;
			}
			// if current is the new first element of its alternative letters
			else if (previous == 0)
			{
				parent->nextLetter = newNode;
			}
			else
			{
				previous->alternativeLetter = newNode;
			}

			// Link the new node to its next element
			newNode->alternativeLetter = current;

			parent = newNode;
		}
		else if (current->letter == letter)
		{
			parent = current;
		}

		previous = 0;
		current = parent->nextLetter;
	}

	parent->isEndOfWord = true;
}

void Dictionary::removeWord(const string word)
{
	if (word.size() == 0 || !isContainingWord(word))
	{
		return;
	}

	stack<Node*> parentStack;
	stack<Node*> previousStack;
	stack<Node*> currentStack;

	Node* parent = 0;
	Node* previous = 0;
	Node* current = root;

	for (char letter : word)
	{
		while (current != 0 && current->letter < letter)
		{
			previous = current;
			current = current->alternativeLetter;
		}

		parentStack.push(parent);
		previousStack.push(previous);
		currentStack.push(current);

		parent = current;
		previous = 0;
		current = parent->nextLetter;
	}


	currentStack.top()->isEndOfWord = false;
	if (currentStack.top()->nextLetter != 0)
	{
		return;
	}

	while (!currentStack.empty())
	{
		parent = parentStack.top();
		parentStack.pop();

		previous = previousStack.top();
		previousStack.pop();

		current = currentStack.top();
		currentStack.pop();

		if (current->isEndOfWord || current->nextLetter != 0)
		{
			return;
		}

		if (previous != 0)
		{
			previous->alternativeLetter = current->alternativeLetter;
		}
		else
		{
			if (parent == 0)
			{
				root = current->alternativeLetter;
			}
			else
			{
				parent->nextLetter = current->alternativeLetter;
			}
		}

		delete current;
	}
}

void Dictionary::displayDictionary() const
{
	cout << (*this) << endl;
}

bool Dictionary::isContainingWord(const string word) const
{
	if (isEmpty() || word.size() == 0)
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

		if (iterator.node->alternativeLetter != 0)
		{
			string newWord(iterator.word);

			stack.push(Dictionary::WordIterator(newWord, iterator.node->alternativeLetter));
		}

		if (iterator.node->nextLetter != 0)
		{
			string newWord(iterator.word + iterator.node->letter);
			stack.push(Dictionary::WordIterator(newWord, iterator.node->nextLetter));
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