#include "jeu.h"
#include <iostream>
#include <fstream> // pour ifstream
#include <iomanip> // pour setw
#include <ctime>
#include <cstdlib>
#pragma warning (disable:4996)
#include "humain.h"
#include "robot.h"

using namespace std;

void convertir(char tab[],const size_t taille)
{
	char maj;
	for (uint i = 0; i < taille; ++i)
	{
		maj = toupper(tab[i]);
		tab[i] = maj;
	}
}

int verifjoueurs(const uint nbjoueurs)
{
	if (nbjoueurs < MIN_JOUEURS)
	{
		printf("Il doit y avoir au moins 2 joueurs\n");
		return 1;
	}
	return 0;
}
int verifnature(const char tab[],const uint nbjoueurs)
{

	for (uint i = 0; i < nbjoueurs; ++i)
	{
		if (tab[i] != 'H' && tab[i] != 'R')
		{
			printf("Le joueur ne peut etre qu'un Humain (H) ou un Robot (R)\n");
			return 1;
		}
	}
	return 0;
}

void initialiser(Jeu& a,const uint nbjoueurs)
{
	a.NbJoueurs = nbjoueurs;
	a.Joueurs = new Joueurs[nbjoueurs];
	for (uint i = 0; i < nbjoueurs; ++i)
	{
		a.Joueurs[i].points = 0;
	}
	for (int i = 0; i < MAX_CAR; ++i)
	{
		a.mot[i] = 0;
		a.mot_devine[i] = 0;
		a.mot_robot[i] = 0;
	}
	a.lettre = 0;
	a.joueur_perdant = 0;
}

bool comparer(const char mot[])
{
	bool mot_existe = false, devine_existe = false;
	ifstream in("ods4.txt"); // on ouvre le fichier
	if (!in) {
		cout << "Le dictionnaire n'a pu etre ouvert" << endl;
		return false;
	}
	char mot_dico[MAX_CAR];
	in >> setw(MAX_CAR) >> mot_dico; // on essaye de lire le premier mot
	while (in) {

		if (strcmp(mot, mot_dico) == 0)
		{
			devine_existe = true;
		}
		in >> setw(MAX_CAR) >> mot_dico; // on essaye de lire le mot suivant
	}

	in.close(); // on ferme le fichier
	if (devine_existe == true)
		return true;
	else
		return false;
}



void deviner(Jeu& a,const uint numj)
{
	bool correspondance = true;
	cout << a.joueur_precedent + 1 << a.Joueurs[a.joueur_precedent].Nature << ",";
	cout << " saisir le mot > ";
	if (a.Joueurs[a.joueur_precedent].Nature == 'R')
	{
		strcpy(a.mot_devine, a.mot_robot);
	}
	else
	{
		cin >> a.mot_devine;
		convertir(a.mot_devine, strlen(a.mot_devine) + 1);
	}

	//V�rification de la correspondance des lettres
	for (uint i = 1; i <= a.lettre; ++i)
	{
		if (a.mot[i - 1] != a.mot_devine[i - 1])
		{
			correspondance = false;
			break;
		}
	}

	if (correspondance == false)
	{
		cout << "le mot " << a.mot_devine << " ne commence pas par les lettres attendues, ";
		cout << "le joueur " << a.joueur_precedent + 1 << a.Joueurs[a.joueur_precedent].Nature << " prend un quart de singe" << endl;
		a.Joueurs[a.joueur_precedent].points += 0.25;
		a.joueur_perdant = a.joueur_precedent;
		a.perdant_manche = false;
	}
	//Si le mot existe ou pas
	else if (comparer(a.mot_devine) == true)
	{
		cout << "le mot " << a.mot_devine << " existe, ";
		cout << "le joueur " << numj + 1 << a.Joueurs[numj].Nature << " prend un quart de singe" << endl;
		a.Joueurs[numj].points += 0.25;
		a.joueur_perdant = numj;
		a.perdant_manche = false;
	}
	else
	{
		cout << "le mot " << a.mot_devine << " n'existe pas, ";
		cout << "le joueur " << a.joueur_precedent + 1 << a.Joueurs[a.joueur_precedent].Nature << " prend un quart de singe" << endl;
		a.Joueurs[a.joueur_precedent].points += 0.25;
		a.joueur_perdant = a.joueur_precedent;
		a.perdant_manche = false;
	}
}

void lancement(Jeu& a,const uint nbjoueurs, char tab[])
{
	bool virgule = false;
	int fin_manche = 0;
	bool fin_partie = false;
	a.perdant_manche = true;
	a.joueur_precedent = 0;
	initialiser(a, nbjoueurs);
	int verif = verifjoueurs(nbjoueurs);
	verif += verifnature(tab, nbjoueurs);
	if (verif > 0)
		return;
	for (uint i = 0; i < nbjoueurs; ++i)
	{
		a.Joueurs[i].Nature = tab[i];

	}
	do
	{
		do
		{
			for (uint numj = 0; numj < nbjoueurs; ++numj)
			{
				//Pour que le joueur perdant commence
				if (a.perdant_manche == false)
				{
					numj = a.joueur_perdant;
					a.perdant_manche = true;
				}

				if (tab[numj] == 'H')
				{
					fin_manche = partie_humain(a, nbjoueurs, numj);
					if (fin_manche == 1)
						break;

				}
				else if (tab[numj] == 'R')
				{
					fin_manche = partie_robot(a, nbjoueurs, numj);
					if (fin_manche == 1)
						break;
				}
				a.premier_tour = false;
			}
		} while (fin_manche != 1);


		for (uint i = 0; i <= a.lettre; ++i)
		{
			a.mot_precedent[i] = a.mot[i];
			a.mot[i] = 0;
		}
		for (int i = 0; i <= strlen(a.mot_devine); ++i)
		{
			a.mot_devine[i] = 0;
		}
		for (uint i = 0; i < nbjoueurs; ++i)
		{
			if (virgule == true)
			{
				cout << "; ";
			}
			else
			{
				virgule = true;
			}
			cout << i + 1 << a.Joueurs[i].Nature << " : " << a.Joueurs[i].points;

		}
		cout << endl;
		virgule = false;
		a.lettre = 0;
		for (uint i = 0; i < nbjoueurs; ++i)
		{
			if (a.Joueurs[i].points == 1)
			{
				cout << "Le joueur " << i + 1 << a.Joueurs[i].Nature << " a perdu" << endl;
				cout << "La partie est finie" << endl;
				fin_partie = true;
			}
		}



	} while (fin_partie == false);

}


void desallouer(Jeu& a)
{
	delete[] a.Joueurs;
	a.NbJoueurs = 0;
}