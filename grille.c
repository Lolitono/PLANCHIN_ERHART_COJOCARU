//
// Created by arnau on 27/05/2021.
//

#include <stdio.h>
#include<ctype.h>
#include "grille.h"
#include <stdlib.h>

Grid initialisation_tableau(){
    Grid tableau;
    tableau.hauteur=12;
    tableau.largeur=12;

    int i,j;

    for(i=0;i<tableau.hauteur;i++){
        for(j=0;j<tableau.largeur;j++) {
            tableau.grille[i][j] = '_';
            if ((i == 0 || i==11) && (j == 0 || j == 11)) {
                tableau.grille[i][j] = ' ';
            } else if ((i == 0 && i != j) || (i == 11 && i != j)) {
                tableau.grille[i][j] = 'A' + (j - 1);
            } else if ((j == 0 && j != i) || (j == 11 && j != i)) {
                tableau.grille[i][j] = '0' + (i - 1);
            }
        }
    }

    return tableau;
}

Grid initialisation_tableau_ordi(){
    Grid tableau;
    tableau.hauteur=12;
    tableau.largeur=12;
    int i,j;

    for(i=0;i<tableau.hauteur;i++){
        for(j=0;j<tableau.largeur;j++){
            tableau.grille[i][j] = ' ';
            if ((i == 0 || i==11) && (j == 0 || j == 11)) {
                tableau.grille[i][j] = ' ';
            } else if ((i == 0 && i != j) || (i == 11 && i != j)) {
                tableau.grille[i][j] = '_';
            } else if ((j == 0 && j != i) || (j == 11 && j != i)) {
                tableau.grille[i][j] = '|';
            }
        }
    }
    return tableau;
}

Grid placement_grille_bateau(Grid tableau_ordi, Boat bateau[], int i){

    switch(i) {
        case 0 :
            if (bateau[i].H_V  == 0){
                tableau_ordi = placement_horizontal(tableau_ordi,bateau[i]);
            }else{
                tableau_ordi = placement_vertical(tableau_ordi,bateau[i]);
            }
            break;

        case 1 :
            if (bateau[i].H_V  == 0){
                tableau_ordi = placement_horizontal(tableau_ordi,bateau[i]);
            }else{
                tableau_ordi = placement_vertical(tableau_ordi,bateau[i]);
            }
            break;

        case 2 :
            if (bateau[i].H_V  == 0){
                tableau_ordi = placement_horizontal(tableau_ordi,bateau[i]);
            }else{
                tableau_ordi = placement_vertical(tableau_ordi,bateau[i]);
            }
            break;

        case 3 :
            if (bateau[i].H_V  == 0){
                tableau_ordi = placement_horizontal(tableau_ordi,bateau[i]);
            }else{
                tableau_ordi = placement_vertical(tableau_ordi,bateau[i]);
            }
            break;

        case 4 :
            if (bateau[i].H_V  == 0){
                tableau_ordi = placement_horizontal(tableau_ordi,bateau[i]);
            }else{
                tableau_ordi = placement_vertical(tableau_ordi,bateau[i]);
            }
    }

    return tableau_ordi;
}

void affichage_tableau(Grid tableau_ordi)
{
    int i,j;

    for(i=0;i<tableau_ordi.hauteur;i++){
        for(j=0;j<tableau_ordi.largeur;j++){
            printf("%c  ",tableau_ordi.grille[i][j]);
        }
        printf("\n");
    }
}

Grid placement_vertical(Grid tableau_ordi,Boat bateau){
    int i;

    for (i=0;i<bateau.taille_bateau;i++)
    {
        tableau_ordi.grille[1+bateau.ligne+i][1+bateau.colonne] = bateau.identification;
    }
    return tableau_ordi;
}

Grid placement_horizontal(Grid tableau_ordi,Boat bateau){
    int i;

    for (i=0;i<bateau.taille_bateau;i++){
        tableau_ordi.grille[1+bateau.ligne][1+bateau.colonne+i] = bateau.identification;
    }
    return tableau_ordi;
}



Impact demande_tir(Grid tableau_joueur){
    Impact tir_actuel;
    char ligne[2]={0};
    char T[3]={0};
    char lettre;
    int chiffre;
    int verification;

    do{
        verification=0;
        printf("En quelle case voulez vous tirer ( de A0 a J9) ?\n");
        scanf(" %s", &T);
        lettre = toupper(T[0]);
        ligne[0] = T[1];
        chiffre = atoi(ligne);
        tir_actuel.colonne= lettre-'A';
        tir_actuel.ligne= chiffre;
        while( tir_actuel.colonne < 0 || tir_actuel.colonne > 9 || tir_actuel.ligne <0 || tir_actuel.ligne>9 || T[2]!= '\0')
        {
        printf("Votre tir n'est pas valide (case inconnue), veuillez recommencer ...\n");
            scanf(" %s", &T);
            lettre = toupper(T[0]);
            ligne[0] = T[1];
            chiffre = atoi(ligne);
            tir_actuel.colonne= lettre-'A';
            tir_actuel.ligne= chiffre;
        }
        if (tableau_joueur.grille[1 + tir_actuel.ligne][1 + tir_actuel.colonne] == 'O' ||
            tableau_joueur.grille[1 + tir_actuel.ligne][1 + tir_actuel.colonne] == 'X') {
            verification = 1;
            printf("Votre tir n'est pas valide (case deja touchee), veuillez recommencer ...\n");
        }
    }while(verification == 1);

    return tir_actuel;
}

/*Impact tir_actuel;
    char colonne;
    int verification;
    do{
        verification=0;
        printf("Sur quelle colonne voulez-vous tirer (de A a J) ?\n");
        scanf(" %c", &colonne);
        colonne = toupper(colonne);
        tir_actuel.colonne = colonne - 'A';
        while( tir_actuel.colonne < 0 || tir_actuel.colonne > 9)
        {
            printf("Veuillez saisir une colonne valide (de A a J).\n");
            scanf(" %c", &colonne);
            colonne = toupper(colonne);
            tir_actuel.colonne = colonne - 'A';
        }

        printf("Sur quelle ligne voulez-vous tirer (de 0 a 9) ?\n");
        scanf(" %d", &tir_actuel.ligne);
        while(tir_actuel.ligne < 0 || tir_actuel.ligne > 9) {
            printf("Veuillez saisir une ligne valide (de 0 a 9).\n");
            scanf(" %d", &tir_actuel.ligne);
        }
        if (tableau_joueur.grille[1 + tir_actuel.ligne][1 + tir_actuel.colonne] == 'O' ||
            tableau_joueur.grille[1 + tir_actuel.ligne][1 + tir_actuel.colonne] == 'X') {
            verification = 1;
        }
    }while(verification == 1);*/

Grid tir_artillerie(Grid tableau_joueur, Grid tableau_ordi,Impact point_impact,int NB_bateau,Boat bateau[]) {
    int i, j;
    for (j = 1; j < 11; j++) {
        for (i = 0; i < NB_bateau; i++) {
            if (tableau_joueur.grille[point_impact.ligne + 1][j] == '_' &&
                tableau_ordi.grille[point_impact.ligne + 1][j] == bateau[i].identification) {
                tableau_joueur.grille[point_impact.ligne + 1][j] = 'X';
            }
        }
        if (tableau_joueur.grille[point_impact.ligne + 1][j] == '_') {
            tableau_joueur.grille[point_impact.ligne + 1][j] = 'O';
        }
    }
    for (j = 1; j < 11; j++) {
        for (i = 0; i < NB_bateau; i++) {
            if (tableau_joueur.grille[j][point_impact.colonne + 1] == '_' && tableau_ordi.grille[j][point_impact.colonne + 1] == bateau[i].identification) {
                tableau_joueur.grille[j][point_impact.colonne + 1] = 'X';
            }
        }
        if (tableau_joueur.grille[j][point_impact.colonne + 1] == '_' ) {
            tableau_joueur.grille[j][point_impact.colonne + 1] = 'O';
        }
    }

    return tableau_joueur;
}

Grid tir_bombe(Grid tableau_joueur, Grid tableau_ordi,Impact point_impact,int NB_bateau,Boat bateau[]) {
    int i, j, k;

    for (j = -1; j < 4; j++) {
        for (i = 0; i < NB_bateau; i++) {
            if (tableau_joueur.grille[point_impact.ligne + 1][point_impact.colonne+j] == '_' && tableau_ordi.grille[point_impact.ligne + 1][point_impact.colonne+j] == bateau[i].identification && point_impact.colonne + j > 0 && point_impact.colonne + j <= 11) {
                tableau_joueur.grille[point_impact.ligne + 1][point_impact.colonne+j] = 'X';
            }
        }
        if (tableau_joueur.grille[point_impact.ligne + 1][point_impact.colonne+j] == '_') {
            tableau_joueur.grille[point_impact.ligne + 1][point_impact.colonne+j] = 'O';
        }
    }

    for (j = -1; j < 4; j++) {
        for (i = 0; i < NB_bateau; i++) {
            if (tableau_joueur.grille[point_impact.ligne+j][point_impact.colonne + 1] == '_' && tableau_ordi.grille[point_impact.ligne+j][point_impact.colonne + 1] == bateau[i].identification && point_impact.ligne + j > 0 && point_impact.ligne + j <= 11) {
                tableau_joueur.grille[point_impact.ligne+j][point_impact.colonne + 1] = 'X';
            }
        }
        if (tableau_joueur.grille[point_impact.ligne+j][point_impact.colonne + 1] == '_' ) {
            tableau_joueur.grille[point_impact.ligne+j][point_impact.colonne + 1] = 'O';
        }
    }
    for (j = 0; j < 3; j=j+2) {
        for(k=0; k<3;k=k+2) {
            for (i = 0; i < NB_bateau; i++) {
                if (tableau_joueur.grille[point_impact.ligne + j][point_impact.colonne + k] == '_' &&
                    tableau_ordi.grille[point_impact.ligne + j][point_impact.colonne + k] == bateau[i].identification && point_impact.ligne + j > 0 && point_impact.ligne + j <= 11) {
                    tableau_joueur.grille[point_impact.ligne + j][point_impact.colonne + k] = 'X';
                }
            }
            if (tableau_joueur.grille[point_impact.ligne + j][point_impact.colonne + k] == '_') {
                tableau_joueur.grille[point_impact.ligne + j][point_impact.colonne + k] = 'O';
            }
        }
    }
    return tableau_joueur;
}

Grid tir_simple(Grid tableau_joueur, Grid tableau_ordi, Impact point_impact){

    if(tableau_ordi.grille[1+point_impact.ligne][1+point_impact.colonne] == ' '){
        tableau_joueur.grille[1+point_impact.ligne][1+point_impact.colonne] = 'O';
    } else {
        tableau_joueur.grille[1+point_impact.ligne][1+point_impact.colonne] = 'X';
    }
    return tableau_joueur;
}

Grid tir_tactique(Grid tableau_joueur, Grid tableau_ordi, Impact point_impact){

    if(tableau_ordi.grille[1+point_impact.ligne][1+point_impact.colonne] == ' '){
        tableau_joueur.grille[1+point_impact.ligne][1+point_impact.colonne] = 'O';
    } else {
        tableau_joueur.grille[1+point_impact.ligne][1+point_impact.colonne] = 'X';
    }
    return tableau_joueur;
}
/**
 *
 *
 *
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