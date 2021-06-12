#include <stdio.h>
#include<ctype.h>
#include "inventory.h"


Inventory assignation_missile(char difficulte){
    Inventory inventaire;

    if(difficulte == 'F'){ // Si la difficulté choisie est facile
        printf("\n===========Difficulte Facile===========\n\n"
               "Voici les missiles dont vous disposez:\n\n");
        inventaire.artillerie = 3;
        inventaire.tactique = 8;
        inventaire.bombe = 4;
        inventaire.simple = 18;
    } else if (difficulte == 'M'){ // Si la difficulté choisie est moyenne
        printf("\n==========Difficulte Moyenne==========\n\n"
               "Voici les missiles dont vous disposez:\n\n");
        inventaire.artillerie = 2;
        inventaire.tactique = 6;
        inventaire.bombe = 2;
        inventaire.simple = 16;
    } else {
        printf("\n=========Difficulte Difficile=========\n\n"
               "Voici les missiles dont vous disposez:\n\n");
        inventaire.artillerie = 2;
        inventaire.tactique = 4;
        inventaire.bombe = 1;
        inventaire.simple = 14;
    }
    return inventaire;
}


void affichage_missile_depart(Inventory missile){

    printf("\n-Missiles d'artilleries : %d  (Le missile d'artillerie inflige des degats a tout les bateaux se situant sur la ligne et la colonne du point d'impact).\n",missile.artillerie);
    printf("-Missiles tactiques : %d  (Si le missile tactique touche un bateau, ce dernier est immediatement coule).\n",missile.tactique);
    printf("-Bombes : %d (La bombe inflige des degats sur et autour de son point d'impact, sur un rayon de 2 cases horizontalement et verticalement et 1 case diagonalement).\n",missile.bombe);
    printf("-Missiles simples : %d (Le missile simple inflige des degats sur le point d'impact uniquement).\n",missile.simple);
    printf("\n=======================================\n\n");
}


void affichage_missile(Inventory missile){
    printf("\nVoici les munitions qu'il vous reste : \n");
    printf("\n-Missiles d'artilleries : %d\n",missile.artillerie);
    printf("-Missiles tactiques : %d\n",missile.tactique);
    printf("-Bombes : %d\n",missile.bombe);
    printf("-Missiles simples : %d\n\n",missile.simple);
}


char demande_missile(Inventory missile){  //  Quel missile veut-il choisir
    char tir_actuel;
    int verification;
    do{
        printf("\nAvec quel missile voulez_vous tirer (A/T/B/S) ?\n");
        scanf(" %c", &tir_actuel);
        tir_actuel = toupper(tir_actuel);
        while(  tir_actuel != 'A' && tir_actuel != 'T' && tir_actuel != 'B' && tir_actuel != 'S' )
        {
            printf("Veuillez saisir une munition valide (A/T/B/S).\n");
            scanf(" %c", &tir_actuel);
            tir_actuel = toupper(tir_actuel);
        }
        verification = verification_missile(missile,tir_actuel);    // On vérfie si l'utilisateur a encore le missile qu'il a choisi

    }while(verification == 1);

    return tir_actuel;
}


int verification_missile(Inventory missile, char tir_actuel){
    if (tir_actuel=='A' && missile.artillerie==0){
        printf("Vous n'avez plus de missiles d'artillerie...\n");
        return 1;
    }
    if (tir_actuel=='T' && missile.tactique==0){
        printf("Vous n'avez plus de missiles tactiques...\n");
        return 1;
    }
    if (tir_actuel=='B' && missile.bombe==0){
        printf("Vous n'avez plus de bombes...\n");
        return 1;
    }
    if (tir_actuel=='S' && missile.simple==0){
        printf("Vous n'avez plus de missiles simples...\n");
        return 1;
    }
    return 0;
}


void tir_artillerie(Grid *tableau_joueur, Grid *tableau_ordi,Impact point_impact,int NB_bateau,Boat bateau[],char mode) {
    int i, j;
    for (j = 1; j < 11; j++) {
        for (i = 0; i < NB_bateau; i++) {
            if (tableau_joueur->grille[point_impact.ligne + 1][j] == '_' &&
                tableau_ordi->grille[point_impact.ligne + 1][j] == bateau[i].identification) {          // Si un bateau se trouve sur la colonne de l'impact
                tableau_joueur->grille[point_impact.ligne + 1][j] = 'X';                                // Il sera marqué sur le tableau joueur
                bateau[i].touche++;
                tableau_ordi->grille[point_impact.ligne + 1][j] = ' ';
                if (mode == 'B') {
                    printf("Un bateau a ete touche en %c%d.\n", 'A' + j - 1, point_impact.ligne);
                }
            }
        }
        if (tableau_joueur->grille[point_impact.ligne + 1][j] == '_') {
            tableau_joueur->grille[point_impact.ligne + 1][j] = 'O';
        }
    }
    for (j = 1; j < 11; j++) {
        for (i = 0; i < NB_bateau; i++) {
            if (tableau_joueur->grille[j][point_impact.colonne + 1] == '_' && tableau_ordi->grille[j][point_impact.colonne + 1] == bateau[i].identification) {    // Si un bateau se trouve sur la ligne de l'impact alors cela mettra qu'on l'a touché sur le tableau joueur
                tableau_joueur->grille[j][point_impact.colonne + 1] = 'X';                                  // Il sera marqué sur le tableau joueur
                bateau[i].touche++;
                tableau_ordi->grille[j][1 + point_impact.colonne] = ' ';
                if (mode == 'B') {
                    printf("Un bateau a ete touche en %c%d.\n", 'A' + point_impact.colonne, j - 1);
                }
            }
        }
        if (tableau_joueur->grille[j][point_impact.colonne + 1] == '_' ) {
            tableau_joueur->grille[j][point_impact.colonne + 1] = 'O';
        }
    }
}


void tir_bombe(Grid *tableau_joueur, Grid *tableau_ordi,Impact point_impact,int NB_bateau,Boat bateau[],char mode) {
    int i, j, k;

    for (j = -1; j < 4; j++) {
        for (i = 0; i < NB_bateau; i++) {
            if (tableau_joueur->grille[point_impact.ligne + 1][point_impact.colonne+j] == '_' && tableau_ordi->grille[point_impact.ligne + 1][point_impact.colonne+j] == bateau[i].identification && point_impact.colonne + j > 0 && point_impact.colonne + j <= 11) {
                tableau_joueur->grille[point_impact.ligne + 1][point_impact.colonne+j] = 'X';
                bateau[i].touche++;
                tableau_ordi->grille[point_impact.ligne +1][point_impact.colonne+j] = ' ';
                if (mode == 'B') {
                    printf("Un bateau a ete touche en %c%d.\n", 'A' + (point_impact.colonne+j-1),
                           point_impact.ligne);
                }
            }
        }
        if (tableau_joueur->grille[point_impact.ligne + 1][point_impact.colonne+j] == '_') {
            tableau_joueur->grille[point_impact.ligne + 1][point_impact.colonne+j] = 'O';
        }
    }

    for (j = -1; j < 4; j++) {
        for (i = 0; i < NB_bateau; i++) {
            if (tableau_joueur->grille[point_impact.ligne+j][point_impact.colonne + 1] == '_' && tableau_ordi->grille[point_impact.ligne+j][point_impact.colonne + 1] == bateau[i].identification && point_impact.ligne + j > 0 && point_impact.ligne + j <= 11) {
                tableau_joueur->grille[point_impact.ligne+j][point_impact.colonne + 1] = 'X';
                bateau[i].touche++;
                tableau_ordi->grille[point_impact.ligne + j][1 + point_impact.colonne] = ' ';
                if (mode == 'B') {
                    printf("Un bateau a ete touche en %c%d.\n", 'A' + point_impact.colonne,
                           point_impact.ligne+j-1);
                }
            }
        }
        if (tableau_joueur->grille[point_impact.ligne+j][point_impact.colonne + 1] == '_' ) {
            tableau_joueur->grille[point_impact.ligne+j][point_impact.colonne + 1] = 'O';
        }
    }

    for (j = 0; j < 3; j=j+2) {
        for(k=0; k<3;k=k+2) {
            for (i = 0; i < NB_bateau; i++) {
                if (tableau_joueur->grille[point_impact.ligne + j][point_impact.colonne + k] == '_' &&
                    tableau_ordi->grille[point_impact.ligne + j][point_impact.colonne + k] == bateau[i].identification && point_impact.ligne + j > 0 && point_impact.ligne + j <= 11) {
                    tableau_joueur->grille[point_impact.ligne + j][point_impact.colonne + k] = 'X';
                    bateau[i].touche++;
                    tableau_ordi->grille[point_impact.ligne + j][point_impact.colonne + k] = ' ';
                    if (mode == 'B') {
                        printf("Un bateau a ete touche en %c%d.\n", 'A' + point_impact.colonne + k - 1,
                               point_impact.ligne + j - 1);
                    }
                }
            }
            if (tableau_joueur->grille[point_impact.ligne + j][point_impact.colonne + k] == '_') {
                tableau_joueur->grille[point_impact.ligne + j][point_impact.colonne + k] = 'O';
            }
        }
    }
}


void tir_simple(Grid *tableau_joueur, Grid *tableau_ordi, Impact point_impact,char mode,int NB_bateau,Boat bateau[]){

    int i;
    for (i = 0; i < NB_bateau; i++) {
        if(tableau_ordi->grille[1+point_impact.ligne][1+point_impact.colonne] == bateau[i].identification){
            tableau_joueur->grille[1+point_impact.ligne][1+point_impact.colonne] = 'X';
            bateau[i].touche++;
            tableau_ordi->grille[1 + point_impact.ligne][1 + point_impact.colonne] = ' ';
            if (mode == 'B') {
                printf("Un bateau a ete touche en %c%d.\n", 'A' + point_impact.colonne, point_impact.ligne);
            }
        }
    }
    if (tableau_joueur->grille[point_impact.ligne + 1][point_impact.colonne + 1] == '_') {
        tableau_joueur->grille[point_impact.ligne + 1][point_impact.colonne + 1] = 'O';
    }
}


void tir_tactique(Grid *tableau_joueur, Grid *tableau_ordi, Impact point_impact,int NB_bateau, Boat bateau[], char mode){
    int i,j,k;



    for (i = 0; i < NB_bateau; i++) {
        if(tableau_ordi->grille[1+point_impact.ligne][1+point_impact.colonne] == bateau[i].identification){
            for (k = 1; k < 11; k++) {
                for (j = 1; j < 11; j++) {
                    if (tableau_ordi->grille[k][j] == bateau[i].identification) {
                        tableau_joueur->grille[k][j] = 'X';
                        tableau_ordi->grille[k][j] = ' ';
                        if (mode == 'B') {
                            printf("Un bateau a ete touche en %c%d.\n", 'A' + j - 1, k - 1);
                        }
                    }
                }
            }
            bateau[i].touche = bateau[i].taille_bateau;
        }
    }
    if (tableau_joueur->grille[point_impact.ligne + 1][point_impact.colonne + 1] == '_') {
        tableau_joueur->grille[point_impact.ligne + 1][point_impact.colonne + 1] = 'O';
    }
}