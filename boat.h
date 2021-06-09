//
// Created by arnau on 27/05/2021.
//

#ifndef PLANCHIN_ERHART_COJOCARU_BOAT_H
#define PLANCHIN_ERHART_COJOCARU_BOAT_H


typedef struct {
    int taille_bateau; // la taille du bateau (nombres de cases occupées)
    int ligne; // indique la ligne de l'extrémité gauche (ou simplement du bateau si bateau horizontal)
    int colonne; // indique la colonne de l'extrémité gauche du bateau (ou simplement du bateau si bateau vertical)
    int H_V; // 0 = horizontal ; 1 = vertical
    int touche; // nombre de cases touchées
    char identification; // on associe une lettre à chaque bateau
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
