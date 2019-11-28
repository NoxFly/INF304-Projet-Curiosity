#include "../include/terrain.h"
#include <stdio.h>

/**
 * @function	afficherErreur
 * @param	Erreur_terrain		e		type d'erreur
 * @return void
 */
void afficherErreur(Erreur_terrain e) {
	switch(e) {
		case ERREUR_FICHIER: 					printf("ERREUR_FICHIER\n"); break;
		case ERREUR_LECTURE_LARGEUR: 			printf("ERREUR_LECTURE_LARGEUR\n"); break;
		case ERREUR_LECTURE_HAUTEUR: 			printf("ERREUR_LECTURE_HAUTEUR\n"); break;
		case ERREUR_LARGEUR_INCORRECTE: 		printf("ERREUR_LARGEUR_INCORRECTE\n"); break;
		case ERREUR_HAUTEUR_INCORRECTE: 		printf("ERREUR_HAUTEUR_INCORRECTE\n"); break;
		case ERREUR_CARACTERE_INCORRECTE: 		printf("ERREUR_CARACTERE_INCORRECT\n"); break;
		case ERREUR_LIGNE_TROP_LONGUE: 			printf("ERREUR_LIGNE_TROP_LONGUE\n"); break;
		case ERREUR_LONGUEUR_LIGNE: 			printf("ERREUR_LONGUEUR_LIGNE\n"); break;
		case ERREUR_LIGNES_MANQUANTES: 			printf("ERREUR_LIGNES_MANQUANTES\n"); break;
		case ERREUR_POSITION_ROBOT_MANQUANTE: 	printf("ERREUR_POSITION_ROBOT_MANQUANTE\n"); break;
		default: break;
	}
}

/**
 * @function  main
 * @param	int		argc	nombre d'argument
 * @param	char	**argv	vecteur d'argument
 * @return	int
 */
int main(int argc, char ** argv) {
	// initialisation du terrain et des valeurs intermédiaires du robot
	Terrain* t = NULL;
	int x, y;
	char *filename; // nom du fichier à ouvrir

	// si pas bon nombre d'argument -> sortie
	if(argc < 2) {
		printf("Usage : %s <fichier>\n", argv[0]);
		return 1;
	}

	filename = argv[1];

	// on place volontairement une erreur pour rentrer au moins une fois dans le while
	Erreur_terrain e = ERREUR_FICHIER;

	// tant qu'il y a une erreur de lecture
	while(e != AUCUNE_ERREUR) {
		// on essaie de lire le terrain
		e = lire_terrain(filename, t, &x, &y);
		if(e != AUCUNE_ERREUR) {
			// error
			printf("erreur lors de la lecture du fichier %s.\n", filename);
			afficherErreur(e);
			// selection d'un nouveau fichier
			printf("Veuillez saisir un fichier valide: ");
			scanf("%19s", filename);
		}
	}

	// success
	afficher_terrain(t,(int)(t->largeur)/2,(int)(t->hauteur)/2);
	printf("Position initiale du robot : (%d, %d)\n", x, y);
}
