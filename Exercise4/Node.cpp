#include "Node.h"


Node::Node(int id, string name, string firstname, int birthyear, EyeColor eyes){
	this->id = id;
	this->name = name;
	this->firstname = firstname;
	this->birthyear = birthyear;
	this->eyes = eyes;
}

Node::~Node(){}
