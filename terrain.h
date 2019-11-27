#ifndef _TERRAIN_H_
#define _TERRAIN_H_

#include <stdio.h>

/**
  * @enum		Case
  *				Valeurs état du terrain
  * @constant	LIBRE		Case vide (non occupée)
  * @constant	ROCHER		Case occupée par un obstacle de type rocher
  * @constant	EAU			Case occupée par un obstacle de type eau
  */
typedef enum
{
	LIBRE,
	EAU,
	ROCHER
} Case;

/** @define DIM_MAX		longueur max qu'une ligne ou un colonne d'une matrice de terrain pourrait avoir */
#define DIM_MAX 256

/**
 * @struct		Terrain
 * @abstract	Contient toutes les propriétés d'un terrain
 * @field	int		largeur		largeur du terrain (abscisse - x)
 * @field	int		hauteur		hauteru du terrain (ordonnée - y)
 * @field	Case	tab			matrice du terrain (quadrillage)
 */
typedef struct
{
	int largeur, hauteur;
	Case tab[DIM_MAX][DIM_MAX];
} Terrain;

/**
 * @enum		Erreur_terrain
 * 				Types d'erreurs rencontrées
 * @constant	ERREUR_FICHIER						le fichier n'a pas pu s'ouvrir ou n'est pas en mode lecture,...
 * @constant	ERREUR_LECTURE_LARGEUR				impossible de lire la largeur du terrain
 * @constant	ERREUR_LECTURE_HAUTEUR				impossible de lire la hauteur du terrain
 * @constant	ERREUR_LARGEUR_INCORRECTE			largeur donnée dépasse les limites autorisées
 * @constant	ERREUR_HAUTEUR_INCORRECTE			hauteur donnée dépasse les limites autorisées
 * @constant	ERREUR_CARACTERE_INCORRECTE			caractère lu pas accepté dans l'alphabet
 * @constant	ERREUR_LIGNE_TROP_LONGUE			la ligne lu n'est pas égale à la largeur donnée pour le terrain (+)
 * @constant	ERREUR_LONGUEUR_LIGNE				la ligne lu n'est dépasse la limite autorisée au max
 * @constant	ERREUR_LIGNES_MANQUANTES			nombre de ligne pas égale à la hauteur donnée du terrain
 * @constant	ERREUR_POSITION_ROBOT_MANQUANTE		Curiosity non trouvé dans le fichier: non positioné
 * @constant	AUCUNE_ERREUR						aucune erreur trouvée
 */
typedef enum
{
	ERREUR_FICHIER,
	ERREUR_LECTURE_LARGEUR,
	ERREUR_LECTURE_HAUTEUR,
	ERREUR_LARGEUR_INCORRECTE,
	ERREUR_HAUTEUR_INCORRECTE,
	ERREUR_CARACTERE_INCORRECTE,
	ERREUR_LIGNE_TROP_COURTE,
	ERREUR_LIGNE_TROP_LONGUE,
	ERREUR_LONGUEUR_LIGNE,
	ERREUR_LIGNES_MANQUANTES,
	ERREUR_POSITION_ROBOT_MANQUANTE,
	AUCUNE_ERREUR
} Erreur_terrain;

// constructor
Erreur_terrain lire_terrain(char *nom_fichier, Terrain *t, int *x, int *y);

// getters
int largeur(Terrain t);
int hauteur(Terrain t);

// boolean state
int est_case_libre(Terrain t, int x, int y);

// printer
void afficher_terrain(Terrain *t,int a,int b);

//terrain random
Terrain random_terrain(int l, int h, float obstacles);

// writer
void ecrire_terrain(FILE *f, Terrain T, int x, int y);

#endif
