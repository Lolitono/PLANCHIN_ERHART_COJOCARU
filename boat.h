//
// Created by arnau on 27/05/2021.
//

#ifndef PLANCHIN_ERHART_COJOCARU_BOAT_H
#define PLANCHIN_ERHART_COJOCARU_BOAT_H


typedef struct {
    int taille_bateau;      // La taille du bateau (nombres de cases occupées)
    int ligne;              // Indique la ligne de l'extrémité gauche (ou simplement du bateau si bateau horizontal)
    int colonne;            // Indique la colonne de l'extrémité gauche du bateau (ou simplement du bateau si bateau vertical)
    int H_V;                // 0 = horizontal ; 1 = vertical
    int touche;             // Nombre de cases touchées
    char identification;    // On associe une lettre à chaque bateau
}Boat;

#include "grille.h"
#include "inventory.h"


/**
 * Initialise la taille du bateau, son orientation, son nombre de cases touchées (0 au début) et assigne une lettre identificatrice à chaque bateau
 * @param i Un compteur
 * @param bateau Le tableau de bateau
 * @return La taille, l'orientation, le nombre de cases touchées et la lettre identificatrice du bateau selectionné
 */
Boat initialisation_bateau(int i,Boat bateau[]);


/**
 * Place un bateau dans la grille de jeu ordinateur en fonction de son horizontalité ou de sa verticalité
 * @param tableau Le tableau de l'ordinateur
 * @param bateau Le tableau de bateau
 * @param i Un compteur
 * @return La position du bateau
 */
Boat placement_bateau(Grid tableau, Boat bateau[], int i);


/**
 * Définit aléatoirement la position d'un bateau horizontal
 * @param tableau_ordi Le tableau de l'ordinateur
 * @param bateau Le bateau choisi
 * @return La position du bateau (ligne et colonne)
 */
Boat position_bateau_horizontal(Grid tableau_ordi, Boat bateau);


/**
 * Vérifie et empêche les collisions horizontales entre les bateaux déjà positionnés
 * @param tableau_ordi Le tableau de l'ordinateur
 * @param bateau Le bateau choisi
 * @return 1 s'il peut y avoir une collision ou 0 si il n'y en a pas
 */
int collision_horizontale(Grid tableau_ordi,Boat bateau);


/**
 * Définit aléatoirement la position d'un bateau vertical
 * @param tableau_ordi Le tableau de l'ordinateur
 * @param bateau Le bateau choisi
 * @return La position du bateau (ligne et colonne)
 */
Boat position_bateau_vertical(Grid tableau_ordi, Boat bateau);


/**
 * Vérifie et empêche les collisions verticales entre les bateaux déjà positionnés
 * @param tableau_ordi Le tableau de l'ordinateur
 * @param bateau Le bateau choisi
 * @return 1 si il peut y avoir une collision ou 0 si il n'y en a pas
 */
int collision_verticale(Grid tableau_ordi,Boat bateau);


/**
 * Affiche le nombre de bateaux restants et ceux qui ont été touchés
 * Affiche si un bateau est coulé
 * @param bateau Le tableau de bateau
 * @param NB_bateau Le nombre de bateau au total (5)
 */
void affichage_nb_bateau(Boat bateau[], int NB_bateau);


#endif //PLANCHIN_ERHART_COJOCARU_BOAT_H