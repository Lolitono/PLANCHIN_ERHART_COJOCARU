//
// Created by arnau on 27/05/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "jeu.h"

char menu(FILE * file){
    char demarrer;
    int charger;
    char temp[5];


    rewind(file);
    fgets(temp, 20, file);
    charger = atoi(temp);

    printf("\n\n=======================================\nMENU\n=======================================\n\n"
           "Que voulez vous faire : \n"
           "-Demarrer une nouvelle partie (D)\n");
    if(charger == 1){
        printf("-Charger votre derniere partie (C)\n");
    }
    printf("-Quitter (Q)\n\n");
    scanf(" %c", &demarrer);
    demarrer = toupper(demarrer);
    if(charger == 0){
        while(demarrer != 'D' && demarrer != 'Q') {
            printf("Veuillez saisir une reponse valide (D/Q):\n");
            scanf(" %c", &demarrer);
            demarrer = toupper(demarrer);
        }
    } else {
        while(demarrer != 'D' && demarrer != 'Q' && demarrer != 'C') {
            printf("Veuillez saisir une reponse valide (D/C/Q):\n");
            scanf(" %c", &demarrer);
            demarrer = toupper(demarrer);
        }
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

int game(Grid tableau_joueur, Grid tableau_ordi, Inventory missile, Boat bateau[], int NB_bateau, char mode, int nombre_tour, int charger){
    int i,j,k,partie,verification;
    char missile_utilise,sauvegarde;
    char temp[5];
    int deplacement_actif;



    Impact point_impact;

    if (nombre_tour == 1) {
        affichage_missile_depart(missile);
        printf("Voici le nombre de bateaux que l'ordinateur va placer aleatoirement:\n\n");
        affichage_nb_bateau(bateau, NB_bateau);
        affichage_tableau(tableau_joueur);
    } else if(charger == 1){
        if(mode == 'C'){
            printf("Vous jouez en mode Classique.\n");
        } else if(mode == 'B'){
            printf("Vous jouez en mode Blind.\n");
        } else {
            printf("Vous jouez en mode Active.\n");
        }

        printf("\nVoici le nombre de bateaux qu'il vous reste a detruire:\n\n");
        affichage_nb_bateau(bateau, NB_bateau);
        affichage_missile(missile);
        if (mode == 'C' || mode == 'A') {
            affichage_tableau(tableau_joueur);
        //    affichage_tableau(tableau_ordi);
        }
    }
    do {
        printf("\n\n=======================================\nTOUR %d\n=======================================\n\n",
               nombre_tour);


        char ecraser[5]={0};
        char quitter[5]={0};



        if(nombre_tour!=1 && mode=='A') {

            deplacement_actif = rand()%3;
            if(deplacement_actif != 0) {
                deplacement_bateau_mode_active(&tableau_ordi,tableau_joueur, &bateau ,NB_bateau);

            }
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
                        if (mode == 'B') {
                            printf("Un bateau a ete touche en %c%d.\n", 'A' + point_impact.colonne, k - 1);
                        }
                    }
                }
                for (j = 1; j < 11; j++) {
                    if (tableau_ordi.grille[point_impact.ligne + 1][j] == bateau[i].identification &&
                        tableau_joueur.grille[point_impact.ligne + 1][j] == 'X') {
                        bateau[i].touche++;
                        tableau_ordi.grille[point_impact.ligne + 1][j] = ' ';
                        if (mode == 'B') {
                            printf("Un bateau a ete touche en %c%d.\n", 'A' + j - 1, point_impact.ligne);
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
                                if (mode == 'B') {
                                    printf("Un bateau a ete touche en %c%d.\n", 'A' + j - 1, k - 1);
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
                        if (mode == 'B') {
                            printf("Un bateau a ete touche en %c%d.\n", 'A' + point_impact.colonne,
                                   point_impact.ligne + k - 1);
                        }
                    }
                }
                for (j = -1; j < 4; j++) {
                    if (tableau_ordi.grille[point_impact.ligne + 1][point_impact.colonne + j] ==
                        bateau[i].identification &&
                        tableau_joueur.grille[point_impact.ligne + 1][point_impact.colonne + j] == 'X') {
                        bateau[i].touche++;
                        tableau_ordi.grille[point_impact.ligne + 1][point_impact.colonne + j] = ' ';
                        if (mode == 'B') {
                            printf("Un bateau a ete touche en %c%d.\n", 'A' + point_impact.colonne + j - 1,
                                   point_impact.ligne);
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
                            if (mode == 'B') {
                                printf("Un bateau a ete touche en %c%d.\n", 'A' + point_impact.colonne + k - 1,
                                       point_impact.ligne + j - 1);
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
                    if (mode == 'B') {
                        printf("Un bateau a ete touche en %c%d.\n", 'A' + point_impact.colonne, point_impact.ligne);
                    }
                }
            }
        }
        nombre_tour++;
        partie = fin_partie(bateau, missile, NB_bateau);

        if (partie==0){
            printf("\nVoici le nombre de bateaux qu'il vous reste a detruire:\n\n");
            affichage_nb_bateau(bateau, NB_bateau);
            affichage_missile(missile);
            if (mode == 'C' || mode == 'A') {
                affichage_tableau(tableau_joueur);
                printf("\n");
                //affichage_tableau(tableau_ordi);
            }
            printf("\nVoulez continuer ou sauvegarder et quitter (C/S)?\n");
            scanf(" %c", &sauvegarde);
            sauvegarde = toupper(sauvegarde);
            while (sauvegarde != 'C' && sauvegarde != 'S') {
                printf("\nVeuillez saisir C pour continuer ou S pour sauvegarder.\n");
                scanf(" %c", &sauvegarde);
                sauvegarde = toupper(sauvegarde);
            }
            if (sauvegarde == 'S') {
                FILE *file = fopen("sauvegarde_jeu.txt", "r");
                rewind(file);
                fgets(temp,5,file);
                verification=atoi(temp);
                fclose(file);
                if(verification == 0){
                    file = fopen("sauvegarde_jeu.txt", "w");
                    save(file, tableau_joueur, tableau_ordi, missile, bateau, NB_bateau, nombre_tour, mode);
                    fclose(file);
                    partie = 4;
                } else {
                    printf("Si vous enregistrez cette partie, la derniere sauvegarde sera ecrasee. Etes-vous sur de vouloir sauvegarder (OUI/NON)\n");
                    fflush(stdin);
                    gets(ecraser);
                    for (i=0;i<5;i++){
                        ecraser[i] = toupper(ecraser[i]);
                    }

                    while(strcmp(ecraser,"OUI")!=0 && strcmp(ecraser,"NON")!=0)
                    {
                        printf("Veuillez saisir un mot valide (OUI/NON)\n");
                        fflush(stdin);
                        gets(ecraser);
                        for (i=0;i<5;i++){
                            ecraser[i] = toupper(ecraser[i]);
                        }
                    }
                    if(strcmp(ecraser,"OUI")==0){
                        file = fopen("sauvegarde_jeu.txt", "w");
                        save(file, tableau_joueur, tableau_ordi, missile, bateau, NB_bateau, nombre_tour, mode);
                        fclose(file);
                        partie = 4;
                    } else {
                        printf("Voulez-vous quitter? (OUI/NON)\n");
                        fflush(stdin);
                        gets(quitter);
                        for (i=0;i<5;i++){
                            quitter[i] = toupper(quitter[i]);
                        }

                        while(strcmp(quitter,"OUI")!=0 && strcmp(quitter,"NON")!=0)
                        {
                            printf("Veuillez saisir un mot valide (OUI/NON)\n");
                            fflush(stdin);
                            gets(quitter);
                            for (i=0;i<5;i++){
                                quitter[i] = toupper(quitter[i]);
                            }
                        }
                        if (strcmp(quitter,"OUI")==0){
                            partie = 5;
                        }
                    }
                }
            }
        }

    } while (partie == 0);
    if (partie<=3) {
        affichage_tableau(tableau_joueur);
    }
    return partie;
}

void deplacement_bateau_mode_active(Grid *tableau_ordi, Grid tableau_joueur, Boat *(bateau[]), int NB_bateau){

    int i,j;
    char tableau_active[6]={0};
    int verification_active,deplacement_actif;
    int choix_bateau;
    int deplacement_max_gauche ,deplacement_max_droite, deplacement_max_haut, deplacement_max_bas;

    int deplacement;


    verification_active = 0;
    for (i = 0; i < NB_bateau; i++) {
        if (bateau[i]->touche == 0) {
            tableau_active[i] = bateau[i]->identification;
        } else {
            tableau_active[i] = ' ';
            verification_active++;
        }
    }
    tableau_active[i] = '\0';
    //printf("%s", tableau_active);

    if (verification_active != 5) {

        do {
            do {
                choix_bateau = rand() % 5;
            } while (tableau_active[choix_bateau] == ' '); // Choix bateau aleatoire non touché

            //printf("bateau choisie : %c, H_V = %d", bateau[choix_bateau].identification,bateau[choix_bateau].H_V);
            deplacement_max_gauche = 0;
            deplacement_max_droite = 0;
            deplacement_max_haut = 0;
            deplacement_max_bas = 0;
            i = 1;
            j = 0;
            if (bateau[choix_bateau]->H_V == 0) { // si le bateau est horizontal
                do {
                    if (tableau_joueur.grille[bateau[choix_bateau]->ligne + 1][bateau[choix_bateau]->colonne -
                                                                              i +
                                                                              1] == '_' &&
                        tableau_ordi->grille[bateau[choix_bateau]->ligne + 1][bateau[choix_bateau]->colonne -
                                                                            i +
                                                                            1] ==
                        ' ') // si la case directement à gauche du bateau// n'a pas été touché et ne contient pas un autre bateau{
                    {
                        deplacement_max_gauche++;
                    }
                    i++;
                } while (i < 4 && deplacement_max_gauche + 1 == i);
                //printf("deplacement max gauche : %d", deplacement_max_gauche);

                do {
                    if (tableau_joueur.grille[bateau[choix_bateau]->ligne + 1][bateau[choix_bateau]->colonne +
                                                                              bateau[choix_bateau]->taille_bateau +
                                                                              j + 1] == '_' &&
                        tableau_ordi->grille[bateau[choix_bateau]->ligne + 1][bateau[choix_bateau]->colonne +
                                                                            bateau[choix_bateau]->taille_bateau +
                                                                            j + 1] == ' ') {
                        deplacement_max_droite++;
                    }
                    j++;
                } while (j < 3 && deplacement_max_droite == j);
                //printf("deplacement max droite : %d", deplacement_max_droite);

            } else {

                do {
                    if (tableau_joueur.grille[bateau[choix_bateau]->ligne - i + 1][
                                bateau[choix_bateau]->colonne +
                                1] == '_' &&
                        tableau_ordi->grille[bateau[choix_bateau]->ligne - i + 1][
                                bateau[choix_bateau]->colonne +
                                1] == ' ') {
                        deplacement_max_haut++;
                    }
                    i++;
                } while (i < 4 && deplacement_max_haut + 1 == i);
                //printf("deplacement max haut : %d", deplacement_max_haut);

                do {
                    if (tableau_joueur.grille[bateau[choix_bateau]->ligne +
                                              bateau[choix_bateau]->taille_bateau +
                                              j + 1][bateau[choix_bateau]->colonne + 1] == '_' &&
                        tableau_ordi->grille[bateau[choix_bateau]->ligne +
                                            bateau[choix_bateau]->taille_bateau +
                                            j + 1][bateau[choix_bateau]->colonne + 1] == ' ') {
                        deplacement_max_bas++;
                    }
                    j++;
                } while (j < 3 && deplacement_max_bas == j);
                //printf("deplacement max bas : %d", deplacement_max_bas);

            }


            if (deplacement_max_droite == 0 && deplacement_max_gauche == 0 && deplacement_max_bas == 0 &&
                deplacement_max_haut == 0) {
                tableau_active[choix_bateau] = ' ';
                verification_active++;
            }

        } while (tableau_active[choix_bateau] == ' ' && verification_active != 5);


        if (tableau_active[choix_bateau] == bateau[choix_bateau]->identification &&
            verification_active != 5) {

            if (bateau[choix_bateau]->H_V == 0) {
                deplacement = rand() % (deplacement_max_gauche + deplacement_max_droite) + 1;
                if (deplacement <= deplacement_max_gauche) {
                    for (i = 1; i < (deplacement + 1); i++) {
                        tableau_ordi->grille[bateau[choix_bateau]->ligne + 1][bateau[choix_bateau]->colonne +
                                                                            bateau[choix_bateau]->taille_bateau -
                                                                            i + 1] = ' ';
                        tableau_ordi->grille[bateau[choix_bateau]->ligne + 1][bateau[choix_bateau]->colonne -
                                                                            i +
                                                                            1] = bateau[choix_bateau]->identification;
                    }
                    bateau[choix_bateau]->colonne = bateau[choix_bateau]->colonne - deplacement;
                } else {
                    for (i = 0; i < (deplacement - deplacement_max_gauche); i++) {
                        tableau_ordi->grille[bateau[choix_bateau]->ligne + 1][bateau[choix_bateau]->colonne +
                                                                            i +
                                                                            1] = ' ';
                        tableau_ordi->grille[bateau[choix_bateau]->ligne + 1][bateau[choix_bateau]->colonne +
                                                                            bateau[choix_bateau]->taille_bateau +
                                                                            i +
                                                                            1] = bateau[choix_bateau]->identification;
                    }
                    bateau[choix_bateau]->colonne =
                            bateau[choix_bateau]->colonne + (deplacement - deplacement_max_gauche);
                }

            } else {
                deplacement = rand() % (deplacement_max_bas + deplacement_max_haut) + 1;
                if (deplacement <= deplacement_max_haut) {
                    for (i = 1; i < (deplacement + 1); i++) {
                        tableau_ordi->grille[bateau[choix_bateau]->ligne +
                                            bateau[choix_bateau]->taille_bateau -
                                            i + 1][bateau[choix_bateau]->colonne + 1] = ' ';
                        tableau_ordi->grille[bateau[choix_bateau]->ligne - i + 1][
                                bateau[choix_bateau]->colonne +
                                1] = bateau[choix_bateau]->identification;
                    }
                    bateau[choix_bateau]->ligne = bateau[choix_bateau]->ligne - deplacement;
                } else {
                    for (i = 0; i < (deplacement - deplacement_max_haut); i++) {
                        tableau_ordi->grille[bateau[choix_bateau]->ligne + i + 1][
                                bateau[choix_bateau]->colonne +
                                1] = ' ';
                        tableau_ordi->grille[bateau[choix_bateau]->ligne +
                                            bateau[choix_bateau]->taille_bateau +
                                            i + 1][bateau[choix_bateau]->colonne +
                                                   1] = bateau[choix_bateau]->identification;
                    }
                    bateau[choix_bateau]->ligne =
                            bateau[choix_bateau]->ligne + (deplacement - deplacement_max_haut);
                }
            }

            //printf("Un bateau de taille %d s'est deplace en nouvelle position : %c %d \n",bateau[choix_bateau].taille_bateau, 'A' + bateau[choix_bateau].colonne,bateau[choix_bateau].ligne);
            printf("Un bateau s'est deplace");
        }

    }

}

void save(FILE* file, Grid tableau_joueur, Grid tableau_ordi, Inventory missile, Boat bateau[], int NB_bateau, int nombre_tour, char mode){
    int i,j;
    rewind(file);
    fprintf(file,"1\n");
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

int load(FILE* file){
    int i,j, nombre_tour,NB_bateau,partie;
    Grid tableau_joueur;
    Grid tableau_ordi;
    Inventory missile;
    char mode;
    tableau_ordi.hauteur = 12;
    tableau_ordi.largeur = 12;
    tableau_joueur.hauteur = 12;
    tableau_joueur.largeur = 12;
    rewind(file);
    char temp[20]={0};
    fgets(temp, 20, file);
    fgets(temp, 20, file);
    NB_bateau = atoi(temp);
    fgets(temp, 20, file);
    nombre_tour = atoi(temp);
    fgets(temp, 20, file);
    mode = temp[0];
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
        fgets(temp, 20, file);
        bateau[i].identification=temp[0];
    }

    for(i=0;i<tableau_joueur.hauteur;i++){
        fgets(temp, 20, file);
        for(j=0;j<tableau_joueur.largeur;j++){
            tableau_joueur.grille[i][j] = temp[j];
        }
    }
    for(i=0;i<tableau_ordi.hauteur;i++){
        fgets(temp, 20, file);
        for(j=0;j<tableau_ordi.largeur;j++){
            tableau_ordi.grille[i][j] = temp[j];
        }
    }
    fclose(file);
    partie = game(tableau_joueur, tableau_ordi, missile, bateau, NB_bateau, mode, nombre_tour,1);
    return partie;
}

int fin_partie(Boat bateau[],Inventory missile,int NB_bateau){
    int i;
    int touche=0;
    int partie;
    for (i=0;i<NB_bateau;i++){
        if (bateau[i].touche == bateau[i].taille_bateau) {
            touche++;
        }
    }
    if(touche == 5 && (missile.tactique != 0 || missile.simple!=0 || missile.artillerie != 0 || missile.bombe != 0)){
        partie = 1;
    }else if(touche == 5 && missile.tactique == 0 && missile.simple==0 && missile.artillerie == 0 && missile.bombe == 0){
        partie = 2;
    } else if(touche != 5 && missile.tactique == 0 && missile.simple==0 && missile.artillerie == 0 && missile.bombe == 0){
        partie = 3;
    } else {
        partie = 0;
    }
    return partie;
}

void partie_finie(int partie) {

    if (partie == 1) {
        printf("\nFelicitations ! Vous avez gagne la partie, Bravo !\n\n");
    } else if (partie == 2) {
        printf("\nVous avez gagne la partie de peu, Bravo !\n\n");
    } else if (partie == 3){
        printf("\nDommage ! Vous avez perdu la partie...\n\n");
    } else if (partie ==4){
        printf("\nVotre partie a bien ete sauvegardee !\n\n");
    }
}

char recommencer()
{
    char rejouer;
    printf("Voulez vous rejouer? (O/N)\n");
    scanf(" %c", &rejouer);
    rejouer = toupper(rejouer);
    while(rejouer != 'O' && rejouer != 'N')
    {
        printf("Veuillez saisir une reponse valide (O/N).\n");
        scanf(" %c", &rejouer);
        rejouer = toupper(rejouer);
    }
    return rejouer;
}
