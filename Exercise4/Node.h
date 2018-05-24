#pragma once
#include <iostream>
#include "EyeColor.h"

using namespace std;


class Node
{
private:
	int id;
	string name;
	string firstname;
	int birthyear;
	EyeColor eyes;

public:
	// constructor
	Node();
	Node(int id, string name, string firstname, int birthyear, EyeColor eyes);

	// destructor
	~Node();

	// setters & getters
	int getId() { return id; }
	string getName() { return name; }
	string getFirstname() { return firstname; }
	int getBirthyear() { return birthyear; }
	EyeColor getEyeColor() { return eyes; }

	// utils
	string toString(bool details);
};

