#include "environnement.h"
#include "programme.h"
#include "interprete.h"

#include <stdio.h>
#include <stdlib.h>

#define LMAX 1000

void gestion_erreur_terrain(Erreur_terrain e) {
	switch(e) {
		case AUCUNE_ERREUR:
			break;
		case ERREUR_FICHIER:
			printf("Erreur lecture du terrain : erreur d'ouverture du fichier\n");
			exit(1);
		case ERREUR_LECTURE_LARGEUR:
			printf("Erreur lecture du terrain : erreur de lecture de la largeur\n");
			exit(1);
		case ERREUR_LECTURE_HAUTEUR:
			printf("Erreur lecture du terrain : erreur de lecture de la hauteur\n");
			exit(1);
		case ERREUR_LARGEUR_INCORRECTE:
			printf("Erreur lecture du terrain : largeur incorrecte\n");
			exit(1);
		case ERREUR_HAUTEUR_INCORRECTE:
			printf("Erreur lecture du terrain : hauteur incorrecte\n");
			exit(1);
		case ERREUR_CARACTERE_INCORRECTE:
			printf("Erreur lecture du terrain : caractère incorrect\n");
			exit(1);
		case ERREUR_LIGNE_TROP_LONGUE:
			printf("Erreur lecture du terrain : ligne trop longue\n");
			exit(1);
		case ERREUR_LIGNE_TROP_COURTE:
			printf("Erreur lecture du terrain : ligne trop courte\n");
			exit(1);
		case ERREUR_LIGNES_MANQUANTES:
			printf("Erreur lecture du terrain : lignes manquantes\n");
			exit(1);
		case ERREUR_POSITION_ROBOT_MANQUANTE:
			printf("Erreur lecture du terrain : position initiale du robot manquante\n");
			exit(1);
		case ERREUR_LONGUEUR_LIGNE:
			printf("Erreur de ligne : La longueur de la ligne n'est pas correcte");
			exit(1);
	}
}

void affichage_position_programme(erreur_programme e) {
	int i;
	printf("Ligne %d, colonne %d :\n", e.num_ligne, e.num_colonne);
	printf("%s\n", e.ligne);
	/* Impression de e.num_colonne-1 espaces */
	for(i = 1; i < e.num_colonne; i++) {
		printf(" ");
	}
	/* Impression d'un curseur de position */
	printf("^\n");
}

void gestion_erreur_programme(erreur_programme e) {
	switch(e.type_err) {
		case OK_PROGRAMME:
			break;
		case ERREUR_FICHIER_PROGRAMME:
			printf("Erreur lecture du programme : erreur d'ouverture du fichier\n");
			exit(2);
		case ERREUR_BLOC_NON_FERME:
			printf("Erreur lecture du programme : bloc non fermé\n");
			exit(2);
		case ERREUR_FERMETURE_BLOC_EXCEDENTAIRE:
			printf("Erreur lecture du programme : fermeture de bloc excédentaire\n");
			affichage_position_programme(e);
			exit(2);
		case ERREUR_COMMANDE_INCORRECTE:
			printf("Erreur lecture du programme : commande incorrecte\n");
			affichage_position_programme(e);
			exit(2);
	}
}

int etat_attendu(Robot r, int ax, int ay, char ao) {
	int rx, ry;
	char ro;

	rx = abscisse(r);
	ry = ordonnee(r);

	switch(orient(r)) {
		case Nord: ro = 'N'; break;
		case Sud: ro = 'S'; break;
		case Est: ro = 'E'; break;
		case Ouest: ro = 'O'; break;
	}

	if((rx = ax) && (ry = ay) && (ro == ao)) {
		printf("Ok.\n");
		return 0;
	}
	
	else {
		printf("Position attendue : (%d, %d), %c\n", ax, ay, ao);
		printf("Position obtenue : (%d, %d), %c\n", rx, ry, ro);
		printf("Test echoue.\n");
		return 1;
	}
}

int main(int argc, char **argv) {
	FILE *ftest;

	char nom_fenvt[LMAX], nom_fprog[LMAX];

	Environnement envt;
	Programme prog;
	Erreur_terrain errt;
	erreur_programme errp;

	int nbstepmax, ax, ay, nbstep;
	char cevent, ao;

	etat_inter etat;
	resultat_inter res;

	if(argc < 2) {
		printf("Usage: %s <fichier test>\n", argv[0]);
		return 1;
	}

	ftest = fopen(argv[1], "r");

	fscanf(ftest, "%s\n", nom_fenvt);
	errt = initialise_environnement(&envt, nom_fenvt);
	gestion_erreur_terrain(errt);

	fscanf(ftest, "%s\n", nom_fprog);
	errp = lire_programme(&prog, nom_fprog);
	gestion_erreur_programme(errp);

	fscanf(ftest, "%d\n", &nbstepmax);

	fscanf(ftest, "%c\n", &cevent);
	if((cevent == 'N') || (cevent == 'F')) {
		fscanf(ftest, "%d %d\n", &ax, &ay);
		fscanf(ftest, "%c", &ao);
	}

	init_etat(&etat);
	res = OK_ROBOT;
	for(nbstep = 0; (nbstep < nbstepmax) && (res == OK_ROBOT); nbstep++) {
		res = exec_pas(&prog, &envt, &etat);
		afficher_envt(&envt);
	}

	switch(res) {
		case OK_ROBOT:
			printf("Robot sur une case libre, programme non termine\n");
			if(cevent == 'N') {
				return etat_attendu(envt.r, ax, ay, ao);
			} else {
				printf("Test echoue, etat attendu = %c\n", cevent);
				return 1;
			}
		case SORTIE_ROBOT:
			printf("Le robot est sorti:-)\n");
			if(cevent == 'S') {
				printf("Ok.\n");
				return 0;
			} else {
				printf("test echoue, etat attendu = %c\n", cevent);
				return 1;
			}
		case ARRET_ROBOT:
			printf("Robot sur une case libre, programme termine :-/\n");
			if(cevent == 'F') {
				return etat_attendu(envt.r, ax, ay, ao);
			} else {
				printf("Test echoue, etat attendu = %c\n", cevent);
				return 1;
			}
		case PLOUF_ROBOT:
			printf("Le robot est tombe dans l'eau :-(\n");
			if(cevent == 'P') {
				printf("Ok.\n");
				return 0;
			} else {
				printf("Test echoue, etat attendu = %c\n", cevent);
				return 1;
			}
		case CRASH_ROBOT:
			printf("Le robot s'est ecrase sur un rocher X-(\n");
			if(cevent == 'O') {
				printf("Ok.\n");
				return 0;
			} else {
				printf("Test echoue, etat attendu = %c\n", cevent);
				return 1;
			}
		case ERREUR_PILE_VIDE:
			printf("ERREUR : pile vide\n");
			return 1;
		case ERREUR_ADRESSAGE:
			printf("ERREUR : erreur d'adressage\n");
			return 1;
		case ERREUR_DIVISION_PAR_ZERO:
			printf("ERREUR : division par 0\n");
			return 1;
	}
}
