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

// CONSTRUCTOR
/**
  * @function					lire_terrain
  * @param	char				*nom_fichier		nom du fichier à ouvrir
  * @param	Terrain_t			*t					terrain (empty)
  * @param	int					*x					position x du robot Curiosity
  * @param	int					*y					position y du robot Curiosity
  * @return	Erreur_terrain							suivant si la lecture et le stockage des variable s'est bien passé ou non
 */
Erreur_terrain lire_terrain(char *nom_fichier, Terrain *t, int *x, int *y);

// GETTERS
/**
 * @function	largeur			getter
 * @param	Terrain		t		terrain ciblé
 * @return	int
 */
int largeur(Terrain t);

/**
 * @function	hauteur			getter
 * @param	Terrain		t		terrain ciblé
 * @return	int
 */
int hauteur(Terrain t);

/**
 * @function	longueur
 * @param	char	*ligne
 * @return	int
 */
int longueur(char *ligne);

/**
 * @function	est_case_libre
 * @param	Terrain		t		terrain ciblé
 * @param	int			x		case à l'abscisse x où il faut regarder l'état
 * @param	int			y		case à l'ordonnée y où il faut regarder l'état
 * @return	int
 */
int est_case_libre(Terrain t, int x, int y);

/**
 * @function	afficher_terrain
 * @param	Terrain		*t		terrain à afficher
 * @return	void
 */
void afficher_terrain(Terrain *t, int a, int b);

/**
  * @function					ecrire_terrain
  * @param	char				*nom_fichier		nom du fichier à ouvrir
  * @param	Terrain_t			*T					terrain à stringifier dans le fichier
  * @param	int					*x					position x du robot Curiosity
  * @param	int					*y					position y du robot Curiosity
 */
void ecrire_terrain(FILE *f, Terrain T, int x, int y);

#endif
