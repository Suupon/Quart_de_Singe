#include <iostream>
#include <assert.h>
#include <fstream> // pour ifstream
#include <iomanip> // pour setw
#include <ctime>
#include <cstdlib>
#pragma warning (disable:4996)
#include "humain.h"
#include "robot.h"
#include "jeu.h"

using namespace std;

void testDevinerHumain() {
	
	Jeu game;
	initialiser(game, 2);
	char mot[8] = { "ABACULE" };
	strcpy(game.mot, mot);
	game.joueur_precedent = 0;
	game.Joueurs[0].Nature = 'H';


	deviner(game, 0);

	assert(strcmp(game.mot, game.mot_devine) == 0);
	assert(game.joueur_perdant == 0);
	assert(game.perdant_manche == false);
	assert(game.Joueurs[0].points == 0.25);
	desallouer(game);
}


void testDevinerRobot() {

	Jeu game;
	char mot_robot[8] = { "ABACULE" };
	initialiser(game, 2);
	strcpy(game.mot_robot, mot_robot);
	game.joueur_precedent = 0;
	game.Joueurs[0].Nature = 'R';


	deviner(game, 0);

	assert(strcmp(game.mot_robot, game.mot_devine) == 0);
	assert(game.joueur_perdant == 0);
	assert(game.perdant_manche == false);
	assert(game.Joueurs[0].points == 0.25);
	desallouer(game);

}


void testComparer() {

	char mot_vrai[6] = "POMME";
	char mot_faux[6] = "APPLE";

	// Teste si la fonction renvoie true pour un mot qui existe dans le dictionnaire
	bool result = comparer(mot_vrai);
	assert(result == true);

	// Teste si la fonction renvoie false pour un mot qui n'existe pas dans le dictionnaire
	result = comparer(mot_faux);
	assert(result == false);


}


void testPartieHumain() {

	Jeu game;
	initialiser(game, 2);
	char mot[8] = { "ABACUL" };
	strcpy(game.mot, mot);
	game.lettre = 6;
	game.joueur_precedent = 0;
	game.Joueurs[1].Nature = 'H';

	// Teste si la fonction renvoie 1 lorsque le joueur rentre '?'
	int result = partie_humain(game, 2, 1);
	assert(result == 1);
	++game.lettre;

	// Teste si la fonction renvoie 1 lorsque le joueur rentre '!'
	result = partie_humain(game, 2, 1);
	assert(result == 1);
	assert(game.perdant_manche == false);
	assert(game.Joueurs[1].points == 0.25);

	// Teste si la fonction renvoie 1 lorsque le mot rentré existe dans le dictionnaire
	strcpy(game.mot, mot);
	result = partie_humain(game, 2, 1);
	assert(result == 1);
	assert(game.perdant_manche == false);
	assert(game.Joueurs[1].points == 0.5);

	// Teste si la fonction renvoie 0 lorsque le mot rentré n'existe pas dans le dictionnaire
	strcpy(game.mot, "APPLE");
	result = partie_humain(game, 2, 1);
	assert(result == 0);
}

void testChoixRobot() {

	Jeu game;
	initialiser(game, 2);
	char mot[4] = { "ABA" };
	strcpy(game.mot, mot);


	// Teste si la fonction renvoie true si un mot est trouvé dans le dictionnaire qui correspond aux critères
	game.lettre = 3;
	bool result = choix_robot(game);
	assert(result == true);

	// Teste si la fonction renvoie false si aucun mot n'est trouvé dans le dictionnaire qui correspond aux critères
	game.lettre = 4;
	char mot_faux[5] = { "ABCD" };
	strcpy(game.mot, mot_faux);
	result = choix_robot(game);
	assert(result == false);
}

void testPartieRobot() {
	
	Jeu game;
	initialiser(game, 2);
	game.lettre = 3;
	char mot[6] = "ABCDE";
	strcpy(game.mot_robot, mot);
	game.NbJoueurs = 2;
	game.joueur_precedent = 0;
	game.Joueurs[1].Nature = 'R';

	// Teste si la fonction renvoie 1 lorsque le robot choisit '?'
	int result = partie_robot(game, 2, 1);
	assert(result == 1);


	// Teste si la fonction renvoie 0 lorsque le mot rentré n'existe pas dans le dictionnaire
	strcpy(game.mot_robot, "ABA");
	result = partie_robot(game, 2, 1);
	assert(result == 0);

	// Teste si la fonction renvoie 1 lorsque le mot rentré existe dans le dictionnaire
	strcpy(game.mot, "ABA");
	strcpy(game.mot_robot, "ABAT");
	result = partie_robot(game, 2, 1);
	assert(result == 1);

	
}
