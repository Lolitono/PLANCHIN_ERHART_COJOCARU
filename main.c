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
//    FILE *file = fopen("sauvegarde_jeu.txt", "w");       // 3 lignes à décommenter pour initialiser le fichier de sauvegarde
//    fprintf(file,"0");
//    fclose(file);
    FILE *file = fopen("sauvegarde_jeu.txt", "r");  // ligne à commenter si aucun fichier de sauvegarde n'existe
    demarrer = menu(file);
    fclose(file);
    if (demarrer == 'D'){
        do {

            mode = demande_mode();
            missile = demande_difficulte();
            tableau_joueur = initialisation_tableau();
            tableau_ordi = initialisation_tableau_ordi();

            for (i = 0; i < NB_bateau; i++) {
                bateau[i] = initialisation_bateau(i);
            }

            for (i = 0; i < NB_bateau; i++) {
                bateau[i].touche = 0;
                bateau[i].H_V = rand() % 2; //0 = horizontal, 1 = vertical
                bateau[i].identification = 'A' + i;
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

        FILE *file = fopen("sauvegarde_jeu.txt", "r");
        if(file != NULL) {
            partie = load(file);
            fclose(file);
            partie_finie(partie);
            if(partie == 4 || partie == 5){
                return 0;
            }
            FILE *file = fopen("sauvegarde_jeu.txt", "w");
            fprintf(file,"0");
            fclose(file);
            rejouer = recommencer();
            if(rejouer == 'O'){
                do {
                    tableau_joueur = initialisation_tableau();
                    tableau_ordi = initialisation_tableau_ordi();
                    mode = demande_mode();
                    missile = demande_difficulte();
                    affichage_missile_depart(missile);

                    for (i = 0; i < NB_bateau; i++) {
                        bateau[i] = initialisation_bateau(i);
                    }

                    for (i = 0; i < NB_bateau; i++) {
                        bateau[i].touche = 0;
                        bateau[i].H_V = rand() % 2;
                        bateau[i].identification = 'A' + i;
                        bateau[i] = placement_bateau(tableau_ordi, bateau, i);
                        tableau_ordi = placement_grille_bateau(tableau_ordi, bateau, i);
                    }

                    printf("Voici le nombre de bateaux que l'ordinateur va placer aleatoirement:\n\n");
                    affichage_nb_bateau(bateau, NB_bateau);

                    //JEU
                    nombre_tour = 1;
                    partie = game(tableau_joueur,tableau_ordi, missile,bateau,NB_bateau,mode,nombre_tour,0);
                    partie_finie(partie);
                    if(partie == 4 || partie == 5){
                        return 0;
                    }
                    FILE *file = fopen("sauvegarde_jeu.txt", "w");
                    fprintf(file,"0");
                    fclose(file);
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

// Faire systeme de sauvegarde
// Demander a chaque tour si l'on veut continuer
// Si oui on continue
// Si non on sauvegarde et on quitte

// Choix du mode avant difficultés ???



//tir artillerie et bombe possible sur une case déja touche ou un O;
//Voir fin de partie




/*
 * tir_artillerie

for(i=0,i<nb_bateau,i++){
	for(j=1;j<11;j++){
		if(tableau.joueur[impact.ligne][j] == '_' && tableau.ordi[impact.ligne][j] == bateau[i].identification){
			tableau.joueur[impact.ligne][j] == 'X';
		} else if(tableau.joueur[impact.ligne][j] == '_' && tableau.ordi[impact.ligne][j] != bateau[i].identification){
			tableau.joueur[impact.ligne][j] == 'O';
		}
	for(j=1;j<11;j++){
		if(tableau.joueur[j][impact.colonne] == '_' && tableau.ordi[j][impact.colonne] == bateau[i].identification){
			tableau.joueur[j][impact.colonne] == 'X';
		} else if(tableau.joueur[j][impact.colonne] == '_' && tableau.ordi[j][impact.colonne] != bateau[i].identification){
			tableau.joueur[j][impact.colonne] == 'O';
		}
	}
}

tir_ bombe

for(i=0,i<nb_bateau,i++){
	for(j=-2;j<3;j++){
		if(tableau.joueur[impact.ligne][impact.colonne+j] == '_' && tableau.ordi[impact.ligne][impact.ligne +j] == bateau[i].identification){
			tableau.joueur[impact.ligne][impact.colonne+j] == 'X';
		} else if(tableau.joueur[impact.ligne][impact.colonne+j] == '_' && tableau.ordi[impact.ligne][impact.colonne+j] != bateau[i].identification){
			tableau.joueur[impact.ligne][impact.colonne+j] == 'O';
		}
	for(j=1;j<11;j++){
		if(tableau.joueur[impact.ligne + j][impact.colonne] == '_' && tableau.ordi[impact.ligne + j][impact.colonne] == bateau[i].identification){
			tableau.joueur[impact.ligne + j][impact.colonne] == 'X';
		} else if(tableau.joueur[impact.ligne + j][impact.colonne] == '_' && tableau.ordi[impact.ligne + j][impact.colonne] != bateau[i].identification){
			tableau.joueur[impact.ligne + j][impact.colonne] == 'O';
		}
	}
}

mettre es #include aprÃ¨s les structs pour tout bien mettre comme il faut
 */





//  Demande ou il veut tirer
//Impact demande_tir(Grid tableau_joueur){
//    char colonne;
//    int ligne;
//    do{
//        printf("Sur quelle colonne voulez-vous tirer (de A à J) ?\n");
//        scanf(" %c", &tir_actuel.colonne);
//        toupper(tir_actuel.colonne);
//        while(  'A' + tir_actuel.colonne < 0 || 'A' + tir_actuel.colonne > 9)
//        {
//            printf("Veuillez saisir une colonne valide (de A à J) \n");
//            scanf(" %c", &tir_actuel.colonne);
//            toupper(tir_actuel.colonne);
//        }

//        printf("Sur quelle ligne voulez-vous tirer (de 0 à 9) ?\n");
//        scanf(" %d", &tir_actuel.ligne);
//        while(tir_actuel.ligne < 0 || tir_actuel.ligne > 9)
//
//            printf("Veuillez saisir une ligne valide (de 0 à 9) \n");
//            scanf(" %d", &tir_actuel.ligne);
//        }
//        if (tableau_joueur[1+tir_actuel.ligne][1+tir_actuel.colonne] == 'O'||tableau_joueur[1+tir_actuel.ligne][1+tir_actuel.colonne] == 'X'){
//            verification = 1;
//        }
//
//    }while(verification == 1);
//
//    return tir_actuel;
//    }

//  A-t-il touché ?
//  Changement tableau et commentaire





// Faire l'initialisation des bateaux de l'IA et les placer dans le tableau (un autre peut être) = Fait

// Fonctions pour l'initialisation des bateaux, changer les lsymboles de chaque bateau pour les distinguer  Fait


// Mettre les coordonnées pour chaque bateau et mettre si c'est horizontal ou verticale pour voir plus facilement si le bateau est coulé  Fait
// commencer les tirs


/**
* Horizontal ou vertical?
 * Nombre aléatoire entre 0 et 1 (0= Horizontal et 1 = Vertical)
 * Si 0 alors
 *      Position sur l'abscisse : nombre aléatoire entre 1 et 10 - taille bateau;
 *      Position sur l'ordonnée : nombre aléatoire entre 1 et 10;
 *      Pour i =0 , i < taille bateau, i ++
 *          tableau [position sur l'abscisse][position sur l'ordonnée +i]='X'
 * Sinon
 *      Position sur l'abscisse : nombre aléatoire entre 1 et 10;
 *      Position sur l'ordonnée : nombre aléatoire entre 1 et 10 - taille bateau;
 *      Pour i =0 , i < taille bateau, i ++
 *          tableau [position sur l'abscisse + i][position sur l'ordonnée]='X'
 *
 *
 * Fonction Initialisation bateau :
 *      paramètres :
 *          Le tableau, nb_bateau,
 *
 *
*/