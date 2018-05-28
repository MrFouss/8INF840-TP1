# EXERCICE 1 - Bataille de cartes

## Structures utilisées
	Nous créons plusieurs piles de cartes de caractéristiques différentes :
	- deck, la pioche, dont la taille maximale est l'ensemble des cartes (constante DECK_SIZE)
	- playerX_play : la pile de jeu du joueur X dont la taille maximale est DECK_SIZE/2 (puisqu'un joueur aura au maximum la moitié de l'ensemble de la pioche)
	- playerX_gain : la pile de cartes remportées par le joueur X au cours de la partie. Sa taille maximale est DECK_SIZE puisque dans le cas extrême, toutes les cartes sont disribuées et un joueur remporte toutes les manches soit toutes les cartes du paquet

## Initialisation
	Le jeu commence par la génération d'un paquet de cartes aléatoires. On choisit le nombre de cartes à distribuer à chaque joueur (maximum de DECK_SIZE/2 soit une distribution de toutes les cartes de la pioche).
	On initialise les piles de gain à vide (puisque les manches n'ont pas encore commencé) et on distribue les cartes de la pioche aux joueurs en respectant l'alternance (j1 puis j2 puis j1, etc).

## Le jeu
	À chaque manche, les joueurs présentent le carte située au sommet de leur pile de jeu respective et le vainqueur est désigné en fonction des règles stipulées par l'énoncé.

## Fin de jeu
	La partie s'arrête lorsque les joueurs n'ont plus de cartes.
	On dépile ensuite les cartes des piles de gain et l'on calcule le score de chaque joueur.
	Le joueur avec le plus haut score gagne. En cas d'égalité des scores, les deux joueurs remportent la partie à ex-aequo.