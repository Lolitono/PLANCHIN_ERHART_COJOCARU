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
            tableau.grille[i][j] = '_';                                 // Des underscore pour montrer les cases encore non touchées
            if ((i == 0 || i==11) && (j == 0 || j == 11)) {
                tableau.grille[i][j] = ' ';                             // Des espaces aux coins du tableau pour le visuel
            } else if ((i == 0 && i != j) || (i == 11 && i != j)) {
                tableau.grille[i][j] = 'A' + (j - 1);                   // Des lettres sur la première et dernière ligne du tableau pour caractériser chaque colonne sur laquelle le joueur pourra lancer un missile
            } else if ((j == 0 && j != i) || (j == 11 && j != i)) {
                tableau.grille[i][j] = '0' + (i - 1);                   // Des chiffres sur la première et dernière colonne du tableau pour caractériser chaque ligne sur laquelle le joueur pourront lancer un missile
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
            tableau.grille[i][j] = ' ';                                 // Des espaces sur le tableau pour rendre la détection des bateaux plus facile
            if ((i == 0 || i==11) && (j == 0 || j == 11)) {
                tableau.grille[i][j] = ' ';                             // Des espaces aux coins du tableau pour le visuel si l'on affiche le tableau de l'ordinateur
            } else if ((i == 0 && i != j) || (i == 11 && i != j)) {
                tableau.grille[i][j] = '_';                             // Des underscore sur la première et dernière ligne du tableau pour améliorer le visuel si l'on affiche le tableau de l'ordinateur
            } else if ((j == 0 && j != i) || (j == 11 && j != i)) {
                tableau.grille[i][j] = '|';                             // Des '|' sur la première et dernière colonne du tableau pour améliorer le visuel si l'on affiche le tableau de l'ordinateur
            }
        }
    }
    return tableau;
}

Grid placement_grille_bateau(Grid tableau_ordi, Boat bateau[], int i){

    if (bateau[i].H_V  == 0){
        tableau_ordi = placement_horizontal(tableau_ordi,bateau[i]);
    }else{
        tableau_ordi = placement_vertical(tableau_ordi,bateau[i]);
    }

    return tableau_ordi;
}

Grid placement_horizontal(Grid tableau_ordi,Boat bateau){
    int i;

    for (i=0;i<bateau.taille_bateau;i++){
        tableau_ordi.grille[1+bateau.ligne][1+bateau.colonne+i] = bateau.identification; // On place les lettres représentant les bateaux horizontaux sur la grille ordinateur
    }
    return tableau_ordi;
}


Grid placement_vertical(Grid tableau_ordi,Boat bateau){
    int i;

    for (i=0;i<bateau.taille_bateau;i++)
    {
        tableau_ordi.grille[1+bateau.ligne+i][1+bateau.colonne] = bateau.identification; // On place les lettres représentant les bateaux verticaux sur la grille ordinateur
    }
    return tableau_ordi;
}

void affichage_tableau(Grid tableau)
{
    int i,j;

    for(i=0;i<tableau.hauteur;i++){
        for(j=0;j<tableau.largeur;j++){
            printf("%c  ",tableau.grille[i][j]);    // On affiche chaque caractère à la suite des autres avec des espaces pour reformer le tableau du joueur ou de l'ordinateur sur la console
        }
        printf("\n");
    }
}

