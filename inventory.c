//
// Created by arnau on 27/05/2021.
//

#include <stdio.h>
#include<ctype.h>
#include "inventory.h"


Inventory demande_difficulte(){
    Inventory inventaire;
    char rep;
    printf("\n\n=======================================\nDIFFICULTE\n=======================================\n\n"
            "\nQuelle difficulte voulez-vous ?\n"
           "-Facile (F)\n"
           "-Moyen (M)\n"
           "-Difficile (D)\n");
    scanf(" %c", &rep);
    rep = toupper(rep);
    while(rep != 'F' && rep != 'M' && rep != 'D') {
        printf("Veuillez saisir une reponse valide (F/M/D):\n");
        scanf(" %c", &rep);
        rep = toupper(rep);
    }
    if(rep == 'F'){
        printf("\n===========Difficulte Facile===========\n\n"
               "Voici les missiles dont vous disposez:\n\n");
        inventaire.artillerie = 3;
        inventaire.tactique = 8;
        inventaire.bombe = 4;
        inventaire.simple = 18;
    } else if (rep == 'M'){
        printf("\n==========Difficulte Moyenne==========\n\n"
               "Voici les missiles dont vous disposez:\n\n");
        inventaire.artillerie = 2;
        inventaire.tactique = 6;
        inventaire.bombe = 2;
        inventaire.simple = 16;
    } else {
        printf("\n=========Difficulte Difficile=========\n\n"
               "Voici les missiles dont vous disposez:\n\n");
        inventaire.artillerie = 2;
        inventaire.tactique = 4;
        inventaire.bombe = 1;
        inventaire.simple = 14;
    }
    return inventaire;
}

void affichage_missile_depart(Inventory missile){

    printf("\n-Missiles d'artilleries : %d  (Le missile d'artillerie inflige des degats a tout les bateaux se situant sur la ligne et la colonne du point d'impact).\n",missile.artillerie);
    printf("-Missiles tactiques : %d  (Si le missile tactique touche un bateau, ce dernier est immediatement coule).\n",missile.tactique);
    printf("-Bombes : %d (La bombe inflige des degats sur et autour de son point d'impact, sur un rayon de 2 cases horizontalement et verticalement et 1 case diagonalement).\n",missile.bombe);
    printf("-Missiles simples : %d (Le missile simple inflige des degats sur le point d'impact uniquement).\n",missile.simple);
    printf("\n=======================================\n\n");
}

void affichage_missile(Inventory missile){
    printf("\nVoici les munitions qu'il vous reste : \n");
    printf("\n-Missiles d'artilleries : %d\n",missile.artillerie);
    printf("-Missiles tactiques : %d\n",missile.tactique);
    printf("-Bombes : %d\n",missile.bombe);
    printf("-Missiles simples : %d\n",missile.simple);
}

//  Quel missile veut-il choisir

char demande_missile(Inventory missile){
    char tir_actuel;
    int verification;
    do{
        printf("\nAvec quel missile voulez_vous tirer (A/T/B/S) ?\n");
        scanf(" %c", &tir_actuel);
        tir_actuel = toupper(tir_actuel);
        while(  tir_actuel != 'A' && tir_actuel != 'T' && tir_actuel != 'B' && tir_actuel != 'S' )
        {
            printf("Veuillez saisir une munition valide (A/T/B/S).\n");
            scanf(" %c", &tir_actuel);
            tir_actuel = toupper(tir_actuel);
        }
        verification = verification_missile(missile,tir_actuel);

    }while(verification == 1);

    return tir_actuel;
}

int verification_missile(Inventory missile, char tir_actuel){
    if (tir_actuel=='A' && missile.artillerie==0){
        printf("Vous n'avez plus de missiles d'artillerie...\n");
        return 1;
    }
    if (tir_actuel=='T' && missile.tactique==0){
        printf("Vous n'avez plus de missiles tactiques...\n");
        return 1;
    }
    if (tir_actuel=='B' && missile.bombe==0){
        printf("Vous n'avez plus de bombes...\n");
        return 1;
    }
    if (tir_actuel=='S' && missile.simple==0){
        printf("Vous n'avez plus de missiles simples...\n");
        return 1;
    }
    return 0;
}
