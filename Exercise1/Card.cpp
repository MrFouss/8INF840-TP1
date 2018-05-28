#include "Card.h"

Card::Card()
{
	this->value = std::rand() % 100 +1;
	this->power = std::rand() % 4 +1;
	this->color = std::rand() %2;
}

Card::~Card(){}

void Card::printCard()
{
	cout << this->getValue() << "/"
		<< this->getPower() << "/"
		<< this->getColor() << "\n";
}
