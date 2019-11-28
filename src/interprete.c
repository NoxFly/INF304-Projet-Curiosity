#include "../include/interprete.h"
#include "../include/type_pile.h"

#include <unistd.h>

/* Interprétation d'un programme dans un environnement */

/* Initialisation de l'état */
void init_etat(etat_inter *etat) {
	creer_pile(&(etat->stack));
	creer_pile(&(etat->sp));
	etat->pc = 0;
}

/* Pas d'exécution de l'interprète : exécute une commande, modifie
   l'environnement et l'état, renvoie l'état du robot */
resultat_inter exec_pas(Programme *prog, Environnement *envt, etat_inter *etat, int debug) {
	Commande c;
	resultat_deplacement res;

	if(etat->pc == prog->lg) {
		return ARRET_ROBOT;
	}

	if((etat->pc > prog->lg) || (etat->pc < 0)) {
		return ERREUR_ADRESSAGE;
	}

	// Commande courante
	c = prog->tab[etat->pc];
	sleep(debug?1:0);
	switch(c.cmd) {
		case Avancer:
		printf("Le robot avance\n");
			res = avancer_envt(envt);
			switch(res) {
				case OK_DEPL:
					etat->pc++;
					return OK_ROBOT;
				case PLOUF:  return PLOUF_ROBOT;
				case CRASH:  return CRASH_ROBOT;
				case SORTIE: return SORTIE_ROBOT;
			}
		case Gauche:
		printf("Le robot tourne a gauche\n");
			gauche_envt(envt);
			etat->pc++;
			return OK_ROBOT;
		case Droite:
		printf("Le robot va a droite\n");
			droite_envt(envt);
			etat->pc++;
			return OK_ROBOT;
		case Mesure:
		printf("Le robot effectue une meusure\n");
			if(est_vide(&(etat->stack))) {
				return ERREUR_PILE_VIDE;
			} else {
				int param, mes;
				param = sommet(&(etat->stack));
				depiler(&(etat->stack));
				mes = mesure_envt(envt, param);
				empiler(&(etat->stack), mes);
				etat->pc++;
				return OK_ROBOT;
			}
		case Marque:
			printf("Le robot vérifie une marque\n");
			// Non implémenté
			etat->pc++;
			return OK_ROBOT;
		case DebutBloc:
		printf("Le robot détècte le début d'un block\n");
			// Empiler le bloc (adresse de début de bloc) sur la pile
			empiler(&(etat->stack), etat->pc + 1);
			// Commande suivante : commande suivant la fin du bloc empilé
			etat->pc = c.aux + 1;
			printf("Le robot a empiler la commande\n");
			return OK_ROBOT;
		case FinBloc:
		printf("Le robot détècte la fin d'un block\n");
			if(est_vide(&(etat->sp))) {
				// Ne devrait pas arriver (prétraitement des blocs)
				return ERREUR_PILE_VIDE;
			} else {
				// Récupérer l'adresse de retour sur la pile sp
				int ret = sommet(&(etat->sp));
				depiler(&(etat->sp));
				etat->pc = ret;
				return OK_ROBOT;
			}
		case EmpilerNb:
			printf("Le robot empile un nombre\n");
			empiler(&(etat->stack), c.aux);
			etat->pc++;
			return OK_ROBOT;
		case ExecBloc:
		printf("Le robot éxécute le block de commande\n");
			if(est_vide(&(etat->stack))) {
				return ERREUR_PILE_VIDE;
			} else {
				int adrexec;
				// Récupérer l'adresse du bloc à exécuter sur la pile
				adrexec = sommet(&(etat->stack));
				depiler(&(etat->stack));
				// Empiler l'adresse de retour dans sp
				empiler(&(etat->sp), etat->pc + 1);
				etat->pc = adrexec;
				return OK_ROBOT;
			}
		case CondExec:
			printf("Le robot a détécter une condition d'execution\n");
			if(taille(&(etat->stack)) < 3) {
				return ERREUR_PILE_VIDE;
			} else {
				int cond, addr_v, addr_f, addrexec;
				// Dépiler l'adresse du bloc "sinon"
				addr_f = sommet(&(etat->stack));
				depiler(&(etat->stack));
				// Dépiler l'adesse du bloc "si"
				addr_v = sommet(&(etat->stack));
				depiler(&(etat->stack));
				// Dépiler la condition
				cond = sommet(&(etat->stack));
				depiler(&(etat->stack));
				if(cond != 0) {
					addrexec = addr_v;
				} else {
					addrexec = addr_f;
				}
				// Empiler l'adresse de retour dans sp
				empiler(&(etat->sp), etat->pc + 1);
				etat->pc = addrexec;
				return OK_ROBOT;
			}
		case Echange:
			printf("Le robot echange\n");
			if(taille(&(etat->stack)) < 2) {
				return ERREUR_PILE_VIDE;
			} else {
				int a, b;
				a = sommet(&(etat->stack));
				depiler(&(etat->stack));
				b = sommet(&(etat->stack));
				depiler(&(etat->stack));
				empiler(&(etat->stack), a);
				empiler(&(etat->stack), b);
				etat->pc++;
				return OK_ROBOT;
			}
		case Mult:
		printf("Le robot fait une multiplication\n");
			if(taille(&(etat->stack)) < 2) {
				return ERREUR_PILE_VIDE;
			} else {
				int a, b;
				a = sommet(&(etat->stack));
				depiler(&(etat->stack));
				b = sommet(&(etat->stack));
				depiler(&(etat->stack));
				empiler(&(etat->stack), b * a);
				etat->pc++;
				return OK_ROBOT;
			}
		case Add:
		printf("Le robot fait une addition\n");
			if(taille(&(etat->stack)) < 2) {
				return ERREUR_PILE_VIDE;
			} else {
				int a, b;
				a = sommet(&(etat->stack));
				depiler(&(etat->stack));
				b = sommet(&(etat->stack));
				depiler(&(etat->stack));
				empiler(&(etat->stack), b + a);
				etat->pc++;
				return OK_ROBOT;
			}
		case Div:
		printf("Le robot fait une division\n");
			if(taille(&(etat->stack)) < 2) {
				return ERREUR_PILE_VIDE;
			} else {
				int a, b;
				a = sommet(&(etat->stack));
				depiler(&(etat->stack));
				b = sommet(&(etat->stack));
				depiler(&(etat->stack));
				if(a == 0) {
					return ERREUR_DIVISION_PAR_ZERO;
				} else {
					empiler(&(etat->stack), b / a);
					etat->pc++;
					return OK_ROBOT;
				}
			}
		case Sub:
		printf("Le robot fait une soustraction\n");
			if(taille(&(etat->stack)) < 2) {
				return ERREUR_PILE_VIDE;
			} else {
				int a, b;
				a = sommet(&(etat->stack));
				depiler(&(etat->stack));
				b = sommet(&(etat->stack));
				depiler(&(etat->stack));
				empiler(&(etat->stack), b - a);
				etat->pc++;
				return OK_ROBOT;
			}
		case Rotation:
			printf("Le robot fait une rotation\n");
			if(taille(&(etat->stack)) < 2) {
				return ERREUR_PILE_VIDE;
			} else {
				int n; // Nombre d'éléments à décaler
				int p; // Pas de décalage
				p = sommet(&(etat->stack));
				depiler(&(etat->stack));
				n = sommet(&(etat->stack));
				depiler(&(etat->stack));
				if(taille(&(etat->stack)) < n) {
					return ERREUR_PILE_VIDE;
				} else {
					int a[n];
					int i;
					// Dépiler les éléments à décaler
					for(i = 0; i < n; i++) {
						a[i] = sommet(&(etat->stack));
						depiler(&(etat->stack));
					}
					// Empiler avec le décalage
					// On veut empiler l'élément A_n-p en premier. Il est rangé à l'indice
					// n-p-1 dans le tableau (d'où la boucle de 1 à n)
					for(i = 1; i <= n; i++) {
						int j = (n - p) - i;
						j = (j < 0) ? (n + j) : j;
						empiler(&(etat->stack), a[j]);
					}
					etat->pc++;
					return OK_ROBOT;
				}
			}
		case Clone:
			printf("Le robot clone\n");
			if(est_vide(&(etat->stack))) {
				return ERREUR_PILE_VIDE;
			} else {
				int a = sommet(&(etat->stack));
				empiler(&(etat->stack), a);
				etat->pc++;
				return OK_ROBOT;
			}
		case Boucle:
			printf("Le robot boucle\n");
			if(taille(&(etat->stack)) < 2) {
				return ERREUR_PILE_VIDE;
			} else {
				int n, addrexec;
				// Dépiler n
				n = sommet(&(etat->stack));
				depiler(&(etat->stack));
				if(n > 0) {
					// Récupérer l'adresse du bloc à exécuter
					addrexec = sommet(&(etat->stack));
					// Empiler n-1
					empiler(&(etat->stack), n - 1);
					// Empiler l'adresse de retour dans sp
					empiler(&(etat->sp), etat->pc);
					etat->pc = addrexec;
				} else {
					// Dépiler l'adresse du bloc
					depiler(&(etat->stack));
					etat->pc++;
				}
				return OK_ROBOT;
			}
		case Ignore:
			printf("Le robot ignore\n");
			if(est_vide(&(etat->stack))) {
				return ERREUR_PILE_VIDE;
			} else {
				depiler(&(etat->stack));
				etat->pc++;
				return OK_ROBOT;
			}
	}

	return OK_ROBOT;
}
