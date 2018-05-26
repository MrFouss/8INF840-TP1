#include "Pile.h"
#include "Card.h"
#include "params.h"

#ifndef UTILS_H
#define UTILS_H

// Build deck containing deckSize random cards
Pile<Card>* MakeDeck(int deckSize);

// get a number of card to be distributed to each player considering some rules
int getCardNumber();

// copy deck and then pop and print every card
void PrintDeck(Pile<Card>* deck);

// pop cards from deck and add them to p1 and p2 stacks
void Distribution(Pile<Card>* deck, Pile<Card>* p1, Pile<Card>* p2, int n);

// add c1 and c2 to the winner stack and print it's name
void WinRound(Pile<Card>* winner, char* winName, Card c1, Card c2);

// as long as the j1 play is not empty, pop j1 and j2 play stacks to confront cards
void PlayGame(Pile<Card>* j1_play, Pile<Card>* j1_gain, Pile<Card>* j2_play, Pile<Card>* j2_gain);

// log the current state of every stack ; if details is true, every card will be printed, if not, only a short view
void PrintSituation(Pile<Card>* j1_play, Pile<Card>* j1_gain, Pile<Card>* j2_play, Pile<Card>* j2_gain, bool details);

// calculation of the score of a gain stack
int Score(Pile<Card>* gain);

#endif // !UTILS_H