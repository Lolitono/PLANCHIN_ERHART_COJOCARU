//
// Created by arnau on 27/05/2021.
//

#ifndef PLANCHIN_ERHART_COJOCARU_JEU_H
#define PLANCHIN_ERHART_COJOCARU_JEU_H

typedef struct {
    int decision;                   // Un nombre choisi aléatoirement par l'ordinateur afin de savoir si il veut bouger un bateau
    char tableau_active[6];         /* Liste des bateaux pouvant se déplacer prenant sur chauqe case soit la lettre du bateau si celui-ci peut se déplacer,
                                    soit un espace si il ne peut pas se déplacer */
    int verification_mode_active;   // nombre de bateau ne pouvant pas se déplacer
    int choix_bateau;               // Bateau choisi parmi les bateaux pouvant se déplacer
    int max_gauche;                 // Déplacement max vers la gauche du bateau choisi
    int max_droite;                 // Déplacement max vers la droite du bateau choisi
    int max_haut;                   // Déplacement max vers le haut du bateau choisi
    int max_bas;                    // Déplacement max vers le bas du bateau choisi
    int mouvement_bateau;           // Déplacement du bateau choisi
}Actif;

#include "grille.h"
#include "inventory.h"
#include "boat.h"

/**
 * Affiche le menu avec les trois choix (Démarrer, Charger, Quitter)
 * Le choix "Charger" ne s'affiche pas si il n'y a aucune partie en sauvegarde
 * Message d'erreur si l'utilisateur saisit une lettre incorrecte (en fonction des choix possibles)
 * @param file  fichier de sauvegarde
 * @return une lettre entre D/C/Q en fonction du choix de l'utilisateur
 */
char menu(FILE * file);

/**
 * Affiche les modes disponibles et demande au joueur lequel il souhaite utiliser
 * Message d'erreur si l'utilisateur saisit une lettre incorrecte
 * @return une lettre entre F/M/D pour le niveau de difficulté associé
 */
char demande_mode();

/**
 * Le jeu de la Bataille navale
 * @param tableau_joueur
 * @param tableau_ordi
 * @param missile
 * @param bateau le tableau de bateau
 * @param NB_bateau Nombre de bateau au total
 * @param mode mode de jeu choisi par l'utilisateur
 * @param nombre_tour nombre de tour de la partie
 * @param charger
 * @return un nombre définissant si la partie est finie ou non ou doit être sauvegardé
 */
int game(Grid tableau_joueur, Grid tableau_ordi, Inventory missile, Boat bateau[], int NB_bateau,char mode,int nombre_tour, int charger);

/**
 * Vérifie parmi tous les bateaux si un ou plusieurs baetaux sont touchés
 * Prends un bateau au hasard dans le tableau et regarde ses déplacements maximum à l'horizontal ou à la vertical
 * @param tableau_ordi
 * @param tableau_joueur
 * @param bateau
 * @param NB_bateau
 * @return la structure actif avec les déplacement max du bateau choisi
 */
Actif verification_deplacement_bateau_mode_active(Grid tableau_ordi, Grid tableau_joueur, Boat bateau[],int NB_bateau);

/**
 * Déplace le bateau choisi par l'ordinateur d'une distance aléatoire en focntion de ses déplacements maximums
 * @param tableau_ordi  le tableau de l'ordinateur
 * @param tableau_joueur
 * @param bateau
 * @param NB_bateau
 * @param deplacement
 * @return La nouvelle position du bateau
 */
Boat deplacement_bateau_mode_active(Grid *tableau_ordi, Grid tableau_joueur, Boat bateau[],int NB_bateau,Actif deplacement);

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
 * @return un nombre définissant si la partie est finie ou non ou doit etre sauvegardé
 */
int load(FILE* file);

/**
 * Conditionne la victoire ou la défaite en fonction du nombre de missiles restants ou des bateaux coulés
 * @param bateau
 * @param missile
 * @param NB_bateau
 * @return un chiffre selon le resultat de la partie (Victoire, Défaite, Sauvegarde ou Pas encore finie)
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
 * @return le choix de l'utilisateur entre entre 0(Oui)/N(Non)
 */
char recommencer();



#endif //PLANCHIN_ERHART_COJOCARU_JEU_H
