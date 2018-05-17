#pragma once
#include <iostream>
#include <string>

enum EyeColor {	blue, green, brown, black };

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
	Node(int id, string name, string firstname, int birthyear, EyeColor eyes);

	// destructor
	~Node();

	// accessors
	int getId() { return id; }
	string getName() { return name; }
	string getFirstname() { return firstname; }
	int getBirthyear() { return birthyear; }
	EyeColor getEyes() { return eyes; }
};

