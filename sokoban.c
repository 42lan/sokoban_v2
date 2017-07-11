#include "sokoban.h"

Position getSokoban(Grille g){
	int i, j;
	Position position = {0, 0};

	for(i=0; i<g.h; i++){
		for(j=0; j<g.L; j++){
			if(g.grille[i][j]=='S'){
				position.x = i;
				position.y = j;
			}
		}
	}
	return position;
}





void nouveauJeu(Grille init, Grille g){
	int i, j;
	for(i=0; i<g.h; i++){
		for(j=0; j<g.L+1; j++){
			g.grille[i][j] = init.grille[i][j];
			if((init.grille[i][j]==CAISSE)||(init.grille[i][j]==SOKOBAN))
				init.grille[i][j]=VIDE;
		}
	}
}




Boolean verif(Grille g){
	int i, j, nbCaisses=0, nbCibles=0;

	for(i=0; i<g.h; i++){
		j=0;

		while(g.grille[i][j]!='\0')
			j++;
		if(g.L!=j)
			error(12); /* G_INCORECT */
	}


	for(i=0; i<g.h; i++){
		for(j=0; j<g.L; j++){
			if(g.grille[i][j]==CAISSE)
				nbCaisses++;
			if(g.grille[i][j]==CIBLE)
				nbCibles++;
		}
	}

	if(nbCaisses==0)
		error(13); /* UNE_CAISSE */

	if(nbCaisses!=nbCibles)
		error(14); /* DIF_CAICIB */
	return true;
}




int compte(Grille g, char c){
	int i, j, nb_occ=0;

	for(i=0; i<g.h; i++)
		for(j=0; j<g.L; j++)
			if(g.grille[i][j]==c)
				nb_occ++;
	return nb_occ;
}




void aide(){
	printf("Aide:\n");
	printf("  (%c)MUR, (%c)CAISSE, (%c)CIBLE, (%c)SOKOBAN, (%c)VIDE\n", MUR, CAISSE, CIBLE, SOKOBAN, VIDE);
	printf("  (%c)ide, (%c)quitter, (%c)aut, (%c)as, (%c)auche, (%c)roite\n", AIDE, QUITTER, HAUT, BAS, GAUCHE, DROITE);
}




Position pas(Position pos_depart, Commande cmd){
	Position position_actuelle;
	position_actuelle=pos_depart;

	switch (cmd){
		case HAUT:		position_actuelle.x--; break;
		case BAS:		position_actuelle.x++; break;
		case GAUCHE:	position_actuelle.y--; break;
		case DROITE:	position_actuelle.y++; break;
		default: break;
	}
	return position_actuelle;
}



Boolean possible(Grille g, Position pos){
	if((g.grille[pos.x][pos.y]==MUR)||(g.grille[pos.x][pos.y]==CAISSE))
		return false;
	return true;
}




void deplace(Grille jeu, Position pos_a,Position pos_b, Grille g){
	jeu.grille[pos_b.x][pos_b.y]=jeu.grille[pos_a.x][pos_a.y];
	jeu.grille[pos_a.x][pos_a.y]=g.grille[pos_a.x][pos_a.y];
}



Position joue(Grille jeu, Commande dir, Position depart, Grille init){
	Position futur_pos;
	futur_pos=pas(depart, dir);

	if(possible(jeu, futur_pos)==true)
		deplace(jeu, depart, futur_pos, init);
	else{
		if(jeu.grille[futur_pos.x][futur_pos.y]==MUR)
			printf("Impossible à cause d'un Mur devant\n");
		if(jeu.grille[futur_pos.x][futur_pos.y]==CAISSE){
			if(possible(jeu, pas(futur_pos, dir))==true){
				deplace(jeu, futur_pos, pas(futur_pos, dir), init);
				deplace(jeu, depart, futur_pos, init);
			}
		}
	}
	return futur_pos;
}




Boolean gagne(Grille jeu, Position soko, Grille init){
	int i, j, nbCibles=0;
	for(i=0; i<jeu.h; i++){
		for(j=0; j<jeu.L; j++){
			if(jeu.grille[i][j]==CIBLE)
				nbCibles++;
		}
	}
	if((nbCibles==0)&&(init.grille[soko.x][soko.y]!=CIBLE))
		return true;
	return false;
}


/* Fonction qui gère les erreur en affichant le message correspondant au code
 * passé en paramètre
 */
void error(CodeErreur code){
	switch(code){
		case ERR_OPEN : fprintf(stderr,"Impossible d'ouvrir le fichier!\n"); break;
		case NO_SOKOBAN : fprintf(stderr,"Pas de Sokoban!\n"); break;
		case G_INCORECT : fprintf(stderr,"Grille initiale incorrecte !\n"); break;
		case UNE_CAISSE : fprintf(stderr,"Au moins une Caisse doit etre presente\n"); break;
		case DIF_CAICIB : fprintf(stderr,"Nombre de Caisses et des Cibles n'est pas egal\n"); break;
		case ALLOC_TAB : fprintf(stderr,"Allocation de la mémoire pour la boîte de 12 ligne a échoué!\n"); break;
		case ALLOC_TABn2 : fprintf(stderr,"Allocation de la mémoire pour 25 cases d'une des ligne a échoué\n"); break;
		default: fprintf(stderr,"Code erreur inconnu!\n");
	}
	exit(code);
}



/* Affiche la grille passée en paramètre précédée d'une ligne blanche.
 */
void afficheGrille(Grille g){
	int i, j;
	for(i=0; i<g.h; i++){
		for(j=0; j<g.L; j++)
			printf("%c", g.grille[i][j]);
		printf("\n");
	}
}



/* Initialise la grille en ouvrant le fichier du nom passé en paramétre.
 *
 * Les code d'erreurs
 * error(10) - Impossible d'ouvrir le fichier
 * error(15) - Alloc de mém pour la boîte de 12 ligne a échoué
 * error(16) - Alloc de mém pour 25 cases d'une des lignes a échoué
 */
 Grille initGrille(char* nomFichier){
 	FILE* fichier = NULL;
 	char buffer[TAILLE_MAX] = ""; /* Buffer-chaine vide de taille TAILLE_MAX */
	Grille g;
	int i, hauteur, largeur;

 	fichier = fopen(nomFichier, "r");
 	if(fichier == NULL)
 		error(10); /* ERR_OPEN */

 	fgets(buffer, TAILLE_MAX, fichier); /* printf("%s", buffer); */
 	sscanf(buffer, "%d %d", &hauteur, &largeur);

	g = creerGrille(hauteur, largeur);
	for(i=0; i<g.h; i++){
		fgets(g.grille[i], g.L+1, fichier);
		fgetc(fichier);
	}

	fclose(fichier);
 	return g;
}



/* Crée une variable Grille et affecte les bonnes dimensions à ces champs
 * en allouant l'espace necessaire, puis renvoit la Grille
 */
Grille creerGrille(int hauteur, int largeur){
	Grille g;
	int i, j;
	g.h = hauteur;
	g.L = largeur;


	g.grille = malloc(sizeof(Ligne) * g.h);
 	if(g.grille == NULL)
 		error(15); /* ALLOC_TAB */

 	for(i=0; i<g.h; i++){
 		g.grille[i] = malloc(sizeof(char) * (g.L+1));
 		if(g.grille[i] == NULL){
 			for(j=0; j<g.L+1; j++) /* j < g.L+1     j < i*/
 				free(g.grille[j]);
 			free(g.grille);
 			error(16); /* ALLOC_TABn2 */
 		}
 	}

	return g;
}



/* Apelle creerGrille() et copie dans la nouvelle grille la grille passée en paramètre
 */
Grille copieGrille(Grille init){
	Grille g;
	int i;
	g = creerGrille(init.h, init.L);
	for(i=0; i<g.h; i++){
		strcpy(g.grille[i], init.grille[i]);
	}
	
	return g;
}


/* Libère la mémoire réservée pour la grille passée en paramètre
void freeGrille(Grille g){
	free(g.grille);
}
*/


/* automate_dcmprsCharInt
void trnsfChartoInt{ nb=(nb*10) + (c-'0'); }
void statLet(char c){
	if(nb==0) *ptout=c;
	else
		memset(ptout, c, nb);
		ptout=ptout+(nb+1);
		nb=0;
	ptout++;
}
void initOut(char* o, int i){ memset(o, '\0', i); }
 */
