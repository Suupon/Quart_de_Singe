#include <iostream>
#include <fstream> // pour ifstream
#include <iomanip> // pour setw
#include <ctime>
#include <cstdlib>
#pragma warning (disable:4996)
#include "jeu.h"


int partie_humain(Jeu& a,const uint nbjoueurs,const uint numj)
{
	bool correspondance = true;

	if (a.lettre >= MAX_CAR)
	{

	}


	//Affichage 1H (mot)>
	cout << numj + 1 << a.Joueurs[numj].Nature << ", ";
	cout << "(" << a.mot << ") > ";
	cin >> a.mot[a.lettre];
	convertir(a.mot, a.lettre + 1);

	//Cas ou le joueur rentre '?'
	if (a.mot[a.lettre] == '?')
	{
		deviner(a, numj);
		return 1;
	}


	//Cas ou le joueur rentre '!'
	if (a.mot[a.lettre] == '!')
	{
		cout << "le joueur " << numj + 1 << a.Joueurs[numj].Nature << " abandonne la manche et prend un quart de singe" << endl;
		a.Joueurs[numj].points += 0.25;
		a.joueur_perdant = numj;
		a.perdant_manche = false;
		return 1;
	}

	if (comparer(a.mot) == true)
	{
		cout << "Le mot " << a.mot << " existe le joueur " << numj + 1 << " prend un quart de singe" << endl;
		a.Joueurs[numj].points += 0.25;
		a.joueur_perdant = numj;
		return 1;
	}
	a.joueur_precedent = numj;
	++a.lettre;
	return 0;
}