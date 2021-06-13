//
// Created by arnau on 27/05/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include "boat.h"

Boat initialisation_bateau(int i,Boat bateau[]){

    switch(i) {                                                       // On donne la taille de chaque bateau
        case 0 :
            bateau[i].taille_bateau = 2;
            break;
        case 1 :
            bateau[i].taille_bateau = 3;
            break;
        case 2 :
            bateau[i].taille_bateau = 3;
            break;
        case 3 :
            bateau[i].taille_bateau = 4;
            break;
        case 4 :
            bateau[i].taille_bateau = 5;
            break;
    }
    bateau[i].touche = 0;                                           // Initialement aucun bateau n'est touché
    bateau[i].H_V = rand() % 2;                                     // 0 = horizontal, 1 = vertical
    bateau[i].identification = 'A' + i;                             // Lettre permettant d'identifier chaque bateau
    return bateau[i];
}


Boat placement_bateau(Grid tableau_ordi, Boat bateau[], int i){

    if (bateau[i].H_V == 0){                                            // Si la variable H_V pour un bateau i=0
        bateau[i] = position_bateau_horizontal(tableau_ordi,bateau[i]); // Le bateau i sera horizontal
    }else{                                                              // Si cette variable est différente de 0
        bateau[i] = position_bateau_vertical(tableau_ordi,bateau[i]);   // Le bateau i sera vertical
    }

    return bateau[i];
}


Boat position_bateau_horizontal(Grid tableau_ordi, Boat bateau)
{
    do{
        bateau.ligne = rand() % 10;                             // Le bateau commence à une ligne aléatoire entre 0 et 9
        bateau.colonne = rand() % (10-bateau.taille_bateau);    // Le bateau commence à une colonne aléatoire entre A et J
    }while(collision_horizontale(tableau_ordi,bateau)==1);      // On répète tant qu'il y une collison avec un autre bateau
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


Boat position_bateau_vertical(Grid tableau_ordi,Boat bateau)
{
    do{
        bateau.ligne = rand() % (10-bateau.taille_bateau);  // Le bateau commence à une ligne aléatoire entre 0 et 9 - la taille du bateau
        bateau.colonne = rand() % 10;                       // Le bateau commence à une colonne aléatoire entre A et J
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


void affichage_nb_bateau(Boat bateau[],int NB_bateau) {
    int i;

    for (i = 0; i < NB_bateau; i++) {
        if (bateau[i].touche == bateau[i].taille_bateau) {      // On regarde si un bateau est coulé (c'est à dire que la taille du bateau est égale au nombre de fois que le bateau a été touché)
            printf("Vous avez coule un bateau de taille %d.\n", bateau[i].taille_bateau);
        } else {
            printf("-Bateau de taille %d | Nombre de cases touchees = %d\n\n", bateau[i].taille_bateau, bateau[i].touche);
        }
    }
}




