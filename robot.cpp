#include <iostream>
#include <fstream> // pour ifstream
#include <iomanip> // pour setw
#include <ctime>
#include <cstdlib>
#pragma warning (disable:4996)
#include "jeu.h"

bool choix_robot(Jeu& a)
{
	bool correspondance = true, taille = false;
	uint j = 0;
	uint nbmot = 0, choix = 1;
	ifstream in("ods4.txt"); // on ouvre le fichier
	if (!in) {
		cout << "Le dictionnaire n'a pu etre ouvert" << endl;
		return false;
	}
	char mot_dico[MAX_CAR];
	in >> setw(MAX_CAR) >> mot_dico; // on essaye de lire le premier mot
	//V�rification de la correspondance des lettres

	while (in)
	{
		//V�rification de la correspondance des lettres
		for (uint i = 0; i < a.lettre; ++i)
		{
			if (a.mot[i] == mot_dico[i])
			{
				++j;
			}

		}
		uint derniere_lettre = strlen(mot_dico) - a.lettre;
		if (derniere_lettre == 1)
		{
			--j;
		}
		choix = (strlen(mot_dico) - a.lettre) % a.NbJoueurs;
		if (choix != 0 && j == a.lettre)
		{
			nbmot = 1;
			strcpy(a.mot_robot, mot_dico);
		}
		j = 0;
		taille = false;
		in >> setw(MAX_CAR) >> mot_dico; // on essaye de lire le mot suivant
	}
	in.close(); // on ferme le fichier
	if (nbmot == 0)
		return false;
	else
		return true;
}
int partie_robot(Jeu& a,const uint nbjoueurs,const uint numj)
{
	bool correspondance = true;
	char lettre_alphabet = (char)('A' + rand() % 26);


	bool choix = choix_robot(a);
	uint derniere_lettre = strlen(a.mot_robot) - a.lettre;
	cout << numj + 1 << a.Joueurs[numj].Nature << ", ";
	cout << "(" << a.mot << ") > ";

	if (strlen(a.mot) == 0 )
	{
		cout << lettre_alphabet << endl;
		a.mot[a.lettre] = lettre_alphabet;
	}

	else if (choix == false || derniere_lettre == 1)
	{
		cout << "?" << endl;
		deviner(a, numj);
		return 1;
	}
	else

	{
		cout << a.mot_robot[a.lettre] << endl;;
		a.mot[a.lettre] = a.mot_robot[a.lettre];
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
