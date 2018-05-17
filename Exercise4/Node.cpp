#include "Node.h"


Node::Node(int id, string name, string firstname, int birthyear, EyeColor eyes){
	this->id = id;
	this->name = name;
	this->firstname = firstname;
	this->birthyear = birthyear;
	this->eyes = eyes;

	this->left = NULL;
	this->right = NULL;
}

Node::~Node(){}

string Node::toString()
{
	string result = this->getFirstname() + " " + this->getName() + " " + to_string(getBirthyear()) + " " + eyeColorToString(getEyes());
	return result;
}

int Node::addChild(Node* child)
{
	if (!left) {
		left = child;
		return 0;
	}

	if (!right) {
		right = child;
		return 0;
	}

	return -1;
}
