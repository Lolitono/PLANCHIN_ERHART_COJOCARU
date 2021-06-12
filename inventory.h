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
Inventory assignation_missile(char difficulte);

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

/**
 * Recherche sur la grille ordinateur si un bateau ou plusieurs ont été touché
 * Créer la zone d'impact du tir d'artillerie (Colonne et Ligne de la case touché sont également touchées)
 * Indique sur la grille du joueur si un bateau ou plusieurs ont été touché
 * @param tableau_joueur
 * @param tableau_ordi
 * @param point_impact
 * @param NB_bateau
 * @param bateau
 * @return le nouveau tableau joueur avec des 'X' ou des 'O' selon si le joueur a touché un bateau ou non
 */
void tir_artillerie(Grid *tableau_joueur, Grid *tableau_ordi,Impact point_impact,int NB_bateau,Boat bateau[],char mode);


/**
 * Recherche sur la grille ordinateur si un bateau ou plusieurs ont été touché
 * Créer la zone d'impact de la bombe (Toutes las cases en étoile autour de la case touchée)
 * Indique sur la grille du joueur si un bateau ou plusieurs ont été touché
 * @param tableau_joueur
 * @param tableau_ordi
 * @param point_impact
 * @param NB_bateau
 * @param bateau
 * @return le nouveau tableau joueur avec des 'X' ou des 'O' selon si le joueur a touché un bateau ou non
 */
void tir_bombe(Grid *tableau_joueur, Grid *tableau_ordi,Impact point_impact,int NB_bateau,Boat bateau[],char modecc);

/** *
 * Recherche sur la grille ordinateur si un bateau a été touché
 * Indique sur la grille du joueur si un bateau a été touché
 * @param tableau_joueur
 * @param tableau_ordi
 * @param point_impact
 * @return le nouveau tableau joueur avec une 'X' ou un 'O' selon si le joueur a touché un bateau ou non
 */
void tir_simple(Grid *tableau_joueur, Grid *tableau_ordi, Impact point_impact,char mode,int NB_bateau,Boat bateau[]);



/**
 * Recherche sur la grille ordinateur et joueur si un bateau a été touché
 * Indique sur la grille du joueur la/les case(s) ou 1 (des) bateaux a (ont) été touché(s) (ou envoie juste un message si on est en mode blind)
 * Enlève du tableau ordi les identification de bateaux correspondant à/aux (la) cases(s) touchée(s)
 * @param tableau_joueur
 * @param tableau_ordi
 * @param point_impact
 * @param NB_bateau
 * @param bateau
 * @param mode
 */
void tir_tactique(Grid *tableau_joueur, Grid *tableau_ordi, Impact point_impact,int NB_bateau, Boat bateau[], char mode);

#endif //PLANCHIN_ERHART_COJOCARU_INVENTORY_H