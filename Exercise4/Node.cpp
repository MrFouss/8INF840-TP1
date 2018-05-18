#include "Node.h"


Node::Node()
{
	this->id = -1;
	this->name = "UNKNOWN";
	this->firstname = "Unknown";
	this->birthyear = 0;
	this->eyes = itoEyeColor(0);
}

Node::Node(int id, string name, string firstname, int birthyear, EyeColor eyes){
	this->id = id;
	this->name = name;
	this->firstname = firstname;
	this->birthyear = birthyear;
	this->eyes = eyes;
}

Node::~Node(){}

string Node::toString(bool details)
{
	string result;
	if (details)
		result = to_string(this->id) + " " + this->firstname + " " + this->name + " " + to_string(this->birthyear) + " " + eyeColorToString(this->eyes);
	else
		result = to_string(this->id) + " " + this->firstname + " " + this->name;

	return result;
}
