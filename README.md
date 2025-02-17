# 🐵 Projet : Jeu du Quart de Singe

## 📜 Description

Ce projet implémente un jeu du type "mot à compléter" où des joueurs humains et des robots participent à la création d'un mot à tour de rôle. Le but du jeu est d'éviter de compléter un mot inexistant ou de perdre en accumulant des pénalités.

Le programme gère des interactions entre joueurs humains et robots, et utilise un dictionnaire externe (`ods4.txt`) pour valider l'existence des mots.

## 🎲 Règles du jeu

1. Le jeu se joue avec au minimum deux joueurs (humains ou robots).
2. Les joueurs ajoutent une lettre au mot en cours à tour de rôle.
3. Un joueur peut décider de deviner le mot s'il pense que celui-ci est complet.
4. Si un joueur entre un mot qui n'existe pas, il reçoit une pénalité.
5. Lorsqu'un joueur accumule une pénalité complète (1 point), il perd la partie.
6. La partie continue jusqu'à ce qu'un joueur atteigne la limite de pénalité.

## 🏗️ Structure du projet

Le projet est organisé en plusieurs fichiers :

### 1. **📂 Fichiers principaux**

- `Singe.cpp` : Point d'entrée du programme. Initialise le jeu et gère la boucle principale.
- `jeu.cpp` / `jeu.h` : Contient la gestion du jeu, notamment l'initialisation, le déroulement des manches et la validation des mots.
- `humain.cpp` / `humain.h` : Implémente la logique des joueurs humains.
- `robot.cpp` / `robot.h` : Implémente la logique des robots qui participent au jeu.

### 2. **🧪 Tests unitaires**

- `TestUnitaires.cpp` / `Test_Unitaires.h` : Contient des tests unitaires pour valider le bon fonctionnement des différentes fonctionnalités du jeu.

## 🔥 Fonctionnalités

- Gestion de joueurs humains et robots.
- Validation des mots avec un dictionnaire externe (`ods4.txt`).
- Prise en charge de pénalités progressives pour les joueurs qui perdent une manche.
- Implémentation de tests unitaires pour assurer la stabilité du jeu.

## Compilation et Exécution

### ⚙️ Compilation avec `g++`

```sh
 g++ -o Singe Singe.cpp jeu.cpp humain.cpp robot.cpp TestUnitaires.cpp -Wall -Wextra -std=c++11
```

### ▶️ Exécution

```sh
 ./Singe HRH
```

Où `HRH` représente la séquence des joueurs (H = Humain, R = Robot).

## 📌 Remarque

Le fichier `ods4.txt` doit être présent dans le répertoire d'exécution du programme, car il est utilisé pour la vérification des mots.

## 👨‍💻 Auteur
- **Aymen** - [Ton GitHub](https://github.com/Suupon)

---

