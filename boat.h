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
 * Initialise la taille du bateau, son orientation, son nombre de cases touchées (0 au début) et assigne une lettre identificatrice à chaque bateau
 * @param i
 * @param bateau tableau des bateaux
 * @return la taille, l'orientation, le nombre de cases touchées et la lettre identificatrice du bateau selectionnée
 */
Boat initialisation_bateau(int i,Boat bateau[]);

/**
 * Place les bateaux dans la grille de jeu ordinateur en fonction de son horizontalité ou de sa verticalité
 * @param tableau
 * @param bateau
 * @param i
 * @return la position du bateau
 */
Boat placement_bateau(Grid tableau, Boat bateau[], int i);

/**
 * Définit la position des bateaux horizontaux aléatoirement
 * @param tableau_ordi
 * @param bateau
 * @return la position du bateau (ligne et colonne)
 */
Boat position_bateau_horizontal(Grid tableau_ordi, Boat bateau);



/**
 * Vérifie et empêche les collisions horizontales entre les bateaux déjà positionnés
 * @param tableau_ordi
 * @param ligne
 * @param colonne
 * @param taille_bateau
 * @return 1 si il peut y avoir une colision ou 0 si il n'y en a pas
 */
int collision_horizontale(Grid tableau_ordi,Boat bateau);

/**
 * Définit la position des bateaux verticaux
 * @param tableau_ordi
 * @param bateau
 * @return la position du bateau (ligne et colonne)
 */
Boat position_bateau_vertical(Grid tableau_ordi, Boat bateau);

/**
 * Vérifie et empêche les collisions verticales entre les bateaux déjà positionnés
 * @param tableau_ordi
 * @param ligne
 * @param colonne
 * @param taille_bateau
 * @return 1 si il peut y avoir une colision ou 0 si il n'y en a pas
 */
int collision_verticale(Grid tableau_ordi,Boat bateau);


/**
 * Affiche le nombre de bateaux restants et ceux qui ont été touchés
 * Affiche si un bateau est coulé
 * @param bateau
 * @param NB_bateau
 */
void affichage_nb_bateau(Boat bateau[], int NB_bateau);


#endif //PLANCHIN_ERHART_COJOCARU_BOAT_H