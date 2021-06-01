//
// Created by arnau on 27/05/2021.
//

#ifndef PLANCHIN_ERHART_COJOCARU_JEU_H
#define PLANCHIN_ERHART_COJOCARU_JEU_H

#include "grille.h"
#include "inventory.h"
#include "boat.h"

int menu();

char demande_mode();

int game(Grid tableau_joueur, Grid tableau_ordi, Inventory missile, Boat bateau[], int NB_bateau,char mode,int nombre_tour);

void partie_finie(int partie);

char recommencer();

void ecriture_sauvegarde(FILE* file, Grid tableau_joueur, Grid tableau_ordi, Inventory missile, Boat bateau[], int NB_bateau, int nombre_tour, char mode);

int charger_partie(FILE* file);

#endif //PLANCHIN_ERHART_COJOCARU_JEU_H
