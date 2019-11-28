#include <stdio.h>
#include <stdlib.h>

/*sur une ligne, un nom de fichier terrain ;
sur une ligne, un nom de fichier programme ;
sur une ligne, le nombre de pas maximum d'exécution ;
sur une ligne, un caractère e indiquant l'évènement attendu à la fin de l'exécution :
«N» si le robot est sur une position normale à l'intérieur du terrain,
«F» si le programme est terminé,
«S» si le robot est sorti du terrain,
«O» si le robot a rencontré un obstacle,
«P» si le robot est tombé dans l'eau ;*/
int test_file(FILE* f);