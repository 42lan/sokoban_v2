#include "sokoban.h"

/*#include "pileGrille.h"*/

/*int main(int argc, char ** argv){
	Grille gCache;
	Grille jeu=initGrille(argv[1]);

	gCache = copieGrille(jeu);

	printf("Grille de jeu\n");	afficheGrille(jeu);
	printf("Grille caché\n");	afficheGrille(gCache);

	return 0;
}*/



int main(int argc, char ** argv){
	Grille jeu;
	Grille gCache;
	Boolean encore;
	Position positionSokoban;
	char instruction[MAXCH+1];
	int coups=0;
	
	jeu=initGrille(argv[1]);
	gCache = copieGrille(jeu);
	encore=true;

	nouveauJeu(gCache, jeu);
	/*afficheGrille(jeu);
	afficheGrille(gCache);*/

	positionSokoban=getSokoban(jeu);

	ajaxVitre;
	if((positionSokoban.x==0) && (positionSokoban.y==0))
		error(11); /* NO_SOKOBAN */
	else
		printf("La position du Sokoban est en (%d;%d)\n", positionSokoban.x, positionSokoban.y);

	verif(jeu);

	
	
	do{
		int i;
		afficheGrille(jeu);
		printf("> ");
		if(fgets(instruction, MAXCH, stdin)==NULL);
		for(i=0; instruction[i]!='\n'; i++){
			ajaxVitre;
			positionSokoban=getSokoban(jeu);
			switch(instruction[i]){
				case HAUT: 		joue(jeu, instruction[i], positionSokoban, gCache); break;
				case BAS: 		joue(jeu, instruction[i], positionSokoban, gCache); break;
				case GAUCHE: 	joue(jeu, instruction[i], positionSokoban, gCache); break;
				case DROITE: 	joue(jeu, instruction[i], positionSokoban, gCache); break;
				case AIDE:		aide(); break;
				case QUITTER: 	encore=false; break;
				default: printf("Instruction inconnu\n"); break;
			}
			coups++;
		}
		if(gagne(jeu, getSokoban(jeu), gCache)==true)
			printf("Félicitations! Tu as gagné en %d coups\n", coups);
	} while(encore==true);

	return 0;
}
