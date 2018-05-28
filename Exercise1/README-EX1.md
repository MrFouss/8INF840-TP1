# EXERCICE 1 - Bataille de cartes

## Structures utilis�es
	Nous cr�ons plusieurs piles de cartes de caract�ristiques diff�rentes :
	- deck, la pioche, dont la taille maximale est l'ensemble des cartes (constante DECK_SIZE)
	- playerX_play : la pile de jeu du joueur X dont la taille maximale est DECK_SIZE/2 (puisqu'un joueur aura au maximum la moiti� de l'ensemble de la pioche)
	- playerX_gain : la pile de cartes remport�es par le joueur X au cours de la partie. Sa taille maximale est DECK_SIZE puisque dans le cas extr�me, toutes les cartes sont disribu�es et un joueur remporte toutes les manches soit toutes les cartes du paquet

## Initialisation
	Le jeu commence par la g�n�ration d'un paquet de cartes al�atoires. On choisit le nombre de cartes � distribuer � chaque joueur (maximum de DECK_SIZE/2 soit une distribution de toutes les cartes de la pioche).
	On initialise les piles de gain � vide (puisque les manches n'ont pas encore commenc�) et on distribue les cartes de la pioche aux joueurs en respectant l'alternance (j1 puis j2 puis j1, etc).

## Le jeu
	� chaque manche, les joueurs pr�sentent le carte situ�e au sommet de leur pile de jeu respective et le vainqueur est d�sign� en fonction des r�gles stipul�es par l'�nonc�.

## Fin de jeu
	La partie s'arr�te lorsque les joueurs n'ont plus de cartes.
	On d�pile ensuite les cartes des piles de gain et l'on calcule le score de chaque joueur.
	Le joueur avec le plus haut score gagne. En cas d'�galit� des scores, les deux joueurs remportent la partie � ex-aequo.