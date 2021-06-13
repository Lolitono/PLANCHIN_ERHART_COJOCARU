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
 * @return L'inventaire des missiles possédés par l'utilisateur
 */
Inventory assignation_missile(char difficulte);


/**
 * Affiche le nombre de missiles au début du jeu selon la difficulté et explique ce qu'ils font
 * @param missile L'inventaire des missiles possédés par l'utilisateur
 */
void affichage_missile_depart(Inventory missile);


/**
 * Affiche le nombre de missiles restants à chaque tour
 * @param missile L'inventaire des missiles possédés par l'utilisateur
 */
void affichage_missile(Inventory missile);


/**
 * Demande à l'utilisateur avec quel missile il souhaite tirer
 * Message d'erreur (redemande le choix) si le missile choisi n'existe pas ou que l'utilisateur n'a plus de ce missile
 * @param missile L'inventaire des missiles possédés par l'utilisateur
 * @return Le missile que l'utilisateur a choisi
 */
char demande_missile(Inventory missile);


/**
 * Indique s'il reste assez de missiles de la catégorie choisie
 * @param missile L'inventaire des missiles possédés par l'utilisateur
 * @param tir_actuel Le missile choisi par l'utilisateur
 * @return 1 si l'utilisateur n'a plus assez de missile et 0 s'il en a encore
 */
int verification_missile(Inventory missile,char tir_actuel);


/**
 * Recherche sur le tableau de l'ordinateur si un bateau ou plusieurs ont été touchés
 * Créer la zone d'impact du tir d'artillerie (Colonne et Ligne de la case touché sont également touchées)
 * Indique sur la grille du joueur si un bateau ou plusieurs ont été touchés
 * Enlève du tableau de l'ordinateaur l'identification des bateaux correspondant à la/aux case(s) touchée(s) si un ou plusieurs bateaux ont été touchés
 * @param tableau_joueur Le tableau de l'utilisateur
 * @param tableau_ordi Le tableau de l'ordinateur
 * @param point_impact Le point d'imapct du missile
 * @param NB_bateau Le nombre de bateau au total (5)
 * @param bateau Le tableau de bateau
 * @param mode Le mode de jeu choisi par l'utilisateur
 */
void tir_artillerie(Grid *tableau_joueur, Grid *tableau_ordi,Impact point_impact,int NB_bateau,Boat bateau[],char mode);


/**
 *
 * Recherche sur le tableau de l'ordinateur si un bateau ou plusieurs ont été touchés
 * Créer la zone d'impact de la bombe (Toutes les cases en étoile autour de la case touchée)
 * Indique sur la grille du joueur si un bateau ou plusieurs ont été touchés
 * Enlève du tableau de l'ordinateaur l'identification des bateaux correspondant à la/aux case(s) touchée(s) si un ou plusieurs bateaux ont été touchés
 * @param tableau_joueur Le tableau de l'utilisateur
 * @param tableau_ordi Le tableau de l'ordinateur
 * @param point_impact Le point d'imapct du missile
 * @param NB_bateau Le nombre de bateau au total (5)
 * @param bateau Le tableau de bateau
 * @param mode Le mode de jeu choisi par l'utilisateur
 */
void tir_bombe(Grid *tableau_joueur, Grid *tableau_ordi,Impact point_impact,int NB_bateau,Boat bateau[],char mode);


/**
 * Recherche sur le tableau de l'ordinateur si un bateau a été touché
 * Indique sur la grille du joueur si un bateau a été touché
 * Enlève du tableau de l'ordinateaur l'identification du bateau correspondant à la case touchée si un bateau a été touché
 * @param tableau_joueur Le tableau de l'utilisateur
 * @param tableau_ordi Le tableau de l'ordinateur
 * @param point_impact Le point d'imapct du missile
 * @param mode Le mode de jeu choisi par l'utilisateur
 * @param NB_bateau Le nombre de bateau au total (5)
 * @param bateau Le tableau de bateau
 */
void tir_simple(Grid *tableau_joueur, Grid *tableau_ordi, Impact point_impact,char mode,int NB_bateau,Boat bateau[]);


/**
 * Recherche sur le tableau de l'ordinateur si un bateau a été touché
 * Indique sur la grille du joueur la/les case(s) ou un (des) bateaux a (ont) été touché(s) (ou envoie juste un message si on est en mode blind)
 * Enlève du tableau de l'ordinateaur l'identification des bateaux correspondant à la/aux case(s) touchée(s) si un bateau a été touché
 * @param tableau_joueur Le tableau de l'utilisateur
 * @param tableau_ordi Le tableau de l'ordinateur
 * @param point_impact Le point d'imapct du missile
 * @param NB_bateau Le nombre de bateau au total (5)
 * @param bateau Le tableau de bateau
 * @param mode Le mode de jeu choisi par l'utilisateur
 */
void tir_tactique(Grid *tableau_joueur, Grid *tableau_ordi, Impact point_impact,int NB_bateau, Boat bateau[], char mode);


#endif //PLANCHIN_ERHART_COJOCARU_INVENTORY_H