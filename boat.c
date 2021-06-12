//
// Created by arnau on 27/05/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include "boat.h"

Boat initialisation_bateau(int i){
    Boat bateau;
    switch(i) {
        case 0 :
            bateau.taille_bateau = 2;
            break;
        case 1 :
            bateau.taille_bateau = 3;
            break;
        case 2 :
            bateau.taille_bateau = 3;
            break;
        case 3 :
            bateau.taille_bateau = 4;
            break;
        case 4 :
            bateau.taille_bateau = 5;
            break;
    }

    return bateau;
}

void affichage_nb_bateau(Boat bateau[],int NB_bateau) {
    int i;

    for (i = 0; i < NB_bateau; i++) {
        if (bateau[i].touche == bateau[i].taille_bateau) {      // On regarde si un bateau est coulé (c'est à dire que la taille du bateau est égale au nombre de fois que le bateau a été touché
            printf("Vous avez coule un bateau de taille %d.\n", bateau[i].taille_bateau);
        } else {
            printf("-Bateau de taille %d | Nombre de cases touchees = %d\n\n", bateau[i].taille_bateau, bateau[i].touche);
        }
    }
}
/*int bateau_T2 = 0, bateau_T3 = 0, bateau_T4 = 0, bateau_T5 = 0;
    for (i = 0; i < NB_bateau; i++) {
        if (bateau[i].taille_bateau == 2 && bateau[i].touche != bateau[i].taille_bateau) {
            bateau_T2++;
        } else if (bateau[i].taille_bateau == 3 && bateau[i].touche != bateau[i].taille_bateau) {
            bateau_T3++;
        } else if (bateau[i].taille_bateau == 4 && bateau[i].touche != bateau[i].taille_bateau) {
            bateau_T4++;
        } else if (bateau[i].taille_bateau == 5 && bateau[i].touche != bateau[i].taille_bateau) {
            bateau_T5++;
        }
    }*/
/* printf("-Bateaux taille 2 : %d ; nombre de cases touchees : %d\n", bateau_T2, bateau[0].touche);
 printf("-Bateaux taille 3 : %d ; nombre de cases touchees 1er bateau : %d ; nombre de cases touchees 2eme bateau : %d\n",bateau_T3, bateau[1].touche, bateau[2].touche);
 printf("-Bateaux taille 4 : %d ; nombre de cases touchees : %d\n", bateau_T4, bateau[3].touche);
 printf("-Bateaux taille 5 : %d ; nombre de cases touchees : %d\n", bateau_T5, bateau[4].touche);
 printf("\n=======================================\n\n");*/


Boat placement_bateau(Grid tableau_ordi, Boat bateau[], int i){

    switch(i) {
        case 0 :
            if (bateau[i].H_V == 0){
                bateau[i] = position_bateau_horizontal(tableau_ordi,bateau[i]);
            }else{
                bateau[i] = position_bateau_vertical(tableau_ordi,bateau[i]);
            }
            break;

        case 1 :
            if (bateau[i].H_V == 0){
                bateau[i] = position_bateau_horizontal(tableau_ordi,bateau[i]);
            }else{
                bateau[i] = position_bateau_vertical(tableau_ordi,bateau[i]);
            }
            break;

        case 2 :
            if (bateau[i].H_V == 0){
                bateau[i] = position_bateau_horizontal(tableau_ordi,bateau[i]);
            }else{
                bateau[i] = position_bateau_vertical(tableau_ordi,bateau[i]);
            }
            break;

        case 3 :
            if (bateau[i].H_V == 0){
                bateau[i] = position_bateau_horizontal(tableau_ordi,bateau[i]);
            }else{
                bateau[i] = position_bateau_vertical(tableau_ordi,bateau[i]);
            }
            break;

        case 4 :
            if (bateau[i].H_V == 0){
                bateau[i] = position_bateau_horizontal(tableau_ordi,bateau[i]);
            }else{
                bateau[i] = position_bateau_vertical(tableau_ordi,bateau[i]);
            }
    }

    return bateau[i];
}

Boat position_bateau_vertical(Grid tableau_ordi,Boat bateau)
{
    do{
        bateau.ligne = rand() % (10-bateau.taille_bateau);
        bateau.colonne = rand() % 10;
    }while(collision_verticale(tableau_ordi,bateau)==1);    // On répète tant qu'il y une collison avec un autre bateau
    return bateau;
}

int collision_verticale(Grid tableau_ordi,Boat bateau)
{
    int i;
    for (i=0;i<bateau.taille_bateau;i++){
        if (tableau_ordi.grille[1+bateau.ligne+i][1+bateau.colonne] != ' '){    // On vérifie horizontalement si il y a un bateau coupant le bateau qui va être positionné
            return 1;
        }
    }
    return 0;
}

Boat position_bateau_horizontal(Grid tableau_ordi, Boat bateau)
{
    do{
        bateau.ligne = rand() % 10;
        bateau.colonne = rand() % (10-bateau.taille_bateau);
    }while(collision_horizontale(tableau_ordi,bateau)==1);  // On répète tant qu'il y une collison avec un autre bateau
    return bateau;
}

int collision_horizontale(Grid tableau_ordi,Boat bateau){
    int i;
    for (i=0;i<bateau.taille_bateau;i++){
        if (tableau_ordi.grille[1+bateau.ligne][1+bateau.colonne+i] != ' '){    // On vérifie horizontalement si il y a un bateau coupant le bateau qui va être positionné
            return 1;
        }
    }
    return 0;
}


