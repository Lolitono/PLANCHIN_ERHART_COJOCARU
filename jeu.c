//
// Created by arnau on 27/05/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "jeu.h"

int menu(){
    int demarrer;
    printf("\n\n=======================================\nMENU\n=======================================\n\n"
           "Que voulez vous faire : \n"
           "-Demarrer une nouvelle partie (1)\n"
           "-Charger votre derniere partie (2)\n"
           "-Quitter (3)\n\n");
    scanf(" %d", &demarrer);
    while(demarrer < 1 || demarrer > 3) {
        printf("Veuillez saisir une reponse valide (1/2/3):\n");
        scanf(" %d", &demarrer);
    }

    return demarrer;
}

char demande_mode(){
    char mode;
    printf("\n\n=======================================\nMODE\n=======================================\n\n"
            "Quel mode voulez-vous : \n"
           "-Classique (C)\n"
           "-Blind (B)\n"
           "-Active (A)\n");
    scanf(" %c", &mode);
    mode = toupper(mode);
    while(mode != 'C' && mode != 'B' && mode != 'A') {
        printf("Veuillez saisir une reponse valide (C/B/A):\n");
        scanf(" %c", &mode);
        mode = toupper(mode);
    }
    return mode;
}

int game(Grid tableau_joueur, Grid tableau_ordi, Inventory missile, Boat bateau[], int NB_bateau, char mode, int nombre_tour){
    int i,j,k,partie;
    char missile_utilise,sauvegarde;

    Impact point_impact;

    do {
        nombre_tour++;
        printf("\n\n=======================================\nTOUR %d\n=======================================\n\n",
               nombre_tour);
        if(mode=='C' || mode =='A' || (mode == 'B' && nombre_tour ==1)){
            affichage_tableau(tableau_joueur);
        }
        missile_utilise = demande_missile(missile);
        point_impact = demande_tir(tableau_joueur);
        printf("Le missile tombera en %c%d.\n\n", 'A' + point_impact.colonne, point_impact.ligne);
        if (missile_utilise == 'A') {
            missile.artillerie = missile.artillerie - 1;
            tableau_joueur = tir_artillerie(tableau_joueur, tableau_ordi, point_impact, NB_bateau, bateau);

            for (i = 0; i < NB_bateau; i++) {
                for (k = 1; k < 11; k++) {
                    if (tableau_ordi.grille[k][1 + point_impact.colonne] == bateau[i].identification &&
                        tableau_joueur.grille[k][1 + point_impact.colonne] == 'X') {
                        bateau[i].touche++;
                        tableau_ordi.grille[k][1 + point_impact.colonne] = ' ';
                        if(mode =='B'){
                            printf("Un bateau a ete touche en %c%d.\n",'A' + point_impact.colonne,k-1);
                        }
                    }
                }
                for (j = 1; j < 11; j++) {
                    if (tableau_ordi.grille[point_impact.ligne + 1][j] == bateau[i].identification &&
                        tableau_joueur.grille[point_impact.ligne + 1][j] == 'X') {
                        bateau[i].touche++;
                        tableau_ordi.grille[point_impact.ligne + 1][j] = ' ';
                        if(mode =='B'){
                            printf("Un bateau a ete touche en %c%d.\n",'A' + j-1,point_impact.ligne);
                        }
                    }
                }
            }

        } else if (missile_utilise == 'T') {

            missile.tactique = missile.tactique - 1;
            tableau_joueur = tir_tactique(tableau_joueur, tableau_ordi, point_impact);
            for (i = 0; i < NB_bateau; i++) {
                if (tableau_ordi.grille[1 + point_impact.ligne][1 + point_impact.colonne] ==
                    bateau[i].identification &&
                    tableau_joueur.grille[1 + point_impact.ligne][1 + point_impact.colonne] == 'X') {
                    for (k = 1; k < 11; k++) {
                        for (j = 1; j < 11; j++) {
                            if (tableau_ordi.grille[k][j] == bateau[i].identification) {
                                tableau_joueur.grille[k][j] = 'X';
                                tableau_ordi.grille[k][j] = ' ';
                                if(mode =='B'){
                                    printf("Un bateau a ete touche en %c%d.\n",'A' + j -1,k-1);
                                }
                            }
                        }
                    }
                    bateau[i].touche = bateau[i].taille_bateau;
                }
            }
        } else if (missile_utilise == 'B') {

            missile.bombe = missile.bombe - 1;
            tableau_joueur = tir_bombe(tableau_joueur, tableau_ordi, point_impact, NB_bateau, bateau);
            for (i = 0; i < NB_bateau; i++) {
                for (k = -1; k < 4; k++) {
                    if (tableau_ordi.grille[point_impact.ligne + k][1 + point_impact.colonne] ==
                        bateau[i].identification &&
                        tableau_joueur.grille[point_impact.ligne + k][1 + point_impact.colonne] == 'X') {
                        bateau[i].touche++;
                        tableau_ordi.grille[point_impact.ligne + k][1 + point_impact.colonne] = ' ';
                        if(mode =='B'){
                            printf("Un bateau a ete touche en %c%d.\n",'A' + point_impact.colonne ,point_impact.ligne + k -1);
                        }
                    }
                }
                for (j = -1; j < 4; j++) {
                    if (tableau_ordi.grille[point_impact.ligne + 1][point_impact.colonne + j] ==
                        bateau[i].identification &&
                        tableau_joueur.grille[point_impact.ligne + 1][point_impact.colonne + j] == 'X') {
                        bateau[i].touche++;
                        tableau_ordi.grille[point_impact.ligne + 1][point_impact.colonne + j] = ' ';
                        if(mode =='B'){
                            printf("Un bateau a ete touche en %c%d.\n",'A' + point_impact.colonne + j -1 ,point_impact.ligne);
                        }
                    }
                }
            }
            for (j = 0; j < 3; j = j + 2) {
                for (k = 0; k < 3; k = k + 2) {
                    for (i = 0; i < NB_bateau; i++) {
                        if (tableau_ordi.grille[point_impact.ligne + j][point_impact.colonne + k] ==
                            bateau[i].identification &&
                            tableau_joueur.grille[point_impact.ligne + j][point_impact.colonne + k] == 'X') {
                            bateau[i].touche++;
                            tableau_ordi.grille[point_impact.ligne + j][point_impact.colonne + k] = ' ';
                            if(mode =='B'){
                                printf("Un bateau a ete touche en %c%d.\n",'A' + point_impact.colonne + k -1,point_impact.ligne + j-1);
                            }
                        }
                    }
                }
            }

        } else {

            missile.simple = missile.simple - 1;
            tableau_joueur = tir_simple(tableau_joueur, tableau_ordi, point_impact);
            for (i = 0; i < NB_bateau; i++) {
                if (tableau_ordi.grille[1 + point_impact.ligne][1 + point_impact.colonne] ==
                    bateau[i].identification &&
                    tableau_joueur.grille[1 + point_impact.ligne][1 + point_impact.colonne] == 'X') {
                    bateau[i].touche++;
                    tableau_ordi.grille[1 + point_impact.ligne][1 + point_impact.colonne] = ' ';
                    if(mode =='B'){
                        printf("Un bateau a ete touche en %c%d.\n",'A' + point_impact.colonne,point_impact.ligne);
                    }
                }
            }
        }

        partie = fin_partie(bateau, missile, NB_bateau);
        printf("\nVoici le nombre de bateaux qu'il vous reste a detruire:\n\n");
        affichage_nb_bateau(bateau, NB_bateau);
        affichage_missile(missile);

        printf("Voulez continuer ou sauvegarder et quitter (C/S)?\n");
        scanf(" %c",&sauvegarde);
        sauvegarde = toupper(sauvegarde);
        while(sauvegarde != 'C' && sauvegarde != 'S')
        {
            printf("Veuillez saisir C pour continuer ou S pour sauvegarder.\n");
            scanf(" %c",&sauvegarde);
            sauvegarde = toupper(sauvegarde);
        }
        if(sauvegarde == 'S')
        {
            FILE *file = fopen("sauvegarde_jeu.txt","w");
            ecriture_sauvegarde(file,tableau_joueur,tableau_ordi,missile,bateau,NB_bateau,nombre_tour,mode);
            fclose(file);
            partie = 4;
        }

    } while (partie == 0);
    affichage_tableau(tableau_joueur);

    return partie;
}

void ecriture_sauvegarde(FILE* file, Grid tableau_joueur, Grid tableau_ordi, Inventory missile, Boat bateau[], int NB_bateau, int nombre_tour, char mode){
    int i,j;
    rewind(file);
    fprintf(file,"%d\n",NB_bateau);
    fprintf(file,"%d\n",nombre_tour);
    fprintf(file,"%c\n",mode);

    fprintf(file,"%d\n",missile.artillerie);
    fprintf(file,"%d\n",missile.tactique);
    fprintf(file,"%d\n",missile.bombe);
    fprintf(file,"%d\n",missile.simple);

    for(i=0;i<NB_bateau;i++){
        fprintf(file,"%d\n",bateau[i].taille_bateau);
        fprintf(file,"%d\n",bateau[i].ligne);
        fprintf(file,"%d\n",bateau[i].colonne);
        fprintf(file,"%d\n",bateau[i].H_V);
        fprintf(file,"%d\n",bateau[i].touche);
        fprintf(file,"%c\n",bateau[i].identification);
    }



    for(i=0;i<tableau_joueur.hauteur;i++){
        for(j=0;j<tableau_joueur.largeur;j++) {
            fprintf(file,"%c",tableau_joueur.grille[i][j]);
        }
        fprintf(file,"\n");
    }
    for(i=0;i<tableau_ordi.hauteur;i++){
        for(j=0;j<tableau_ordi.largeur;j++) {
            fprintf(file,"%c",tableau_ordi.grille[i][j]);
        }
        fprintf(file,"\n");
    }
}

int charger_partie(FILE* file){
    int i, nombre_tour,NB_bateau,partie;
    Grid tableau_joueur;
    Grid tableau_ordi;
    Inventory missile;
    char mode,*identification;
    tableau_ordi.hauteur = 12;
    tableau_ordi.largeur = 12;
    tableau_joueur.hauteur = 12;
    tableau_joueur.largeur = 12;
    rewind(file);
    char temp[20]={0};

    fgets(temp, 20, file);
    NB_bateau = atoi(temp);
    fgets(temp, 20, file);
    nombre_tour = atoi(temp);
    fgets(mode, 1, file);
    Boat bateau[NB_bateau];

    //while(i<tableau_joueur.hauteur && )


    fgets(temp, 20, file);
    missile.artillerie = atoi(temp);
    fgets(temp, 20, file);
    missile.tactique = atoi(temp);
    fgets(temp, 20, file);
    missile.bombe = atoi(temp);
    fgets(temp, 20, file);
    missile.simple = atoi(temp);


    for(i=0;i<NB_bateau;i++){
        fgets(temp, 20, file);
        bateau[i].taille_bateau = atoi(temp);
        fgets(temp, 20, file);
        bateau[i].ligne = atoi(temp);
        fgets(temp, 20, file);
        bateau[i].colonne = atoi(temp);
        fgets(temp, 20, file);
        bateau[i].H_V = atoi(temp);
        fgets(temp, 20, file);
        bateau[i].touche = atoi(temp);
        fgets(identification, 1, file);
        bateau[i].identification=*identification;
    }


    for(i=0;i<tableau_joueur.hauteur;i++){
        fgets(tableau_joueur.grille[i], 12, file);
    }
    for(i=0;i<tableau_ordi.hauteur;i++){
        fgets(tableau_ordi.grille[i], 12, file);
    }
    fclose(file);
    partie = game(tableau_joueur, tableau_ordi, missile, bateau, NB_bateau, mode, nombre_tour);
    return partie;
}

void partie_finie(int partie) {

    if (partie == 1) {
        printf("\nFelicitations ! Vous avez gagne la partie, Bravo !\n\n");
    } else if (partie == 2) {
        printf("\nVous avez gagne la partie de peu, Bravo !\n\n");
    } else if (partie == 3){
        printf("\nDommage ! Vous avez perdu la partie...\n\n");
    } else {
        printf("\nVotre partie a bien ete sauvegardee !\n\n");
    }
}

char recommencer()
{
    char rejouer;
    printf("Voulez vous rejouer? (O/N)\n");
    scanf(" %c", &rejouer);
    while(rejouer != 'O' && rejouer != 'N')
    {
        printf("Veuillez saisir une reponse valide (O/N).\n");
        scanf(" %c", &rejouer);
    }
    return rejouer;
}
