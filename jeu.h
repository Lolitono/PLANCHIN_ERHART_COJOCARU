//
// Created by arnau on 27/05/2021.
//

#ifndef PLANCHIN_ERHART_COJOCARU_JEU_H
#define PLANCHIN_ERHART_COJOCARU_JEU_H

typedef struct {
    int decision;                   // Un nombre choisi aléatoirement par l'ordinateur afin de savoir s'il veut bouger un bateau
    char tableau_active[6];         /* Liste des bateaux pouvant se déplacer prenant sur chaque case soit la lettre du bateau si celui-ci peut se déplacer,
                                    soit un espace si il ne peut pas se déplacer */
    int verification_mode_active;   // nombre de bateau ne pouvant pas se déplacer
    int choix_bateau;               // Bateau choisi parmi les bateaux pouvant se déplacer
    int max_gauche;                 // Déplacement maximal vers la gauche du bateau choisi
    int max_droite;                 // Déplacement maximal vers la droite du bateau choisi
    int max_haut;                   // Déplacement maximal vers le haut du bateau choisi
    int max_bas;                    // Déplacement maximal vers le bas du bateau choisi
    int mouvement_bateau;           // Déplacement du bateau choisi
}Actif;

#include "grille.h"
#include "inventory.h"
#include "boat.h"
#include "sauvegarde.h"


/**
 * Affiche le menu avec les trois choix (Démarrer, Charger, Quitter)
 * Le choix "Charger" ne s'affiche pas si il y a aucune partie dans la sauvegarde
 * Message d'erreur si l'utilisateur saisit une lettre incorrecte (en fonction des choix possibles)
 * @param file Le fichier de sauvegarde
 * @return Une lettre entre D/C/Q en fonction du choix de l'utilisateur
 */
char menu(FILE * file);


/**
 * Affiche les modes disponibles et demande au joueur lequel il souhaite utiliser
 * Message d'erreur si l'utilisateur saisit une lettre incorrecte
 * @return Le mode de jeu choisi par l'utilisateur (C/B/A)
 */
char demande_mode();


/**
 * Demande à l'utilisateur de choisir la difficulté du jeu
 * @return La réponse de l'utilisateur
 */
char demande_difficulte();


/**
 * Affiche le nombre de tour
 * Affiche le nombre de missiles en fonction du nombre qu'il en reste
 * Affiche le nombre de bateaux au début de chaque tour
 * Affiche le tableau joueur si on est en mode Classique ou Active
 * Fait choisir à l'ordinateur s'il déplace un bateau avec vérification pour le mode Active
 * Demande en quelle case l'utilisateur veut tirer
 * Enlève les missiles utilisés dans l'inventaire
 * Tire un missile et montre le tableau avec les changements (bateau touché ou non)
 * Demande à l'utilisateur s'il veut sauvegarder ou continuer à la fin de chaque tour
 * Ouvre un fichier "sauvegarde_jeu.txt" si l'utilisateur choisi de sauvegarder
 * @param tableau_joueur Le tableau de l'utilisateur
 * @param tableau_ordi Le tableau de l'ordinateur
 * @param missile L'inventaire des missiles possédés par l'utilisateur
 * @param bateau Le tableau de bateau
 * @param NB_bateau Le nombre de bateau au total (5)
 * @param mode Le mode de jeu choisi par l'utilisateur
 * @param nombre_tour Le nombre de tour de la partie
 * @param charger Un nombre entre 0 et 1 (0 = partie non chargée, 1 = partie chargée)
 * @return Un nombre définissant si la partie est finie ou non ou doit être sauvegardé
 */
int game(Grid tableau_joueur, Grid tableau_ordi, Inventory missile, Boat bateau[], int NB_bateau,char mode,int nombre_tour, int charger);


/**
 * Demande où l'utilisateur veut tirer
 * Message d'erreur si l'utilisateur tire sur une case inconnue ou s'il tire sur une case déjà touchée
 * @param tableau_joueur Le tableau de l'utilisateur
 * @return Le point d'impact du missile tiré
 */
Impact saisie_tir(Grid tableau_joueur);


/**
 * Vérifie parmi tous les bateaux si un ou plusieurs bateaux sont touchés
 * Prends un bateau au hasard dans le tableau et regarde ses déplacements maximum à l'horizontal ou à la vertical
 * @param tableau_ordi Le tableau de l'ordinateur
 * @param tableau_joueur Le tableau de l'utilisateur
 * @param bateau Le tableau de bateau
 * @param NB_bateau Le nombre de bateau au total (5)
 * @return La structure Actif avec les déplacements max du bateau choisi
 */
Actif verification_deplacement_bateau_mode_active(Grid tableau_ordi, Grid tableau_joueur, Boat bateau[],int NB_bateau);


/**
 * Déplace le bateau choisi par l'ordinateur d'une distance aléatoire en fonction de ses déplacements maximums
 * @param tableau_ordi Le tableau de l'ordinateur
 * @param bateau Le tableau de bateau
 * @param deplacement La structure Actif avec les déplacements max du bateau choisi
 * @return La nouvelle position du bateau
 */
Boat deplacement_bateau_mode_active(Grid *tableau_ordi, Boat bateau[],Actif deplacement);


/**
 * Conditionne la victoire ou la défaite en fonction du nombre de missiles restants ou des bateaux coulés
 * @param bateau Le tableau de bateau
 * @param missile L'inventaire des missiles possédés par l'utilisateur
 * @param NB_bateau Le nombre de bateau au total (5)
 * @return Un chiffre selon le resultat de la partie (1 ou 2 = Victoire, 3 = Défaite ou 0 = Pas encore finie)
 */
int fin_partie(Boat bateau[],Inventory missile,int NB_bateau);


/**
 * Affiche le résultat de la partie (Victoire, Défaite ou Sauvegarde)
 * @param partie Le chiffre signifiant le résultat de la partie (1 = partie gagnée, 2 = partie gagnée de peu, 3 = partie perdue)
 */
void partie_finie(int partie);


/**
 * Demande à l'utilisateur si il souhaite recommencer une partie
 * Message d'erreur si l'utilisateur saisit une lettre incorrecte
 * @return Le choix de l'utilisateur entre entre 0(Oui)/N(Non)
 */
char recommencer();


#endif //PLANCHIN_ERHART_COJOCARU_JEU_H
