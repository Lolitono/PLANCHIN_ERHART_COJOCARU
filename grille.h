//
// Created by arnau on 27/05/2021.
//

#ifndef PLANCHIN_ERHART_COJOCARU_GRILLE_H
#define PLANCHIN_ERHART_COJOCARU_GRILLE_H

typedef struct{
    int hauteur;
    int largeur;
    char grille[12][12];
}Grid;

typedef struct {
    int ligne;
    int colonne;
}Impact;

#include "boat.h"
#include "inventory.h"

/**
 * Initialisation du tableau visible par le joueur,
 * avec les chiffres et lettres aux extrémités pour pouvoir se repérer dans la grille ainsi que les tirets pour visualiser les cases
 * @return le tableau visible par l'utlisateur
 */
Grid initialisation_tableau();


/**
 * Initialisation du tableau de l'ordinateur, qui enregistre la position des bateaux
 * @return le tableau de l'ordinateur
 */
Grid initialisation_tableau_ordi();


/**
 * Place les bateaux de manière aléatoire horizotalement ou verticalement
 * @param tableau_ordi
 * @param bateau
 * @param i
 * @return
 */
Grid placement_grille_bateau(Grid tableau_ordi, Boat bateau[], int i);

/**
 * Affiche le tableau de jeu
 * @param tableau_ordi
 */
void affichage_tableau(Grid tableau_ordi);

/**
 * Place les bateaux horizontaux sur le tableau ordinateur
 * @param tableau_ordi
 * @param bateau
 * @return
 */
Grid placement_horizontal(Grid tableau_ordi,Boat bateau);

/**
 * Place les bateaux verticaux sur le tableau ordinateur
 * @param tableau_ordi
 * @param bateau
 * @return
 */
Grid placement_vertical(Grid tableau_ordi,Boat bateau);

/**
 * Demande où l'utilisateur veut tirer
 * Message d'erreur si l'utilisateur tire sur une case inconnue ou s'il tire sur une case déjà touchée
 * @param tableau_joueur
 * @return
 */
Impact demande_tir(Grid tableau_joueur);

/**
 * Recherche sur la grille ordinateur si un bateau ou plusieurs ont été touché
 * Créer la zone d'impact du tir d'artillerie (Colonne et Ligne de la case touchésont également touchées)
 * Indique sur les grilles si un bateau ou plusieurs ont été touché
 * @param tableau_joueur
 * @param tableau_ordi
 * @param point_impact
 * @param NB_bateau
 * @param bateau
 * @return
 */
Grid tir_artillerie(Grid tableau_joueur, Grid tableau_ordi,Impact point_impact,int NB_bateau,Boat bateau[]);

/**
 * Recherche sur la grille ordinateur si un bateau ou plusieurs ont été touché
 * Créer la zone d'impact de la bombe (Toutes las cases en étoile autour de la case touchée)
 * Indique sur les grilles si un bateau ou plusieurs ont été touché
 * @param tableau_joueur
 * @param tableau_ordi
 * @param point_impact
 * @param NB_bateau
 * @param bateau
 * @return
 */
Grid tir_bombe(Grid tableau_joueur, Grid tableau_ordi,Impact point_impact,int NB_bateau,Boat bateau[]);

/** *
 * Recherche sur la grille ordinateur si un bateau a été touché
 * Indique sur les grilles si un bateau a été touché
 * @param tableau_joueur
 * @param tableau_ordi
 * @param point_impact
 * @return
 */
Grid tir_simple(Grid tableau_joueur, Grid tableau_ordi, Impact point_impact);

/**
 * Recherche sur la grille ordinateur si un bateau a été touché
 * Prends l'identification d'un bateau et l'élimine en entier si il est touché
 * Indique sur les grilles si un bateau a été touché
 * @param tableau_joueur
 * @param tableau_ordi
 * @param point_impact
 * @return
 */
Grid tir_tactique(Grid tableau_joueur, Grid tableau_ordi, Impact point_impact);


#endif //PLANCHIN_ERHART_COJOCARU_GRILLE_H
