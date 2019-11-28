#ifndef _ROBOT_H_
#define _ROBOT_H_

/**
  * @enum	Orientation
  * 		les 4 directions horizontales et verticales possibles
  * @constant	Nord	(haut)
  * @constant	Est		(droite)
  * @constant	Sud		(bas)
  * @constant	Ouest	(gauche)
  */
typedef enum { Nord, Est, Sud, Ouest } Orientation;

/**
 * @struct	Robot
 * @abstract	contient toutes les propriétés du robot
 * @field	int				x		position x (abscisse) du robot sur le terrain
 * @field	int				y		position y (ordonnée) du robot sur le terrain
 * @field	Orientation		o		orientation du robot sur le terrain
 */
typedef struct {
	int x, y;
	Orientation o;
} Robot;

/**
 * @function init_robot
 * @param   Robot           *r      Robot ciblé
 * @param   int             x       x que doit prendre le robot pour abscisse
 * @param   int             y       y que doit prendre le robot pour ordonnée
 * @param   Orientation     o       orientation que doit prendre le robot
 * @return  void
 */
void init_robot(Robot *r, int x, int y, Orientation o);

/**
 * @function    avancer
 * @param   Robot   *r      Robot ciblé
 * @return  void
 */
void avancer(Robot *r);

/**
 * @function    tourner_a_gauche
 * @param   Robot   *r      Robot ciblé
 * @return  void
 */
void tourner_a_gauche(Robot *r);

/**
 * @function    tourner_a_droite
 * @param   Robot   *r      Robot ciblé
 * @return  void
 */
void tourner_a_droite(Robot *r);

/**
 * @function    position
 * @param   Robot   r       Robot ciblé
 * @param   int     *x      x qui recevra la position x du robot
 * @param   int     *y      y qui recevra la position y du robot
 * @return  void
 */
void position(Robot r, int *x, int *y);

/**
 * @function    abscisse    getter
 * @param   Robot   r       Robot ciblé
 * @return  int
 */
int abscisse(Robot r);

/**
 * @function    ordonnee    getter
 * @param   Robot   r       Robot ciblé
 * @return  int
 */
int ordonnee(Robot r);

/**
 * @function    orient      getter
 * @param   Robot   r       Robot ciblé
 * @return  Orientation
 */
Orientation orient(Robot r);

/**
 * @function    position_devant
 * @param   Robot   r       Robot ciblé
 * @param   int     *x      x qui recevra le x de la case située devant le robot
 * @param   int     *y      y qui recevra le y de la case située devant le robot
 * @return void
 */
void position_devant(Robot r, int *x, int *y);

#endif
