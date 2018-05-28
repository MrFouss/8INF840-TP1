#include "utils.h"

using namespace std;

int main() {
	srand(time(NULL));

	// init game
	Pile<Card>* deck = MakeDeck(DECK_SIZE);
	//PrintDeck(deck);

	int nbCardPlayer = GetCardNumber();
	Pile<Card>* j1_play = new Pile<Card>(nbCardPlayer);
	Pile<Card>* j1_gain = new Pile<Card>(DECK_SIZE);

	Pile<Card>* j2_play = new Pile<Card>(nbCardPlayer);
	Pile<Card>* j2_gain = new Pile<Card>(DECK_SIZE);

	// distribution
	Distribution(deck, j1_play, j2_play, nbCardPlayer);

	cout << "\n\n----- Init -----------------\n";
	PrintSituation(j1_play, j1_gain, j2_play, j2_gain, LOG_DETAILS);

	// start game
	cout << "\n\n----- Start Game -----------\n";
	PlayGame(j1_play, j1_gain, j2_play, j2_gain);

	cout << "\n\n----- End ------------------\n";
	PrintSituation(j1_play, j1_gain, j2_play, j2_gain, LOG_DETAILS);

	// score calculation
	cout << "\n\n----- Scores ---------------\n";
	int score1 = Score(j1_gain);
	cout << "Player 1 : " << score1 << " pts\n";

	int score2 = Score(j2_gain);
	cout << "Player 2 : " << score2 << " pts\n";

	if (score1 > score2)
		cout << "\nPlayer 1 wins !\n\n";
	else if (score1 < score2)
		cout << "\nPlayer 2 wins !\n\n";
	else
		cout << "\nEx-aequo !\n\n";

	system("pause");
	return 0;
}