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
 *
 * @param bateau
 * @param NB_bateau
 */
void affichage_nb_bateau(Boat bateau[], int NB_bateau);

/**
 *
 * @param i
 * @return
 */
Boat initialisation_bateau(int i);

/**
 *
 * @param tableau
 * @param bateau
 * @param i
 * @return
 */
Boat placement_bateau(Grid tableau, Boat bateau[], int i);



/**
 *
 * @param tableau_ordi
 * @param bateau
 * @return
 */
Boat position_bateau_vertical(Grid tableau_ordi, Boat bateau);

#endif //PLANCHIN_ERHART_COJOCARU_BOAT_H
