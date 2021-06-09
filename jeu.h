//
// Created by arnau on 27/05/2021.
//

#ifndef PLANCHIN_ERHART_COJOCARU_JEU_H
#define PLANCHIN_ERHART_COJOCARU_JEU_H

#include "grille.h"
#include "inventory.h"
#include "boat.h"

/**
 * Affiche le menu avec les trois choix (Démarrer, Charger, Quitter)
 * Le choix "Charger" ne s'affiche pas si il n'y a aucune partie en sauvegarde
 * Message d'erreur si l'utilisateur saisit une lettre incorrecte (en fonction des choix possibles)
 * @param file
 * @return
 */
char menu(FILE * file);

/**
 * Affiche les modes disponibles et demande au joueur lequel il souhaite utiliser
 * Message d'erreur si l'utilisateur saisit une lettre incorrecte
 * @return
 */
char demande_mode();

/**
 * Deplace un bateau choisi alétoirement si il peut se deplacer
 * @param tableau_ordi
 * @param tableau_joueur
 * @param bateau
 */
void deplacement_bateau_mode_active(Grid *tableau_ordi, Grid tableau_joueur, Boat *(bateau[]),int NB_bateau);

/**
 *
 * @param tableau_joueur
 * @param tableau_ordi
 * @param missile
 * @param bateau
 * @param NB_bateau
 * @param mode
 * @param nombre_tour
 * @param charger
 * @return
 */
int game(Grid tableau_joueur, Grid tableau_ordi, Inventory missile, Boat bateau[], int NB_bateau,char mode,int nombre_tour, int charger);

/**
 * Sauvegarde dans le fichier "sauvegarde_jeu.txt"
 * Nombre de bateau sauvegardé
 * Nombre de tour sauvegardé
 * Mode sauvegardé
 * Nombre de missiles restants sauvegardé
 * Taille, Ligne, Colonne, Sens, Cases touchées et identification de chauqe bateau sauvegardé
 * Tableau joueur et ordinateur sauvegardé
 * @param file
 * @param tableau_joueur
 * @param tableau_ordi
 * @param missile
 * @param bateau
 * @param NB_bateau
 * @param nombre_tour
 * @param mode
 */
void save(FILE* file, Grid tableau_joueur, Grid tableau_ordi, Inventory missile, Boat bateau[], int NB_bateau, int nombre_tour, char mode);

/**
 * Récupère les données sauvegardées dans la fonction save
 * Partie chargée devient la partie en cours
 * @param file
 * @return
 */
int load(FILE* file);

/**
 * Conditionne la victoire ou la défaite en fonction du nombre de missiles restants ou des bateaux coulés
 * @param bateau
 * @param missile
 * @param NB_bateau
 * @return
 */
int fin_partie(Boat bateau[],Inventory missile,int NB_bateau);

/**
 * Affiche le résultat de la partie (Victoire, Défaite ou Sauvegarde)
 * @param partie
 */
void partie_finie(int partie);

/**
 * Demande à l'utilisateur si il souhaite recommencer une partie
 * Message d'erreur si l'utilisateur saisit une lettre incorrecte
 * @return
 */
char recommencer();



#endif //PLANCHIN_ERHART_COJOCARU_JEU_H
