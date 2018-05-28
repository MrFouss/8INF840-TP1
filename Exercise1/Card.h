#pragma once

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

class Card
{
private:
	int value;
	int power;
	bool color; //black = 0, red = 1

public:
	Card();
	~Card();

	// accessors
	int getValue()	{ return this->value; }
	int getPower()  { return this->power; }
	bool getColor() { return this->color; }

	// useful
	void printCard();
};

