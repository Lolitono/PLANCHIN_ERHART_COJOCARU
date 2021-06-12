#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "jeu.h"

#define NB_bateau 5

// denis.dubaj@utbm.fr
int main() {
    int i,demarrer, partie,nombre_tour;
    Grid tableau_joueur;
    Grid tableau_ordi;
    Inventory missile;
    Boat bateau[NB_bateau];
    char rejouer,mode;

    srand(time(0));

    // FILE *file = fopen("sauvegarde_jeu.txt", "w");       /*
    //  fprintf(file,"0");                                    3 lignes à décommenter pour initialiser le fichier de sauvegarde
    // fclose(file);                                         */

    FILE *file = fopen("sauvegarde_jeu.txt", "r");  // ligne à commenter si aucun fichier de sauvegarde n'existe

    demarrer = menu(file);
    fclose(file);

    if (demarrer == 'D'){
        do {

            mode = demande_mode();                          // On demande le mode de jeu auquelle l'utilisateur veut jouer
            rejouer = demande_difficulte();                 // On demande la difficulté
            missile = assignation_missile(rejouer);         // On assigne le nombre de missile en fonction de la difficulté
            tableau_joueur = initialisation_tableau();      // On initialise le tableau joueur
            tableau_ordi = initialisation_tableau_ordi();   // On initialise le tableau ordi

            for (i = 0; i < NB_bateau; i++) {
                bateau[i] = initialisation_bateau(i);
                bateau[i].touche = 0;                                           // aucun bateau n'est touché initialement
                bateau[i].H_V = rand() % 2;                                     //0 = horizontal, 1 = vertical
                bateau[i].identification = 'A' + i;                             //lettre permettant d'identifier chaque bateau
                bateau[i] = placement_bateau(tableau_ordi, bateau, i);
                tableau_ordi = placement_grille_bateau(tableau_ordi, bateau, i);
            }

            //JEU
            nombre_tour=1;
            partie = game(tableau_joueur,tableau_ordi, missile,bateau,NB_bateau,mode,nombre_tour,0);
            partie_finie(partie);
            if(partie == 4 || partie == 5){
                return 0;
            }
            rejouer = recommencer();

        }while(rejouer == 'O');

        return 0;

    } else if (demarrer == 'C'){

        FILE *file = fopen("sauvegarde_jeu.txt", "r"); //on ouvre le fichier en lecture seule
        if(file != NULL) { //on vérifie qu'il n'y a pas de problèmes avec le ficher
            partie = load(file);
            partie_finie(partie);
            if(partie == 4 || partie == 5){ //si on veut sauvegarder la partie
                return 0;
            }
            FILE *file = fopen("sauvegarde_jeu.txt", "w");
            fprintf(file,"0");
            fclose(file);
            rejouer = recommencer();
            if(rejouer == 'O'){
                do {
                    mode = demande_mode();                          // On demande le mode de jeu auquelle l'utilisateur veut jouer
                    rejouer = demande_difficulte();                 // On demande la difficulté
                    missile = assignation_missile(rejouer);         // On assigne le nombre de missile en fonction de la difficulté
                    tableau_joueur = initialisation_tableau();      // On initialise le tableau joueur
                    tableau_ordi = initialisation_tableau_ordi();   // On initialise le tableau ordi

                    for (i = 0; i < NB_bateau; i++) {
                        bateau[i] = initialisation_bateau(i);
                        bateau[i].touche = 0;                                           // initialement aucun bateau n'est touché
                        bateau[i].H_V = rand() % 2;                                     //0 = horizontal, 1 = vertical
                        bateau[i].identification = 'A' + i;                             //lettre permettant d'identifier chaque bateau
                        bateau[i] = placement_bateau(tableau_ordi, bateau, i);
                        tableau_ordi = placement_grille_bateau(tableau_ordi, bateau, i);
                    }

                    affichage_missile_depart(missile);
                    printf("Voici le nombre de bateaux que l'ordinateur va placer aleatoirement:\n\n");
                    affichage_nb_bateau(bateau, NB_bateau);

                    //JEU
                    nombre_tour = 1; //on est au premier tour
                    partie = game(tableau_joueur,tableau_ordi, missile,bateau,NB_bateau,mode,nombre_tour,0);
                    partie_finie(partie);
                    if(partie == 4 || partie == 5){
                        return 0;
                    }
                    rejouer = recommencer();
                }while(rejouer == '0');
            }
            return 0;
        } else {
            printf("Erreur de sauvegarde");
        }
    } else {
        return 0;
    }
}
