//
// Created by arnau on 27/05/2021.
//

#ifndef PLANCHIN_ERHART_COJOCARU_INVENTORY_H
#define PLANCHIN_ERHART_COJOCARU_INVENTORY_H


typedef struct {
    int artillerie;
    int tactique;
    int bombe;
    int simple;
}Inventory;

#include "grille.h"
#include "boat.h"

/**
 * Demande la difficulté à laquelle l'utilisateur veut jouer
 * Etablit l'inventaire pour chaque difficulté (nombres de missiles)
 * @return l'inventaire de l'utilisateur
 */
Inventory demande_difficulte();

/**
 * Affiche le nombre de missiles au début du jeu selon la difficulté et développe ce qu'ils font
 * @param missile
 */
void affichage_missile_depart(Inventory missile);

/**
 * Affiche le nombre de missiles restants à chaque tour
 * @param missile
 */
void affichage_missile(Inventory missile);

/**
 * Demande à l'utilisateur avec quel missile il souhaite tirer
 * Message d'erreur (redemande le choix) si missile choisi n'existe pas ou que l'utilisateur n'a plus de ce missile
 * @param missile
 * @return le missile que l'utilisateur a choisi
 */
char demande_missile(Inventory missile);

/**
 * Indique si il reste assez de missiles de la catégorie choisie
 * @param missile
 * @param tir_actuel
 * @return 1 si l'utilisateur n'a plus assez de missile et 0 si il en a encore
 */
int verification_missile(Inventory missile,char tir_actuel);




#endif //PLANCHIN_ERHART_COJOCARU_INVENTORY_H
