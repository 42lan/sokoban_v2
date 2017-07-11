#ifndef __SOKO__
#define __SOKO__

/* Aliace ajaxVitre avec commande UNIX pour effacer l'écran du terminal */
#ifndef __UNIX__
	#define ajaxVitre system("clear");
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAXCH 40
#define TAILLE_MAX 10 /* pour fgets() dans initGrille() */


/*char* ptin;
char* ptout;
int nb=0;*/

/* Définition des termes qui ont des valeurs correspondant aux entiers */
typedef enum {false=0, true}Boolean;
typedef enum {MUR='#', CAISSE='O', CIBLE='o', SOKOBAN='S', VIDE='.'}Symbole;
typedef enum {HAUT='h', BAS='b', GAUCHE='g', DROITE='d', AIDE='a', QUITTER='q'}Commande;
typedef enum {ERR_OPEN=10, NO_SOKOBAN, G_INCORECT, UNE_CAISSE, DIF_CAICIB, ALLOC_TAB, ALLOC_TABn2}CodeErreur;

typedef char* Ligne;

typedef struct _grille{
	int h;	/* Hauteur */
	int L;	/* Largeur */
	Ligne* grille;
} Grille;

typedef struct{
    int x, y;
} Position;

/* Partie SOKOBAN_1 */
void aide();
void error(CodeErreur code);
void nouveauJeu(Grille init, Grille g);
void deplace(Grille jeu, Position pos_a, Position pos_b, Grille init);
int compte(Grille g, char c);
Position getSokoban(Grille g);
Position pas(Position pos_depart, Commande instruction);
Position joue(Grille jeu, Commande dir, Position depart, Grille init);
Boolean verif(Grille g);
Boolean possible(Grille g, Position pos);
Boolean gagne(Grille jeu, Position soko, Grille init);

/* Partie SOKOBAN_2 */
void afficheGrille(Grille g);
Grille initGrille(char* nomFichier);
void freeGrille(Grille g);
Grille creerGrille(int hauteur, int largeur);
Grille copieGrille(Grille g);
Boolean verif(Grille g);
void automate();

#endif
