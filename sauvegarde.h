//
// Created by arnau on 13/06/2021.
//

#ifndef PLANCHIN_ERHART_COJOCARU_SAUVEGARDE_H
#define PLANCHIN_ERHART_COJOCARU_SAUVEGARDE_H

#include "grille.h"
#include "inventory.h"
#include "boat.h"
#include "jeu.h"

/**
 * On vérifie la demande de l'utilisateur lorsqu'il veut sauvegarder la partie
 * Si l'utilisateur veut sauvegarder la partie, on regarde si il y une sauvegarde déjà présente
 * Si oui, on lui demande si il veut écraser cette sauvegarde
 * @param file le fichier de sauvegarde
 * @param tableau_joueur
 * @param tableau_ordi
 * @param missile
 * @param bateau
 * @param NB_bateau
 * @param nombre_tour
 * @param mode
 * @return un chiffre entre 4 et 5 (Sauvegarder ou quitter la partie si on ne veut pas ecraser la sauvegarde)
 */
int demande_sauvegarde(FILE* file, Grid tableau_joueur, Grid tableau_ordi, Inventory missile, Boat bateau[], int NB_bateau, int nombre_tour, char mode);


/**
 * Sauvegarde dans le fichier "sauvegarde_jeu.txt"
 * Nombre de bateau sauvegardé
 * Nombre de tour sauvegardé
 * Mode sauvegardé
 * Nombre de missiles restants sauvegardé
 * Taille, Ligne, Colonne, Sens, Cases touchées et identification de chauqe bateau sauvegardé
 * Tableau joueur et ordinateur sauvegardé
 * @param file le fichier de sauvegarde
 * @param tableau_joueur
 * @param tableau_ordi
 * @param missile Inventaire de missile
 * @param bateau les données des bateaux
 * @param NB_bateau Nombre de bateau au total (5)
 * @param nombre_tour
 * @param mode
 */
void save(FILE* file, Grid tableau_joueur, Grid tableau_ordi, Inventory missile, Boat bateau[], int NB_bateau, int nombre_tour, char mode);


/**
 * Récupère les données sauvegardées dans la fonction save
 * Partie chargée devient la partie en cours
 * @param file
 * @return un nombre définissant si la partie est finie ou non ou doit etre sauvegardé
 */
int load(FILE* file);

#endif //PLANCHIN_ERHART_COJOCARU_SAUVEGARDE_H
