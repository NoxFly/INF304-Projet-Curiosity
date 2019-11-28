#include "../include/robot.h"
#include <stdio.h>

/** @define TAILLE_TERRAIN ?? */
#define TAILLE_TERRAIN 10

/**
 * @function	afficher_orientation
 * @param	Orienation	o	orientation du robot
 * @return	void
 */
void afficher_orientation(Robot r) {
	Orientation o = orient(r);
	switch(o) {
		case Nord : printf("Nord\n"); break;
		case Est  : printf("Est\n"); break;
		case Sud  : printf("Sud\n"); break;
		case Ouest: printf("Ouest\n");
	}
}

/**
 * @function afficher_infos_robot
 * @param	Robot	r	Robot ciblé
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
 * @function	main
 * @param	int		argc	nombre d'argument
 * @param	char	**argv	vecteur d'argument
 * @return	int
 */
int main(int argc, char ** argv) {
	// initialisation du robot et de la commande utilisateur
	Robot r;
	char c;

	// initialisation personnalisée du robot (0,0,Est)
	init_robot(&r, 0, 0, Est);

	// affiche les infos relatives au robot r
	afficher_infos_robot(r);

	do {
		printf("Entrer une action ([a]vancer, [g]auche, [d]roite, [f]in) : ");
		scanf(" %c", &c);

		switch(c) {
			case 'a': avancer(&r); break;
			case 'g': tourner_a_gauche(&r); break;
			case 'd': tourner_a_droite(&r);
		}

		afficher_infos_robot(r);
	} while(c != 'f');
}