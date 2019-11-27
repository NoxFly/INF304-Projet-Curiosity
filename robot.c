#include "robot.h"
#include <stdio.h>

void init_robot(Robot * r, int x, int y, Orientation o) {
    r->x = x;
    r->y = y;
    r->o = o;
}
	
void avancer(Robot *r) {
    int x = 0,
        y = 0;
    
    // on prend les coordonnées de la case devant le robot suivant son orientation
    position_devant(*r, &x, &y);

    // on le fait avancer
    r->x = x;
    r->y = y;
}

void tourner_a_gauche(Robot *r) {
    // nouvelle orientation
    Orientation nouvOri;
    // on choisi l'orientation qu'aura le robot en fonction de son orientation acutelle
    switch(r->o) {
        case Nord:  nouvOri = Ouest; break;
        case Est:   nouvOri = Nord; break;
        case Sud:   nouvOri = Est; break;
        case Ouest: nouvOri = Sud; break;
    }

    // affectation
    r->o = nouvOri;
}

void tourner_a_droite(Robot *r) {
    // nouvelle orientation
    Orientation nouvOri;
    // on choisi l'orientation qu'aura le robot en fonction de son orientation acutelle
    switch(r->o) {
        case Nord:  nouvOri = Est; break;
        case Est:   nouvOri = Sud; break;
        case Sud:   nouvOri = Ouest; break;
        case Ouest: nouvOri = Nord; break;
    }

    // affectation
    r->o = nouvOri;
}

void position(Robot r, int *x, int *y) {
    *x = r.x;
    *y = r.y;
}

int abscisse(Robot r) {
    return r.x;
}

int ordonnee(Robot r) {
    return r.y;
}

Orientation orient(Robot r) {
    return r.o;
}

void position_devant(Robot r, int *x, int *y) {
    // vecteur directionnel de longueur absolue |v| = 1  // (-1,0,1)
    int ox = 0,
        oy = 0;

    // suivant l'orientation, on change un vecteur dans le sens du regard du robot
    switch(r.o) {
        case Nord:  oy--; break;
        case Sud:   oy++; break;
        case Est:   ox++; break;
        case Ouest: ox--; break;
    }

    // on affecte à x et y la position du robot + v
    *x = r.x + ox;
    *y = r.y + oy;
}