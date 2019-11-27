#include <stdio.h>
#include <stdlib.h>
#include <iostream.h>
#include <time.h>

#include "performance.h"

void performance(FILE* f_open,int L,int H,int d_obst,int nb_max_step,FILE* f_write){
    printf("Pas encore faite...");
}

int main(int argc,char* argv){
    if(argc != 9){
        printf("Utilisation demandée : curiosity-perf fichier_programme N L H d graine nb_step_max fichier_res")
        return 1;
    }
    int N,L,H,d_obst,nb_max_step;
    FILE* f_open = fopen(argv[1],"r");
    if(f_open == NULL){
        printf("Erreur sur le premier argument, cela doit etre un fichier valide");
        return 2;
    }
    FILE* f_write = fopen(argv[8],"w");
    if(f_write == NULL){
        printf("Erreur sur le dernier argument, cela doit etre un fichier valide");
        return 3;
    }
    N = argv[2];
    L = argv[3];
    H = argv[4];
    d_obst = argv[5];
    nb_max_step = argv[6];
    performance(f_open,L,H,d_obst,nb_max_step,f_write);
}