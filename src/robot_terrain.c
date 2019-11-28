#include "../include/terrain.h"
#include "../include/robot.h"
#include <stdio.h>

/** @define TAILLE_TERRAIN ?? */
#define TAILLE_TERRAIN 10

/**
 * @function	afficher_orientation
 * @param	Orientation		o		orientation du robot
 * @return void
 */
void afficher_orientation(Robot r) {
	Orientation o = orient(r);
	switch(o) {
		case Nord : 	printf("Nord\n"); break;
		case Est  : 	printf("Est\n"); break;
		case Sud  : 	printf("Sud\n"); break;
		case Ouest: 	printf("Ouest\n"); break;
	}
}

/**
 * @function	afficher_infos_robot
 * @param	Robot		r		Robot_ciblé
 * @return	void
 */
void afficher_infos_robot(Robot r) {
	int x, y;

	// Récupérer la position du robot
	position(r, &x, &y);

	// Afficher la position
	printf("Position : (%d, %d) - Orientation : ", x, y);
	afficher_orientation(r);
	printf("\n");
}

/**
 * @function	afficher_terrain_et_robot
 * @param	Terrain		t		Terrain ciblé
 * @param	Robot		r		Robot ciblé
 * @return void
 */
void afficher_terrain_et_robot(Terrain t, Robot r) {
	int i, j;
	char c;

	for(j = 0; j < t.hauteur; j++) { // hauteur du terrain
		for(i = 0; i < t.largeur; i++) { // largeur du terrain
			if((i == abscisse(r)) && (j == ordonnee(r))) { // si position du robot
				// recupère la position du robot selon son orientation
				switch(orient(r)) {
					case Nord : c = '^'; break;
					case Est  : c = '>'; break;
					case Sud  : c = 'v'; break;
					case Ouest: c = '<'; break;
				}
			} else { // sinon
				// récupère la case correspondante
				switch(t.tab[j][i]) {
					case LIBRE : c = '.'; break;
					case ROCHER: c = '#'; break;
					case EAU   : c = '~'; break;
				}
			}
			printf("%c", c); // affiche l'élèment [i][j]
		}
		printf("\n"); // ligne suivante
	}
}

/**
 * @function	robot_peut_avancer
 * @param	Terrain		t		Terrain ciblé
 * @param	Robot		r		Robot ciblé
 * @return	int
 */
int robot_peut_avancer(Terrain t, Robot r) {
	int peut = 0, // booleen, 0 = ne peut pas, 1 = peut avancer
		x = 0, // position de la case devant le robot
		y = 0;

	position_devant(r, &x, &y);

	// si la case est vide, alors le robot peut
	if(est_case_libre(t, x, y)) {
		peut = 1;
	}

	return peut;
}

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
	// initialisation du terrain, du robot, de la commande
	Terrain t;
	Robot r;
	Erreur_terrain e;
	int x, y;
	char c;
	char *filename;

	// Lecture du terrain : nom du fichier en ligne de commande
	if (argc < 2) {
		printf("Usage: %s <fichier terrain>\n", argv[0]);
		return 1;
	}

	filename = argv[1];
	
	// tant qu'il y a une erreur de lecture
	do {
		// on essaie de lire le terrain
		e = lire_terrain(filename, &t, &x, &y);
		if(e != AUCUNE_ERREUR) {
			// error
			printf("erreur lors de la lecture du fichier %s.\n", filename);
			afficherErreur(e);
			// selection d'un nouveau fichier
			printf("Veuillez saisir un fichier valide: ");
			scanf("%19s", filename);
		}
	} while(e != AUCUNE_ERREUR);

	// success
	init_robot(&r, x, y, Est);

	afficher_infos_robot(r);
	afficher_terrain_et_robot(t,r);

	do {
		printf("Entrer une action ([a]vancer, [g]auche, [d]roite, [f]in) : ");
		scanf(" %c", &c);
		
		switch(c) {
			case 'G':
			case 'g':
				tourner_a_gauche(&r);
				break;
			case 'D':
			case 'd':
				tourner_a_droite(&r);
				break;
			case 'A':
			case 'a':
				if(robot_peut_avancer(t,r)) {
					avancer(&r);
				} else {
					printf(" !! Le robot ne peut pas avancer !!\n");
				}
		}

		afficher_infos_robot(r);
		afficher_terrain_et_robot(t,r);
	} while(c != 'f');
}
