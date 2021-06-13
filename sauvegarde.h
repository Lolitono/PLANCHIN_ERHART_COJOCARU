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
 * @param file Le fichier de sauvegarde
 * @param tableau_joueur Le tableau de l'utilisateur
 * @param tableau_ordi Le tableau de l'ordinateur
 * @param missile L'inventaire des missiles possédés par l'utilisateur
 * @param bateau Le tableau de bateau
 * @param NB_bateau Le nombre de bateau au total (5)
 * @param nombre_tour Le nombre de tour de la partie
 * @param mode Le mode de jeu choisi par l'utilisateur
 * @return un chiffre entre 4 et 5 (Sauvegarder ou quitter la partie si on ne veut pas ecraser la sauvegarde)
 */
int demande_sauvegarde(FILE* file, Grid tableau_joueur, Grid tableau_ordi, Inventory missile, Boat bateau[], int NB_bateau, int nombre_tour, char mode);


/**
 * Sauvegarde dans le fichier "sauvegarde_jeu.txt"
 * Nombre de bateau sauvegardé
 * Nombre de tour sauvegardé
 * Mode sauvegardé
 * Nombre de missiles restants sauvegardé
 * Taille, Ligne, Colonne, Orientation, Cases touchées et identification de chaque bateau sauvegardé
 * Tableau joueur et ordinateur sauvegardé
 * @param file Le fichier de sauvegarde
 * @param tableau_joueur Le tableau de l'utilisateur
 * @param tableau_ordi Le tableau de l'ordinateur
 * @param missile L'inventaire des missiles possédés par l'utilisateur
 * @param bateau Le tableau de bateau
 * @param NB_bateau Le nombre de bateau au total (5)
 * @param nombre_tour Le nombre de tour de la partie
 * @param mode Le mode de jeu choisi par l'utilisateur
 */
void save(FILE* file, Grid tableau_joueur, Grid tableau_ordi, Inventory missile, Boat bateau[], int NB_bateau, int nombre_tour, char mode);


/**
 * Récupère les données sauvegardées dans la fonction save
 * Partie chargée devient la partie en cours
 * On lance la partie avec les données chargées
 * @param file Le fichier de sauvegarde
 * @return Un nombre définissant si la partie est finie ou non ou doit etre sauvegardé
 */
int load(FILE* file);


#endif //PLANCHIN_ERHART_COJOCARU_SAUVEGARDE_H
