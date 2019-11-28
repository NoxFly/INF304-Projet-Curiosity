#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "generation_terrains.h"
#include "terrain.h"

int nb_cases_occupees(Terrain T) {
	int occupee = 0;
	int x, y;
	for(x = 0; x < largeur(T); x++) {
		for(y = 0; y < hauteur(T); y++) {
			if(T.tab[x][y] != LIBRE) occupee++;
		}
	}
	return occupee;
}

// Test de generation aléatoire de terrains
// Le programme génère n terrains de largeur et hauteur fixes
// avec largeur et hauteur impaires et inférieures a dimension_x de terrain.h
// avec densité d'obstacle dObst
// autre que la case centrale soit occupee
// l'appel du programme se fait avec 5 arguments :
// generation_terrains N largeur hauteur dObstacle fichier_res
// la sortie se fait dans le fichier resultat

int main(int argc, char **argv){
  int N, l, h;
  float dObst;
  FILE* resFile;

	if(argc < 6) {
		printf("Usage: %s <N> <largeur> <hauteur> <densite_obstacle> <fichier_res> \n", argv[0]);
		return 1;
	}

	N = strtol(argv[1], NULL, 10);
	l = strtol(argv[2], NULL, 10);
	h = strtol(argv[3], NULL, 10);
	dObst = strtof(argv[4], NULL);

	// test de l et h
	if(l > DIM_MAX || l % 2 == 0) {
		printf("Largeur incorrecte : doit être impaire et <= %d\n", DIM_MAX);
		return 1;
	}

	if(h > DIM_MAX || h % 2 == 0) {
		printf("Hauteur incorrecte : doit être impaire et <= %d\n", DIM_MAX);
		return 1;
	}

	if((dObst > 1) || (dObst < 0)) {
		printf("Densité incorrecte : doit être comprise entre 0 et 1\n");
		return 1;
	}

	// Ouverture du fichier résultat
	resFile = fopen(argv[5], "w");
	// Écriture du nombre de terrains
	fprintf(resFile, "%d\n", N);

	// Génération aléatoire des terrains
	int terrrain_faux = 0;
	int densitee_moyenne = 0;
	for(int i = 0; i < N; i++) {
		printf("Génération d'un terrain aléatoire...\n");

		Terrain T;
		generation_aleatoire(&T, l, h, dObst);
		while(!existe_chemin_vers_sortie(T)){
			generation_aleatoire(&T, l, h, dObst);
			terrrain_faux ++;
		}

    	printf("Terrain aléatoire numéro %d : \n",i+1);
		afficher_terrain(&T,(int)(l/2), (int)(h/2));
    	printf("\n");
		int compt = caracteristique_terrain(&T);
		int val_obst = dObst * 100;
		printf("Il y a %d d'obstacles dans ce terrain contre %d attendu\n",compt,val_obst);
		densitee_moyenne = densitee_moyenne + compt;


		ecrire_terrain(resFile, T, (int)(l / 2), (int)(h / 2));
		fprintf(resFile, "\n");
		fprintf(resFile,"%d\n",compt);
		fprintf(resFile, "\n");

		sleep(1);
	}
	float prop_terrain_faux = ((terrrain_faux*100.0)/N);
	fprintf(resFile,"%d\n",(int)densitee_moyenne/N);
	fprintf(resFile,"%f\n",prop_terrain_faux);
	// Écriture des terrains générés dans le fichier resFile
	// Écriture/Affichage des statistiques
	// fermeture des fichiers
	fclose(resFile);
	return 0;
}
