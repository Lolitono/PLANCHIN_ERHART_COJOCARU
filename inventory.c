#include <stdio.h>
#include<ctype.h>
#include "inventory.h"


Inventory assignation_missile(char difficulte){
    Inventory inventaire;

    if(difficulte == 'F'){ // Si la difficulté choisie est Facile
        printf("\n===========Difficulte Facile===========\n\n"
               "Voici les missiles dont vous disposez:\n\n");
        inventaire.artillerie = 3;
        inventaire.tactique = 8;
        inventaire.bombe = 4;
        inventaire.simple = 18;
    } else if (difficulte == 'M'){ // Si la difficulté choisie est Moyenne
        printf("\n==========Difficulte Moyenne==========\n\n"
               "Voici les missiles dont vous disposez:\n\n");
        inventaire.artillerie = 2;
        inventaire.tactique = 6;
        inventaire.bombe = 2;
        inventaire.simple = 16;
    } else { // Si la difficulté choisie est Difficile
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


char demande_missile(Inventory missile){  // Quel missile veut-il choisir?
    char tir_actuel;
    int verification;
    do{
        printf("\nAvec quel missile voulez_vous tirer (A/T/B/S) ?\n");
        scanf(" %c", &tir_actuel);
        tir_actuel = toupper(tir_actuel); // On remplace les lettres écrites en minuscule par leurs majuscules respectives
        while(  tir_actuel != 'A' && tir_actuel != 'T' && tir_actuel != 'B' && tir_actuel != 'S' ) // Tant que l'utilisateur aura écrit une lettre différente de "a","t","b","s"
        {
            printf("Veuillez saisir une munition valide (A/T/B/S).\n");
            scanf(" %c", &tir_actuel);
            tir_actuel = toupper(tir_actuel); // On remplace les lettres écrites en minuscule par leurs majuscules respectives
        }
        verification = verification_missile(missile,tir_actuel);    // On vérfie si l'utilisateur a encore le missile qu'il a choisi

    }while(verification == 1); // Tant qu'il n'y a pas le missile voulu

    return tir_actuel;
}


int verification_missile(Inventory missile, char tir_actuel){
    if (tir_actuel=='A' && missile.artillerie==0){ // Si le missile choisi est un tir d'artillerie et qu'il n'en reste plus
        printf("Vous n'avez plus de missiles d'artillerie...\n");
        return 1;
    }
    if (tir_actuel=='T' && missile.tactique==0){ // Si le missile choisi est un tir tactique et qu'il n'en reste plus
        printf("Vous n'avez plus de missiles tactiques...\n");
        return 1;
    }
    if (tir_actuel=='B' && missile.bombe==0){ // Si le missile choisi est une bombe et qu'il n'en reste plus
        printf("Vous n'avez plus de bombes...\n");
        return 1;
    }
    if (tir_actuel=='S' && missile.simple==0){ // Si le missile choisi est un tir simple et qu'il n'en reste plus
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
                bateau[i].touche++;                                                                     // On ajoute 1 au nombre de fois que le bateau a été touché
                tableau_ordi->grille[point_impact.ligne + 1][j] = ' ';                                  // On retire la partie du bateau touchée sur le tableau de l'ordinateur
                if (mode == 'B') {
                    printf("Un bateau a ete touche en %c%d.\n", 'A' + j - 1, point_impact.ligne);   // On indique à l'utilisateur la position où le missile a touché un bateau si on est en mode "Blind"
                }
            }
        }
        if (tableau_joueur->grille[point_impact.ligne + 1][j] == '_') {     // Si aucun bateau se trouve sur la position
            tableau_joueur->grille[point_impact.ligne + 1][j] = 'O';        // On le marque d'un 'O'
        }
    }
    for (j = 1; j < 11; j++) {
        for (i = 0; i < NB_bateau; i++) {
            if (tableau_joueur->grille[j][point_impact.colonne + 1] == '_' && tableau_ordi->grille[j][point_impact.colonne + 1] == bateau[i].identification) {    // Si un bateau se trouve sur la ligne de l'impact
                tableau_joueur->grille[j][point_impact.colonne + 1] = 'X';  // Il sera marqué d'une 'X' sur le tableau joueur
                bateau[i].touche++;                                         // On ajoute 1 au nombre de fois que le bateau a été touché
                tableau_ordi->grille[j][1 + point_impact.colonne] = ' ';    // On retire la partie du bateau touchée sur le tableau de l'ordinateur
                if (mode == 'B') {
                    printf("Un bateau a ete touche en %c%d.\n", 'A' + point_impact.colonne, j - 1); // On indique à l'utilisateur la position où le missile a touché un bateau si on est en mode "Blind"
                }
            }
        }
        if (tableau_joueur->grille[j][point_impact.colonne + 1] == '_' ) {  // Si aucun bateau ne se trouve sur la position
            tableau_joueur->grille[j][point_impact.colonne + 1] = 'O';      // On le marque d'un 'O'
        }
    }
}


void tir_bombe(Grid *tableau_joueur, Grid *tableau_ordi,Impact point_impact,int NB_bateau,Boat bateau[],char mode) {
    int i, j, k;

    for (j = -1; j < 4; j++) {
        for (i = 0; i < NB_bateau; i++) {
            if (tableau_joueur->grille[point_impact.ligne + 1][point_impact.colonne+j] == '_' && tableau_ordi->grille[point_impact.ligne + 1][point_impact.colonne+j] == bateau[i].identification && point_impact.colonne + j > 0 && point_impact.colonne + j <= 11) {
                //Si un bateau se trouve sur le point d'impact, 2 cases à gauche du point d'impact ou 2 cases à droite et que le tir soit compris dans le tableau joueur
                tableau_joueur->grille[point_impact.ligne + 1][point_impact.colonne+j] = 'X';   // Le bateau sera marqué d'une 'X' sur le tableau joueur
                bateau[i].touche++;                                                             // On ajoute 1 au nombre de fois que le bateau a été touché
                tableau_ordi->grille[point_impact.ligne +1][point_impact.colonne+j] = ' ';      // On retire la partie du bateau touchée sur le tableau de l'ordinateur
                if (mode == 'B') {
                    printf("Un bateau a ete touche en %c%d.\n", 'A' + (point_impact.colonne+j-1),point_impact.ligne); // On indique à l'utilisateur la position où le missile a touché un bateau si on est en mode "Blind"
                }
            }
        }
        if (tableau_joueur->grille[point_impact.ligne + 1][point_impact.colonne+j] == '_') {    // Si aucun bateau ne se trouve sur la position
            tableau_joueur->grille[point_impact.ligne + 1][point_impact.colonne+j] = 'O';       // On le marque d'un 'O'
        }
    }

    for (j = -1; j < 4; j++) {
        for (i = 0; i < NB_bateau; i++) {
            if (tableau_joueur->grille[point_impact.ligne+j][point_impact.colonne + 1] == '_' && tableau_ordi->grille[point_impact.ligne+j][point_impact.colonne + 1] == bateau[i].identification && point_impact.ligne + j > 0 && point_impact.ligne + j <= 11) {
                //Si un bateau se trouve sur le point d'impact, 2 cases en haut du point d'impact ou 2 cases en bas et que le tir soit compris dans le tableau joueur
                tableau_joueur->grille[point_impact.ligne+j][point_impact.colonne + 1] = 'X';   // Le bateau sera marqué d'une 'X' sur le tableau joueur
                bateau[i].touche++;                                                             // On ajoute 1 au nombre de fois que le bateau a été touché
                tableau_ordi->grille[point_impact.ligne + j][1 + point_impact.colonne] = ' ';   // On retire la partie du bateau touchée sur le tableau de l'ordinateur
                if (mode == 'B') {
                    printf("Un bateau a ete touche en %c%d.\n", 'A' + point_impact.colonne,point_impact.ligne+j-1);// On indique à l'utilisateur la position où le missile a touché un bateau si on est en mode "Blind"
                }
            }
        }
        if (tableau_joueur->grille[point_impact.ligne+j][point_impact.colonne + 1] == '_' ) {   // Si aucun bateau ne se trouve sur la position
            tableau_joueur->grille[point_impact.ligne+j][point_impact.colonne + 1] = 'O';       // On le marque d'un 'O'
        }
    }

    for (j = 0; j < 3; j=j+2) {
        for(k=0; k<3;k=k+2) {
            for (i = 0; i < NB_bateau; i++) {
                if (tableau_joueur->grille[point_impact.ligne + j][point_impact.colonne + k] == '_' &&
                    tableau_ordi->grille[point_impact.ligne + j][point_impact.colonne + k] == bateau[i].identification && point_impact.ligne + j > 0 && point_impact.ligne + j <= 11) {
                    //Si un bateau se trouve sur les diagonales en périphérie de la case et que le tir est compris dans le tableau joueur
                    tableau_joueur->grille[point_impact.ligne + j][point_impact.colonne + k] = 'X'; // Le bateau sera marqué d'une 'X' sur le tableau joueur
                    bateau[i].touche++;                                                             // On ajoute 1 au nombre de fois que le bateau a été touché
                    tableau_ordi->grille[point_impact.ligne + j][point_impact.colonne + k] = ' ';   // On retire la partie du bateau touchée sur le tableau de l'ordinateur
                    if (mode == 'B') {
                        printf("Un bateau a ete touche en %c%d.\n", 'A' + point_impact.colonne + k - 1,point_impact.ligne + j - 1);// On indique à l'utilisateur la position où le missile a touché un bateau si on est en mode "Blind"
                    }
                }
            }
            if (tableau_joueur->grille[point_impact.ligne + j][point_impact.colonne + k] == '_') {  // Si aucun bateau ne se trouve sur la position
                tableau_joueur->grille[point_impact.ligne + j][point_impact.colonne + k] = 'O';     // On le marque d'un 'O'
            }
        }
    }
}


void tir_simple(Grid *tableau_joueur, Grid *tableau_ordi, Impact point_impact,char mode,int NB_bateau,Boat bateau[]){

    int i;
    for (i = 0; i < NB_bateau; i++) {
        if(tableau_ordi->grille[1+point_impact.ligne][1+point_impact.colonne] == bateau[i].identification){ //Si le missile touche un bateau
            tableau_joueur->grille[1+point_impact.ligne][1+point_impact.colonne] = 'X';     // L'impact sera marqué d'une 'X' sur le tableau joueur
            bateau[i].touche++;                                                             // On ajoute 1 au nombre de fois que le bateau a été touché
            tableau_ordi->grille[1 + point_impact.ligne][1 + point_impact.colonne] = ' ';   // On retire la partie du bateau touchée sur le tableau de l'ordinateur
            if (mode == 'B') {
                printf("Un bateau a ete touche en %c%d.\n", 'A' + point_impact.colonne, point_impact.ligne);    // On indique à l'utilisateur la position où le missile a touché un bateau si on est en mode "Blind"
            }
        }
    }
    if (tableau_joueur->grille[point_impact.ligne + 1][point_impact.colonne + 1] == '_') {  // Si aucun bateau ne se trouve sur la position
        tableau_joueur->grille[point_impact.ligne + 1][point_impact.colonne + 1] = 'O';     // On le marque d'un 'O'
    }
}


void tir_tactique(Grid *tableau_joueur, Grid *tableau_ordi, Impact point_impact,int NB_bateau, Boat bateau[], char mode){
    int i,j,k;



    for (i = 0; i < NB_bateau; i++) {
        if(tableau_ordi->grille[1+point_impact.ligne][1+point_impact.colonne] == bateau[i].identification){ //Si le missile tombe sur un bateau
            for (k = 1; k < 11; k++) {
                for (j = 1; j < 11; j++) {
                    if (tableau_ordi->grille[k][j] == bateau[i].identification) {   //On regarde où le bateau est positionné
                        tableau_joueur->grille[k][j] = 'X'; // Le bateau en entier sera marqué d'une 'X' sur le tableau joueur
                        tableau_ordi->grille[k][j] = ' ';   // et il sera effacé du tableau de l'ordinateur
                        if (mode == 'B') {
                            printf("Un bateau a ete touche en %c%d.\n", 'A' + j - 1, k - 1);    // On indique à l'utilisateur la position où le missile a touché un bateau si on est en mode "Blind"
                        }
                    }
                }
            }
            bateau[i].touche = bateau[i].taille_bateau; // On déclare le bateau comme coulé
        }
    }
    if (tableau_joueur->grille[point_impact.ligne + 1][point_impact.colonne + 1] == '_') {  // Si aucun bateau ne se trouve sur la position
        tableau_joueur->grille[point_impact.ligne + 1][point_impact.colonne + 1] = 'O';     // On le marque d'un 'O'
    }
}