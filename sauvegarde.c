//
// Created by arnau on 13/06/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "sauvegarde.h"

int demande_sauvegarde(FILE* file, Grid tableau_joueur, Grid tableau_ordi, Inventory missile, Boat bateau[], int NB_bateau, int nombre_tour, char mode){
    int i;
    char temp[5];
    int verification;
    int partie;
    char ecraser[5]={0};
    char quitter[5]={0};

    rewind(file);
    fgets(temp,5,file);             // On prend le chiffre au tout début du fichier pour voir s'il y a une sauvegarde dans ce fichier
    verification=atoi(temp);
    fclose(file);
    if(verification == 0){                    // S'il n'y a pas de sauvegarde, on sauvegarde
        save(file, tableau_joueur, tableau_ordi, missile, bateau, NB_bateau, nombre_tour, mode);
        partie = 4;
    } else {                                  // Sinon on demande à l'utilisateur si il veut écraser cette sauvegarde

        printf("Si vous enregistrez cette partie, la derniere sauvegarde sera ecrasee. Etes-vous sur de vouloir sauvegarder (OUI/NON)\n");
        fflush(stdin);
        gets(ecraser);

        for (i=0;i<5;i++){
            ecraser[i] = toupper(ecraser[i]);
        }

        while(strcmp(ecraser,"OUI")!=0 && strcmp(ecraser,"NON")!=0)         // Verfication avec message d'erreur si l'utilisateur ne saisie pas la bonne chaine de caractère
        {
            printf("Veuillez saisir un mot valide (OUI/NON)\n");
            fflush(stdin);
            gets(ecraser);
            for (i=0;i<5;i++){
                ecraser[i] = toupper(ecraser[i]);
            }
        }

        if(strcmp(ecraser,"OUI")==0){                                       // Si l'utilisateur veut écraser une sauvegarde alors on sauvegarde par dessus en effacant le fichier
            save(file, tableau_joueur, tableau_ordi, missile, bateau, NB_bateau, nombre_tour, mode);
            partie = 4;

        } else {

            printf("Voulez-vous quitter? (OUI/NON)\n");
            fflush(stdin);  // On vide le buffer
            gets(quitter);       // On récupère la réponse de l'utilisateur

            for (i=0;i<5;i++){
                quitter[i] = toupper(quitter[i]);                           // On met en majuscule pour que l'utilisateur puisse taper soit en majuscule, soit en minuscule
            }

            while(strcmp(quitter,"OUI")!=0 && strcmp(quitter,"NON")!=0)     // Verfication avec message d'erreur si l'utilisateur ne saisie pas la bonne chaine de caractère
            {
                printf("Veuillez saisir un mot valide (OUI/NON)\n");
                fflush(stdin);  // On vide le buffer
                gets(quitter);       // On récupère la réponse de l'utilisateur
                for (i=0;i<5;i++){
                    quitter[i] = toupper(quitter[i]); // On met en majuscule la saisie de l'utilisateur pour pouvoir lire ce qu'il a écrit même si c'est en minuscule
                }
            }

            if (strcmp(quitter,"OUI")==0){  // Si l'utilisateur confirme qu'il veut quitter le programme
                partie = 5;                 // On quitte la partie
            } else {
                partie =0;                  // On continue la partie
            }
        }
    }
    return partie;
}


void save(FILE* file, Grid tableau_joueur, Grid tableau_ordi, Inventory missile, Boat bateau[], int NB_bateau, int nombre_tour, char mode){
    int i,j;
    file = fopen("sauvegarde_jeu.txt", "w");     // On ouvre le fichier en écriture
    rewind(file);                                               // On remonte le curseur en haut du fichier
    fprintf(file,"1\n");                                 // On écrit le chiffre 1 pour pouvoir vérifier lors du prochain lancement de programme qu'il y a une sauvegarde
    fprintf(file,"%d\n",NB_bateau);                      // On écrit le nombre total de bateau
    fprintf(file,"%d\n",nombre_tour);                    // On écrit le nombre de tour où l'utilisateur s'est arrêté
    fprintf(file,"%c\n",mode);                           // On écrit le mode que l'utilisateur a choisi

    fprintf(file,"%d\n",missile.artillerie);    // On écrit le nombre de missiles d'artillerie restants à l'utilisateur
    fprintf(file,"%d\n",missile.tactique);      // On écrit le nombre de missiles tactiques restants à l'utilisateur
    fprintf(file,"%d\n",missile.bombe);         // On écrit le nombre de bombes restantes à l'utilisateur
    fprintf(file,"%d\n",missile.simple);        // On écrit le nombre de missiles simples restants à l'utilisateur

    for(i=0;i<NB_bateau;i++){                                  // Pour chaque bateau on écrit :
        fprintf(file,"%d\n",bateau[i].taille_bateau);   // sa taille
        fprintf(file,"%d\n",bateau[i].ligne);           // sa ligne définissant sa position dans le tableau
        fprintf(file,"%d\n",bateau[i].colonne);         // sa colonne définissant sa position dans le tableau
        fprintf(file,"%d\n",bateau[i].H_V);             // son orientation
        fprintf(file,"%d\n",bateau[i].touche);          // le nombre de fois que le bateau a été touché pendant la partie
        fprintf(file,"%c\n",bateau[i].identification);  // sa lettre qui permet de l'identifier sur la tableau de l'ordinateur
    }


    for(i=0;i<tableau_joueur.hauteur;i++){
        for(j=0;j<tableau_joueur.largeur;j++) {
            fprintf(file,"%c",tableau_joueur.grille[i][j]);     // On écrit chaque cases du tableau du joueur dans le fichier
        }
        fprintf(file,"\n");                                     // On saute une ligne pour respecter le rendu visuel du tableau et son format
    }
    for(i=0;i<tableau_ordi.hauteur;i++){
        for(j=0;j<tableau_ordi.largeur;j++) {
            fprintf(file,"%c",tableau_ordi.grille[i][j]);       // On écrit chaque cases du tableau de l'ordinateur dans le fichier
        }
        fprintf(file,"\n");                                     // On saute une ligne pour respecter le rendu visuel du tableau et son format
    }
    fclose(file);
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

    fgets(temp, 20, file);            // On saute la récupération du chiffre permattant de savoir si il y a une sauvegarde ou pas

    fgets(temp, 20, file);
    NB_bateau = atoi(temp);                     // On récupère le nombre total de bateau
    fgets(temp, 20, file);
    nombre_tour = atoi(temp);                   // On récupère le nombre de tour où l'utilisateur s'est arrêté
    fgets(temp, 20, file);
    mode = temp[0];                             // On récupère le mode que l'utilisateur a choisi


    fgets(temp, 20, file);
    missile.artillerie = atoi(temp);            // On récupère le nombre de missiles d'artillerie restants à l'utilisateur
    fgets(temp, 20, file);
    missile.tactique = atoi(temp);              // On récupère le nombre de missiles tactiques restants à l'utilisateur
    fgets(temp, 20, file);
    missile.bombe = atoi(temp);                 // On récupère le nombre de bombes restantes à l'utilisateur
    fgets(temp, 20, file);
    missile.simple = atoi(temp);                // On récupère le nombre de missiles simples restants à l'utilisateur

    Boat bateau[NB_bateau];
    for(i=0;i<NB_bateau;i++){                   // Pour chaque bateau on récupère :
        fgets(temp, 20, file);
        bateau[i].taille_bateau = atoi(temp);   // sa taille
        fgets(temp, 20, file);
        bateau[i].ligne = atoi(temp);           // sa ligne définissant sa position dans le tableau
        fgets(temp, 20, file);
        bateau[i].colonne = atoi(temp);         // sa colonne définissant sa position dans le tableau
        fgets(temp, 20, file);
        bateau[i].H_V = atoi(temp);             // son orientation
        fgets(temp, 20, file);
        bateau[i].touche = atoi(temp);          // le nombre de fois que le bateau a été touché pendant la partie
        fgets(temp, 20, file);
        bateau[i].identification=temp[0];       // sa lettre qui permet de l'identifier sur la tableau de l'ordinateur
    }

    for(i=0;i<tableau_joueur.hauteur;i++){
        fgets(temp, 20, file);              // On récupère chaque cases du tableau du joueur dans le fichier
        for(j=0;j<tableau_joueur.largeur;j++){
            tableau_joueur.grille[i][j] = temp[j];    // On associe chaque ligne du fichier à la case correspondante du tableau
        }
    }
    for(i=0;i<tableau_ordi.hauteur;i++){
        fgets(temp, 20, file);              // On récupère chaque cases du tableau de l'ordinateur dans le fichier
        for(j=0;j<tableau_ordi.largeur;j++){
            tableau_ordi.grille[i][j] = temp[j];      // On associe chaque ligne du fichier à la case correspondante du tableau
        }
    }
    fclose(file);
    partie = game(tableau_joueur, tableau_ordi, missile, bateau, NB_bateau, mode, nombre_tour,1); // On lance la aprtie avec les données chargées
    return partie;
}