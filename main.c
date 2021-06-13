#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "jeu.h"

#define NB_bateau 5

int main() {
    int i,demarrer, partie,nombre_tour;
    Grid tableau_joueur;
    Grid tableau_ordi;
    Inventory missile;
    Boat bateau[NB_bateau];
    char rejouer,mode;

    srand(time(0));

    //FILE *file = fopen("sauvegarde_jeu.txt", "w");           //
    //fprintf(file,"0");                                       // 3 lignes à décommenter pour initialiser le fichier de sauvegarde
    //fclose(file);                                            //

    FILE *file = fopen("sauvegarde_jeu.txt", "r");  // Ligne à commenter si aucun fichier de sauvegarde n'existe et décommenter les 3 lignes ci-dessus pour en créer un

    demarrer = menu(file);
    fclose(file);

    if (demarrer == 'D'){
        do {
            mode = demande_mode();
            rejouer = demande_difficulte();
            missile = assignation_missile(rejouer);
            tableau_joueur = initialisation_tableau();
            tableau_ordi = initialisation_tableau_ordi();

            for (i = 0; i < NB_bateau; i++) {
                bateau[i] = initialisation_bateau(i,bateau);
                bateau[i] = placement_bateau(tableau_ordi, bateau, i);
                tableau_ordi = placement_grille_bateau(tableau_ordi, bateau, i);
            }

            nombre_tour=1;
            partie = game(tableau_joueur,tableau_ordi, missile,bateau,NB_bateau,mode,nombre_tour,0);
            partie_finie(partie);
            if(partie == 4 || partie == 5){
                return 0;           // On arrête le programme si l'utilisateur sauvegarde la partie ou quitte une partie pour ne pas écraser la sauvegarde
            }
            rejouer = recommencer();

        }while(rejouer == 'O');

        return 0;                   // On arrête le programme si l'utilisateur ne veut pas recommencer une nouvelle partie

    } else if (demarrer == 'C'){

        FILE *file = fopen("sauvegarde_jeu.txt", "r");       // On ouvre le fichier en lecture seule
        if(file != NULL) {                                                  // On vérifie qu'il n'y a pas de problèmes avec le ficher
            partie = load(file);
            partie_finie(partie);
            if(partie == 4 || partie == 5){                                 // On arrête le programme si l'utilisateur sauvegarde la partie ou quitte une partie pour ne pas écraser la sauvegarde
                return 0;
            }
            FILE *file = fopen("sauvegarde_jeu.txt", "w");   // On efface la sauvegarde si on a fini une partie chargée
            fprintf(file,"0");
            fclose(file);

            rejouer = recommencer();
            if(rejouer == 'O'){
                do {
                    mode = demande_mode();
                    rejouer = demande_difficulte();
                    missile = assignation_missile(rejouer);
                    tableau_joueur = initialisation_tableau();
                    tableau_ordi = initialisation_tableau_ordi();

                    for (i = 0; i < NB_bateau; i++) {
                        bateau[i] = initialisation_bateau(i,bateau);
                        bateau[i] = placement_bateau(tableau_ordi, bateau, i);
                        tableau_ordi = placement_grille_bateau(tableau_ordi, bateau, i);
                    }

                    affichage_missile_depart(missile);
                    printf("Voici le nombre de bateaux que l'ordinateur va placer aleatoirement:\n\n");
                    affichage_nb_bateau(bateau, NB_bateau);

                    nombre_tour = 1;            // On est au premier tour
                    partie = game(tableau_joueur,tableau_ordi, missile,bateau,NB_bateau,mode,nombre_tour,0);
                    partie_finie(partie);
                    if(partie == 4 || partie == 5){
                        return 0;               // On arrête le programme si l'utilisateur sauvegarde la partie ou quitte une partie pour ne pas écraser la sauvegarde
                    }
                    rejouer = recommencer();
                }while(rejouer == '0');
            }
            return 0;                           // On arrête le programme si l'utilisateur ne veut pas recommencer une nouvelle partie
        } else {
            printf("Erreur de sauvegarde");
        }
    } else {
        return 0;                               // On arrête le programme si l'utilisateur veut quitter le jeu depuis le menu
    }
}