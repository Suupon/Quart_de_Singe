#pragma once

#include "jeu.h"

typedef unsigned int uint;

enum
{
	MAX_CAR = 27,
	MIN_JOUEURS = 2,
};
typedef struct {
	char Nature;
	float points;
}Joueurs;

typedef struct {
	Joueurs* Joueurs;
	char mot[MAX_CAR];
	char mot_precedent[MAX_CAR];
	char mot_devine[MAX_CAR];
	uint NbJoueurs;
	uint joueur_perdant;
	uint lettre;
	uint numj;
	bool premier_tour;
	uint joueur_precedent;
	bool perdant_manche;
	char mot_robot[MAX_CAR];
}Jeu;


using namespace std;

void convertir(char tab[],const uint nbjoueurs);


int verifjoueurs(const uint nbjoueurs);

int verifnature(char tab[],const uint nbjoueurs);


void initialiser(Jeu& a,const uint nbjoueurs);

bool comparer(const char mot[]);



void deviner(Jeu& a,const uint numj);


void lancement(Jeu& a,const uint nbjoueurs, char tab[]);


void desallouer(Jeu& a);