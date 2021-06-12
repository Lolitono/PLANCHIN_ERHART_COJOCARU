//
// Created by arnau on 27/05/2021.
//

#ifndef PLANCHIN_ERHART_COJOCARU_GRILLE_H
#define PLANCHIN_ERHART_COJOCARU_GRILLE_H

typedef struct{
    int hauteur;            // hauteur du tableau
    int largeur;            // largeur du tableau
    char grille[12][12];    // tableau
}Grid;

typedef struct {
    int ligne;              // ligne du point d'impact
    int colonne;            // colonne du point d'impact
}Impact;

#include "boat.h"
#include "inventory.h"

/**
 * Initialisation du tableau visible par le joueur,
 * avec les chiffres et lettres aux extrémités pour pouvoir se repérer dans la grille ainsi que les tirets pour visualiser les cases
 * @return le tableau visible par l'utlisateur
 */
Grid initialisation_tableau();


/**
 * Initialisation du tableau de l'ordinateur, qui enregistre la position des bateaux
 * @return le tableau de l'ordinateur
 */
Grid initialisation_tableau_ordi();


/**
 * Place les bateaux de manière aléatoire horizotalement ou verticalement
 * @param tableau_ordi
 * @param bateau
 * @param i
 * @return le nouveau tableau ordi avec le bateau positionné en fonction de son horizontalité/verticalité et de sa taille
 */
Grid placement_grille_bateau(Grid tableau_ordi, Boat bateau[], int i);


/**
 * Place les bateaux horizontalement (de gauche à droite) sur le tableau ordinateur
 * @param tableau_ordi
 * @param bateau
 * @return La grille de l'ordi avec un bateau placer horizontalement de la gauche vers la droite
 */
Grid placement_horizontal(Grid tableau_ordi,Boat bateau);


/**
 * Place les bateaux verticalement (du haut vers le bas) sur le tableau ordinateur
 * @param tableau_ordi
 * @param bateau
 * @return La grille de l'ordi avec un bateau placer horizontalement de la gauche vers la droite
 */
Grid placement_vertical(Grid tableau_ordi,Boat bateau);


/**
 * Affiche le tableau de jeu
 * @param tableau le tabelau que l'on veut afficher
 */
void affichage_tableau(Grid tableau);
















#endif //PLANCHIN_ERHART_COJOCARU_GRILLE_H