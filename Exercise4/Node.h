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

	Node* left;
	Node* right;

public:
	// constructor
	Node(int id, string name, string firstname, int birthyear, EyeColor eyes);

	// destructor
	~Node();

	// setters & getters
	int getId() { return id; }
	string getName() { return name; }
	string getFirstname() { return firstname; }
	int getBirthyear() { return birthyear; }
	EyeColor getEyes() { return eyes; }

	Node* getLeft() { return left; }
	Node* getRight() { return right; }
	void setLeft(Node* _left) { this->left = _left; }
	void setRight(Node* _right) { this->right = _right; }

	// utils
	string toString();
	int addChild(Node* child);
};

