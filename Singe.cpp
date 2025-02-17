#include <iostream>
#include <fstream> // pour ifstream
#include <iomanip> // pour setw
#include <ctime>
#include <cstdlib>
#pragma warning (disable:4996)
#include "jeu.h"

using namespace std;

int main(int argc, char* jeu[])
{
	Jeu a;
	int nbjoueurs;
	srand((unsigned int)time(NULL));
	if (argc >= 2)
	{
		nbjoueurs = strlen(jeu[1]);
		convertir(jeu[1], nbjoueurs);
		lancement(a, nbjoueurs, jeu[1]);
		desallouer(a);
	}
}



