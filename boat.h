//
// Created by arnau on 27/05/2021.
//

#ifndef PLANCHIN_ERHART_COJOCARU_BOAT_H
#define PLANCHIN_ERHART_COJOCARU_BOAT_H


typedef struct {
    int taille_bateau;
    int ligne;
    int colonne;
    int H_V;
    int touche;
    char identification;
}Boat;

#include "grille.h"
#include "inventory.h"

/**
 * Affiche le nombre de bateaux restants et ceux qui ont été touchés
 * Affiche si un bateau est coulé
 * @param bateau
 * @param NB_bateau
 */
void affichage_nb_bateau(Boat bateau[], int NB_bateau);

/**
 * Initialise le nombre de bateau
 * @param i
 * @return
 */
Boat initialisation_bateau(int i);

/**
 * Place les bateaux dans la grille de jeu ordinateur en fonction de son horizontalité ou de sa verticalité
 * @param tableau
 * @param bateau
 * @param i
 * @return
 */
Boat placement_bateau(Grid tableau, Boat bateau[], int i);



/**
 * Définit la position des bateaux verticaux
 * @param tableau_ordi
 * @param bateau
 * @return
 */
Boat position_bateau_vertical(Grid tableau_ordi, Boat bateau);

/**
 * Empêche les collisions verticales entre les bateaux verticaux
 * @param tableau_ordi
 * @param ligne
 * @param colonne
 * @param taille_bateau
 * @return
 */
int collision_verticale(Grid tableau_ordi,Boat bateau);

/**
 * Définit la position des bateaux horizontaux
 * @param tableau_ordi
 * @param bateau
 * @return
 */
Boat position_bateau_horizontal(Grid tableau_ordi, Boat bateau);

/**
 * Empêche les collisions horizontales entre les bateaux horizontaux
 * @param tableau_ordi
 * @param ligne
 * @param colonne
 * @param taille_bateau
 * @return
 */
int collision_horizontale(Grid tableau_ordi,Boat bateau);

#endif //PLANCHIN_ERHART_COJOCARU_BOAT_H
