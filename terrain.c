#include "terrain.h"
#include "robot.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

/**
 * @function	longueur
 * @param	char	*ligne
 * @return	int
 */
int longueur(char *ligne) {
	int i = 0;
	while(ligne[i] != '\n' && ligne[i] != '\0') i++;
	return i;
}

/**
  * @function					lire_terrain
  * @param	char				*nom_fichier		nom du fichier à ouvrir
  * @param	Terrain_t			*t					terrain (empty)
  * @param	int					*x					position x du robot Curiosity
  * @param	int					*y					position y du robot Curiosity
  * @return	Erreur_terrain							suivant si la lecture et le stockage des variable s'est bien passé ou non
 */
Erreur_terrain lire_terrain(char * nom_fichier, Terrain * t, int * x, int * y) {
	FILE * f;
	int l, h; // Dimensions du terrain
	int rx, ry; // Coordonnées initiales du robot
	char ligne[DIM_MAX];
	Case c;

	// réponses des checks erreurs
	int check;
	char* check2;
	int foundCuriosity = 0;

	// Ouverture du fichier en lecture
	f = fopen(nom_fichier, "r");
	if(f == NULL) { // erreur lors de l'ouverture -> sortie
		return ERREUR_FICHIER;
	}

	// Lecture de la largeur
	check = fscanf(f, "%d", &l); // stockage de la largeur dans l
	if(check == 0 || check == EOF) { // si il n'y avait rien, ou une lettre, ou la fin du fichier -> sortie
		return ERREUR_LECTURE_LARGEUR;
	} else if (l < 0 || l > DIM_MAX) { // si la largeur dépasse les limites -> sortie
		return ERREUR_LARGEUR_INCORRECTE;
	}

	// Lecture de la hauteur
	check = fscanf(f, "%d", &h); // stoackage de la hauteur dans h
	if(check == 0 || check == EOF) { // si rien, lettre ou fin de fichier -> sortie
		return ERREUR_LECTURE_HAUTEUR;
	} else if (h < 0 || h > DIM_MAX) { // si dépassement des limites -> sortie
		return ERREUR_HAUTEUR_INCORRECTE;
	}

	// assignation de la largeur et de la hauteur pour le terrain
	t->largeur = l;
	t->hauteur = h;

	// Lecture du terrain
	fscanf(f, "\n"); // retour à la ligne
	for(int i = 0; i < h; i++) { // ligne par ligne
		check2 = fgets(ligne, DIM_MAX, f); // on recupère la ligne entière (par exemple "#...#.......")
		if(check2 == NULL) { // si ligne vide -> sortie
			return ERREUR_LIGNES_MANQUANTES;
		}

		int len = longueur(ligne); // longueur de la ligne
		if (len > DIM_MAX) { // si elle dépasse la limite autorisée
			return ERREUR_LIGNE_TROP_LONGUE;
		} else if(len != l) { // si la longueur de la ligne est différente de celle annoncée pour le terrain
			return ERREUR_LONGUEUR_LIGNE;
		}

		// pour chaque caractère de la ligne (.#~)
		for(int j = 0; j < l; j++) {
			switch (ligne[j]) {
				case '.': c = LIBRE; 	break;
				case '#': c = ROCHER; 	break;
				case '~': c = EAU; 		break;
				case 'C':
					// Initialisation de la position du robot
					rx = j; // variables intermédiaires
					ry = i;
					c = LIBRE;
					foundCuriosity = 1; // on sauvegarde le fait qu'on ait positioné curiosity
					break;
				default:
					return ERREUR_CARACTERE_INCORRECTE; // caractère rentré non accepté dans l'alphabet -> sortie
			}

			t->tab[i][j] = c; // assignation de la case transformée char -> Case
		}
	}

	// si on n'a pas trouvé Curiosity (et donc pas positioné) -> sortie
	if(!foundCuriosity) {
		return ERREUR_POSITION_ROBOT_MANQUANTE;
	}

	// assignation des posititions initiales du robot
	*x = rx;
	*y = ry;

	// Fermeture du fichier
	fclose(f);
	return AUCUNE_ERREUR;
}

/**
 * @function	largeur			getter
 * @param	Terrain		t		terrain ciblé
 * @return	int
 */
int largeur(Terrain t) {
	return t.largeur;
}

/**
 * @function	hauteur			getter
 * @param	Terrain		t		terrain ciblé
 * @return	int
 */
int hauteur(Terrain t) {
	return t.hauteur;
}

/**
 * @function	afficher_terrain
 * @param	Terrain		*t		terrain à afficher
 * @return	void
 */
void afficher_terrain(Terrain *t,int a,int b) {
	for(int y=0; y < hauteur(*t); y++) { // hauteur du terrain
		for(int x=0; x < largeur(*t); x++) { // largeur du terrain
			if(a == x && b == y){
				printf("c");
			}
			else{
			switch(t->tab[y][x]) { // on ne peut pas afficher un type Case dans un printf, donc on regarde sa correspondance en format char
				case LIBRE: 	printf("."); break;
				case ROCHER: 	printf("#"); break;
				case EAU: 		printf("~");break;
			}
		}
		}
		printf("\n"); // ligne suivante
	}
}

/**
 * @function	est_case_libre
 * @param	Terrain		t		terrain ciblé
 * @param	int			x		case à l'abscisse x où il faut regarder l'état
 * @param	int			y		case à l'ordonnée y où il faut regarder l'état
 * @return	int
 */
int est_case_libre(Terrain t, int x, int y) {
	if(
		x > -1 && // si ne déborder pas à gauche
		y > -1 && // ni en haut
		x < t.largeur && // ni à droite
		y < t.hauteur && // ni en bas
		t.tab[y][x] == LIBRE // et qu'il n'y a pas d'obstacle
	) {
		return 1; // retourne vrai
	}

	return 0; // sinon faux
}

void ecrire_terrain(FILE *f, Terrain T, int x, int y){
	fprintf(f,"%d\n",T.largeur);
	fprintf(f,"%d\n",T.hauteur);
	for(int i=0;i < T.hauteur; i++){
		for(int j=0;j < T.largeur; j++){
			if(x == i & y == j){
				fprintf(f, "c");
			}
			else {
			switch (T.tab[i][j]) {
				case LIBRE:
						fprintf(f,".");
					break;
				case EAU: fprintf(f, "~");break;
				case ROCHER: fprintf(f, "#");break;
			}
			}
		}
		if(i < T.hauteur-1) fprintf(f,"\n");
	}
}
