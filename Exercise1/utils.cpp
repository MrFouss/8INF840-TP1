#include <iostream>

#include "utils.h"

Pile<Card>* MakeDeck(int deckSize)
{
	Pile<Card>* deck = new Pile<Card>(deckSize);

	for (int i = 0; i < deckSize; i++) {
		deck->push(*(new Card()));
	}

	return deck;
}

int GetCardNumber() {
	int cn;
	bool flag = false;

	do
	{
		cout << "Entrer le nombre de cartes par joueur [1-" << (DECK_SIZE / 2) << "]\n";
		cin >> cn;
	} while (cn < 1 || cn >(DECK_SIZE / 2));

	return cn;
}

void PrintDeck(Pile<Card>* deck)
{
	Pile<Card> d = *deck;

	if (d.getSize() == 0)
		cout << "This deck is empty\n";
	else
	{
		int count = 1;

		cout << "This deck contains " << d.getSize() << " cards. \n";

		while (!d.isEmpty())
			d.pop().printCard();
	}

	cout << "----------------------------\n";
}

void Distribution(Pile<Card>* deck, Pile<Card>* p1, Pile<Card>* p2, int n)
{
	int i = 0;
	while (i < n)
	{
		p1->push(deck->pop());
		p2->push(deck->pop());
		i++;
	}
}

void WinRound(Pile<Card>* winner, const char* winName, Card c1, Card c2)
{
	cout << winName << " wins\n";
	winner->push(c1);
	winner->push(c2);
}

// players are supposed to have a play deck with the same number of cards
void PlayGame(Pile<Card>* j1_play, Pile<Card>* j1_gain, Pile<Card>* j2_play, Pile<Card>* j2_gain)
{
	while (!j1_play->isEmpty())
	{
		Card c1 = j1_play->pop();
		Card c2 = j2_play->pop();

		cout << c1.getValue() << "/" << c1.getPower() << "/" << c1.getColor()
			<< "\t-VS- "
			<< c2.getValue() << "/" << c2.getPower() << "/" << c2.getColor()
			<< "\t--> ";

		if (c1.getValue() > c2.getValue())
			WinRound(j1_gain, "Player 1", c1, c2);
		else if (c1.getValue() < c2.getValue())
			WinRound(j2_gain, "Player 2", c1, c2);
		else
		{
			if (c1.getPower() > c2.getPower())
				WinRound(j1_gain, "Player 1", c1, c2);
			else if (c1.getPower() < c2.getPower())
				WinRound(j2_gain, "Player 2", c1, c2);
			else
			{
				cout << "Ex-aequo\n";
				j1_gain->push(c1);
				j2_gain->push(c2);
			}
		}
	}
}

void PrintSituation(Pile<Card>* j1_play, Pile<Card>* j1_gain, Pile<Card>* j2_play, Pile<Card>* j2_gain, bool details)
{
	if (!details)
	{
		cout << "Player 1 >> play : " << j1_play->getSize() << " cards -- gain : " << j1_gain->getSize() << " cards\n";
		cout << "Player 2 >> play : " << j2_play->getSize() << " cards -- gain : " << j2_gain->getSize() << " cards\n";
	}
	else
	{
		cout << "----- Player 1 stacks ------\n";

		cout << "PLAY : ";
		PrintDeck(j1_play);
		cout << "GAIN : ";
		PrintDeck(j1_gain);

		cout << "\n----- Player 2 stacks ------\n";
		cout << "PLAY : ";
		PrintDeck(j2_play);
		cout << "GAIN : ";
		PrintDeck(j2_gain);

		cout << "\n";
	}
}

int Score(Pile<Card>* gain)
{
	int score = 0, tmp;
	Card c;

	while (!gain->isEmpty())
	{
		c = gain->pop();
		tmp = c.getValue() * c.getPower();
		if (c.getColor() == 1)
			tmp *= 1.5;
		score += tmp;
	}

	return score;
}