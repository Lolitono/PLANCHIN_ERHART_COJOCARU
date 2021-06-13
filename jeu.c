//
// Created by arnau on 27/05/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "jeu.h"


char menu(FILE * file){
    char demarrer;
    int charger;
    char temp[5];

    rewind(file);                                   // On remonte le curseur en haut du fichier
    fgets(temp, 20, file);                // On récupère la première valeur du fichier
    charger = atoi(temp);                           // On convertit cette valeur en entier (ce sera soit 0 soit 1)

    printf("\n\n=======================================\nMENU\n=======================================\n\n"
           "Que voulez vous faire : \n"
           "-Demarrer une nouvelle partie (D)\n");
    if(charger == 1){                               // Si le fichier contient une sauvegarde, l'utilisateur pourra charger une partie (sinon, l'utilisateur ne peut que démarrer ou quitter)
        printf("-Charger votre derniere partie (C)\n");
    }
    printf("-Quitter (Q)\n\n");
    scanf(" %c", &demarrer);                 // On récupère le choix de l'utilisateur
    demarrer = toupper(demarrer);                   // On le met en majuscule (pour qu'il puisse écrire en majuscule ou minuscule)
    if(charger == 0){                               // Si il n'y a pas de sauvegarde dans le fichier
        while(demarrer != 'D' && demarrer != 'Q') { // On lui demande de recommencer tant qu'il n'a pas saisit de valeur valide
            printf("Veuillez saisir une reponse valide (D/Q):\n");
            scanf(" %c", &demarrer);         // On récupère le choix de l'utilisateur
            demarrer = toupper(demarrer);           // On met son choix en majuscule
        }
    } else {                                                            // Si il y a une sauvegarde dans le fichier
        while(demarrer != 'D' && demarrer != 'Q' && demarrer != 'C'){   // On lui demande de recommencer tant qu'il n'a pas saisit de valeur valide
            printf("Veuillez saisir une reponse valide (D/C/Q):\n");
            scanf(" %c", &demarrer);                             // On récupère le choix de l'utilisateur
            demarrer = toupper(demarrer);                               // On le met en majuscule
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
        scanf(" %c", &mode);                                             // On récupère le choix de l'utilsateur
        mode = toupper(mode);                                                   // On le met en majuscule
        while(mode != 'C' && mode != 'B' && mode != 'A') {                      // On lui demande de recommencer tant que la valeur saisie n'est pas correcte
        printf("Veuillez saisir une reponse valide (C/B/A):\n");
        scanf(" %c", &mode);                                             // On récupère le choix de l'utilisateur
        mode = toupper(mode);                                                   // On le met en majuscule
    }
    return mode;                                                                // On renvoie son choix
}


char demande_difficulte()
{
    char rep;
    printf("\n\n=======================================\nDIFFICULTE\n=======================================\n\n"
           "\nQuelle difficulte voulez-vous ?\n"
           "-Facile (F)\n"
           "-Moyen (M)\n"
           "-Difficile (D)\n");
    scanf(" %c", &rep);                                             // On récupère le choix de l'utilisateur
    rep = toupper(rep);                                                     // On le met en majuscule
    while(rep != 'F' && rep != 'M' && rep != 'D') {                         // On lui demande de recommencer tant que la valeur saisie n'est pas correcte
        printf("Veuillez saisir une reponse valide (F/M/D):\n");
        scanf(" %c", &rep);                                         // On récupère le choix utilisateur
        rep = toupper(rep);                                                 // On le met en majuscule
    }
    return rep;                                                             // On renvoie son choix
}


int game(Grid tableau_joueur, Grid tableau_ordi, Inventory missile, Boat bateau[], int NB_bateau, char mode, int nombre_tour, int charger){
    int partie;
    char missile_utilise,sauvegarde;
    Actif deplacement_actif={0};
    Impact point_impact;

    if (nombre_tour == 1) {                                             // On donne ces informations si on commence une nouvelle partie
        affichage_missile_depart(missile);
        printf("Voici le nombre de bateaux que l'ordinateur va placer aleatoirement:\n\n");
        affichage_nb_bateau(bateau, NB_bateau);
        affichage_tableau(tableau_joueur);
    } else if(charger == 1){                                            // Si on charge une partie existante
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
        if (mode == 'C' || mode == 'A') {                               // On affiche le tableau sauf si on est en mode Blind
            affichage_tableau(tableau_joueur);
           // affichage_tableau(tableau_ordi); //Décommenter pour voir le tableau de l'ordinateur en même temps que le tableau du joueur et comparer
        }
    }

    do {
        printf("\n\n=======================================\nTOUR %d\n=======================================\n\n",
               nombre_tour);

        if(nombre_tour!=1 && mode=='A') {
            deplacement_actif.decision = rand()%3;                      // L'ordinateur décide si il veut bouger un bateau ou pas
            if(deplacement_actif.decision != 0) {                       // On a choisi que le bateau avait 2 chances sur 3 de bouger
                deplacement_actif = verification_deplacement_bateau_mode_active(tableau_ordi,tableau_joueur, bateau ,NB_bateau);
                if (deplacement_actif.tableau_active[deplacement_actif.choix_bateau] == bateau[deplacement_actif.choix_bateau].identification && deplacement_actif.verification_mode_active!=5){
                    // Si le bateau choisi est bien identifié dans le tableau de verfication des bateaux pouvant se déplacer ET qu'au moins un bateau peut se déplacer
                    bateau[deplacement_actif.choix_bateau] = deplacement_bateau_mode_active(&tableau_ordi,bateau,deplacement_actif); // On déplace un bateau
                }
            }
        }

        missile_utilise = demande_missile(missile);
        point_impact = saisie_tir(tableau_joueur);
        printf("Le missile tombera en %c%d.\n\n", 'A' + point_impact.colonne, point_impact.ligne);

        if (missile_utilise == 'A') {                                                               // Si l'utilisateur utilise un missile d'artillerie

            missile.artillerie = missile.artillerie - 1;                                            // Il en pert un de son inventaire
            tir_artillerie(&tableau_joueur, &tableau_ordi, point_impact, NB_bateau, bateau,mode);

        } else if (missile_utilise == 'T') {                                                        // Si l'utilisateur utilise un missile tactique

            missile.tactique = missile.tactique - 1;                                                // Il en pert un de son inventaire
            tir_tactique(&tableau_joueur, &tableau_ordi, point_impact,NB_bateau,bateau,mode);

        } else if (missile_utilise == 'B') {                                                        // Si l'utilisateur utilise une bombe

            missile.bombe = missile.bombe - 1;                                                      // Il en pert une de son inventaire
            tir_bombe(&tableau_joueur, &tableau_ordi, point_impact, NB_bateau, bateau,mode);

        } else {                                                                                    // Si l'utilisateur utilise un missile simple

            missile.simple = missile.simple - 1;                                                    // Il en pert un de son inventaire
            tir_simple(&tableau_joueur, &tableau_ordi,point_impact,mode,NB_bateau,bateau);

        }

        nombre_tour++;                                                                              // Le tour est fini, on l'incrémente donc de 1
        partie = fin_partie(bateau, missile, NB_bateau);

        if (partie==0){                                                                             // Si il reste des munitions à l'utilisateur et des bateaux à détruire
            printf("\nVoici le nombre de bateaux qu'il vous reste a detruire:\n\n");
            affichage_nb_bateau(bateau, NB_bateau);
            affichage_missile(missile);
            if (mode == 'C' || mode == 'A') {                                                       // On affiche le tableau sauf en mode blind
                affichage_tableau(tableau_joueur);
                printf("\n");
                //affichage_tableau(tableau_ordi); //Décommenter pour voir le tableau de l'ordinateur en même temps que le tableau du joueur et comparer
            }
            printf("\nVoulez continuer ou sauvegarder et quitter (C/S)?\n");
            scanf(" %c", &sauvegarde);                                                       // On récupère le choix de l'utilisateur
            sauvegarde = toupper(sauvegarde);                                                       // On le met en majuscule
            while (sauvegarde != 'C' && sauvegarde != 'S') {                                        // On demande à l'utilisateur de recommencer tant que la valeur saisie est non valide
                printf("\nVeuillez saisir C pour continuer ou S pour sauvegarder.\n");
                scanf(" %c", &sauvegarde);                                                  // On récupère le choix de l'utilisateur
                sauvegarde = toupper(sauvegarde);                                                   // On le met en majuscule
            }
            if (sauvegarde == 'S') {                                                                // Si l'utilisateur veut sauvegarder
                FILE *file = fopen("sauvegarde_jeu.txt", "r");                       // On ouvre le fichier en mode lecture
                partie = demande_sauvegarde(file, tableau_joueur, tableau_ordi, missile, bateau, NB_bateau, nombre_tour, mode);
            }
        }
    } while (partie == 0);                                                                          // On continue la partie tant que l'utilisateur peut et veut continuer à jouer

    if (partie<=3) {                                                                                // Dès que la partie est finie, on affiche le tableau sauf s'il sauvegarde
        affichage_tableau(tableau_joueur);
    }

    return partie;                                                                                  // On retourne la situation de la partie (continue/gagnée/sauvegardée/perdue)
}


Impact saisie_tir(Grid tableau_joueur){
    Impact tir_actuel;
    char ligne[2]={0};
    char T[3]={0};
    char lettre;
    int chiffre;
    int verification;

    do{                                                                                                                     //On demande la position où l'utilisateur veut tirer
        verification=0;
        printf("En quelle case voulez vous tirer ( de A0 a J9) ?\n");
        scanf(" %s", &T);                                                                                            // On récupère le choix de l'utilisateur
        lettre = toupper(T[0]);                                                                                         // On met la lettre en majuscule
        ligne[0] = T[1];                                                                                                    // On transmet le chiffre dans un autre tableau de caractère
        chiffre = atoi(ligne);                                                                                              // pour le convertir en entier
        tir_actuel.colonne= lettre-'A';                                                                                     // On obtient un chiffre correspondant à la colonne
        tir_actuel.ligne= chiffre;                                                                                          // et un chiffre correspondant à la ligne
        while( tir_actuel.colonne < 0 || tir_actuel.colonne > 9 || tir_actuel.ligne <0 || tir_actuel.ligne>9 || T[2]!= '\0')// On vérifie que le tir est bien dans la grille de jeu
        {
            printf("Votre tir n'est pas valide (case inconnue), veuillez recommencer ...\n");
            scanf(" %s", &T);                                                                                       // On récupère le choix de l'utilisateur
            lettre = toupper(T[0]);                                                                                     // On met la lettre en majuscule
            ligne[0] = T[1];                                                                                                // On transmet le chiffre dans un autre tableau de caractère
            chiffre = atoi(ligne);                                                                                          // pour le convertir en entier
            tir_actuel.colonne= lettre-'A';                                                                                 // On obtient un chiffre correspondant à la colonne
            tir_actuel.ligne= chiffre;                                                                                      // Et un chiffre correspondant à la ligne
        }
        if (tableau_joueur.grille[1 + tir_actuel.ligne][1 + tir_actuel.colonne] == 'O' ||
            tableau_joueur.grille[1 + tir_actuel.ligne][1 + tir_actuel.colonne] == 'X') {                                   // On vérifie si l'utilisateur ne tire pas sur une case déjà touchée
            verification = 1;
            printf("Votre tir n'est pas valide (case deja touchee), veuillez recommencer ...\n");
        }
    }while(verification == 1);                                                                                              // Jusqu'à ce que l'utilisateur choisisse une case valide

    return tir_actuel;                                                                                                      // On retourne les coordonnes du tir
}


Actif verification_deplacement_bateau_mode_active(Grid tableau_ordi, Grid tableau_joueur, Boat bateau[],int NB_bateau){
    int i,j;
    Actif deplacement;

    deplacement.verification_mode_active = 0;                                                                               // On part du principe que tout les bateaux peuvent se déplacer
    for (i = 0; i < NB_bateau; i++) {                                                                                       // On fait ceci pour tout les bateaux
        if (bateau[i].touche == 0) {                                                                                        // Si le bateau n'est pas touche
            deplacement.tableau_active[i] = bateau[i].identification;                                                       // Il aura la possibilité de se déplacer
        } else {                                                                                                            // Sinon
            deplacement.tableau_active[i] = ' ';                                                                            // Il ne pourra pas se déplacer
            deplacement.verification_mode_active++;                                                                         // On incrémente de 1 le nombre de bateaux non déplacables
        }
    }
    deplacement.tableau_active[i] = '\0';                                                                                   // On rajoute le caractère de fin de chaîne pour finir le tablaeu
    //printf("%s\n", tableau_active); //Ligne à décommenter pour voir les bateaux pouvant ce déplacer

    if (deplacement.verification_mode_active != 5) {                                                                        // S'il reste au moins un bateau non touché

        do {
            do {
                deplacement.choix_bateau = rand() % 5;
            } while (deplacement.tableau_active[deplacement.choix_bateau] == ' ');                                          // On choisit aléatoirement un bateau non touché

            //printf("bateau choisie : %c, H_V = %d\n", bateau[choix_bateau].identification,bateau[choix_bateau].H_V); // Ligne à décommenter si vous voulez voir le bateau choisi ainsi que son orientation pour avoir une idée des deplacements possibles de ce bateau

            deplacement.max_gauche = 0;                                                                                     //On initialise les déplacements maximaux du bateau à 0
            deplacement.max_droite = 0;
            deplacement.max_haut = 0;
            deplacement.max_bas = 0;
            i = 1;
            j = 0;
            if (bateau[deplacement.choix_bateau].H_V == 0) {                                                                // Si le bateau est horizontal on regarde :
                do {
                    if (tableau_joueur.grille[bateau[deplacement.choix_bateau].ligne + 1][bateau[deplacement.choix_bateau].colonne - i + 1] == '_' &&
                        tableau_ordi.grille[bateau[deplacement.choix_bateau].ligne + 1][bateau[deplacement.choix_bateau].colonne - i + 1] == ' ')
                    {                                                                       // Si la case directement à gauche du bateau n'a pas été touché et ne contient pas un autre bateau dans le tableau de l'ordinateur
                        deplacement.max_gauche++;                                           // On incrémente le déplacement maximal vers la gauche de 1
                    }
                    i++;                                                                    // On incrémente le compteur de 1
                } while (i < 4 && deplacement.max_gauche + 1 == i);                         // On répète jusqu'à ce que le déplacement maximaximal soit égal à 3 ou qu'il y ait un bateau sur la route

                //printf("deplacement max gauche : %d\n", deplacement_max_gauche); // Ligne à décommenter si vous voulez voir le déplacement max gauche du bateau choisi

                do {
                    if (tableau_joueur.grille[bateau[deplacement.choix_bateau].ligne + 1][bateau[deplacement.choix_bateau].colonne +bateau[deplacement.choix_bateau].taille_bateau + j + 1] == '_' &&
                        tableau_ordi.grille[bateau[deplacement.choix_bateau].ligne + 1][bateau[deplacement.choix_bateau].colonne +bateau[deplacement.choix_bateau].taille_bateau + j + 1] == ' ')
                    {                                                                       // Si la case directement à droite du bateau n'a pas été touché et ne contient pas un autre bateau
                        deplacement.max_droite++;                                           // On incrémente le déplacement maximal vers la droite de 1
                    }
                    j++;                                                                    // On incrémente le compteur de 1
                } while (j < 3 && deplacement.max_droite == j);                             // On répète jusqu'à ce que le déplacement maximal soit égal à 3 ou qu'il y ait un bateau sur la route

                //printf("deplacement max droite : %d\n", deplacement_max_droite); // Ligne à décommenter si vous voulez voir le déplacement max droite du bateau choisi

            } else {                                                                        // On fait la même démarche mais pour les bateaux verticaux qui se déplaceront vers le haut ou le bas

                do {
                    if (tableau_joueur.grille[bateau[deplacement.choix_bateau].ligne - i + 1][bateau[deplacement.choix_bateau].colonne +1] == '_' &&
                        tableau_ordi.grille[bateau[deplacement.choix_bateau].ligne - i + 1][bateau[deplacement.choix_bateau].colonne +1] == ' ')
                    {                                                                       // Si la case directement en haut du bateau n'a pas été touché et ne contient pas un autre bateau dans le tableau de l'ordinateur
                        deplacement.max_haut++;                                             // On incrémente le déplacement maximal vers le haut de 1
                    }
                    i++;                                                                    // On incrémente le compteur de 1
                } while (i < 4 && deplacement.max_haut + 1 == i);                           // On répète jusqu'à ce que le déplacement maximal soit égal à 3 ou qu'il y ait un bateau sur la route

                //printf("deplacement max haut : %d\n", deplacement_max_haut); // Ligne à décommenter si vous voulez voir le déplacement max haut du bateau choisi

                do {
                    if (tableau_joueur.grille[bateau[deplacement.choix_bateau].ligne +bateau[deplacement.choix_bateau].taille_bateau +j + 1][bateau[deplacement.choix_bateau].colonne + 1] == '_' &&
                        tableau_ordi.grille[bateau[deplacement.choix_bateau].ligne +bateau[deplacement.choix_bateau].taille_bateau +j + 1][bateau[deplacement.choix_bateau].colonne + 1] == ' ')
                    {                                                                       // Si la case directement en bas du bateau n'a pas été touché et ne contient pas un autre bateau dans le tableau de l'ordinateur
                        deplacement.max_bas++;                                              // On incrémente le déplacement maximal vers le bas de 1
                    }
                    j++;                                                                    // On incrémente le compteur de 1
                } while (j < 3 && deplacement.max_bas == j);                                // On répète jusqu'à ce que le déplacement maximal soit égal à 3 ou qu'il y ait un bateau sur la route

                //printf("deplacement max bas : %d\n", deplacement_max_bas); // Ligne à décommenter si vous voulez voir le déplacement max bas du bateau choisi

            }

            if (deplacement.max_droite == 0 && deplacement.max_gauche == 0 && deplacement.max_bas == 0 &&deplacement.max_haut == 0)
            {                                                                               // Si le bateau choisi n'a pas de déplacement possible
                deplacement.tableau_active[deplacement.choix_bateau] = ' ';                 // On enlève le bateau choisi des bateaux déplaçables
                deplacement.verification_mode_active++;                                     // On incrémente de 1 le nombre de bateaux non déplaçables
            }

        } while (deplacement.tableau_active[deplacement.choix_bateau] == ' ' && deplacement.verification_mode_active != 5); // On regarde si un bateau est déplacebale tant qu'on n'a pas trouvé de bateau déplaçable et qu'il en reste au moins 1
    } else{                                     // Si aucun bateau ne peut se déplacer
        deplacement.choix_bateau = 0;           // On prends un bateau qui ne peut pas se déplacer
    }
    return deplacement;
}


Boat deplacement_bateau_mode_active(Grid *tableau_ordi, Boat bateau[], Actif deplacement){

    int i;

    if (bateau[deplacement.choix_bateau].H_V == 0) {                                                    // Si le bateau à déplacer est horizontal
        deplacement.mouvement_bateau = rand() % (deplacement.max_gauche + deplacement.max_droite) + 1;  // On choisit aléatoirement le déplacement du bateau par rapport à l'horizontal
        if (deplacement.mouvement_bateau <= deplacement.max_gauche) {                                   // Si le déplacement choisi est inférieur au déplacement maximal vers la gauche, le bateau se déplacera vers la gauche
            for (i = 1; i < (deplacement.mouvement_bateau + 1); i++) {                                  // On répète le décalage du bateau jusqu'à ce que le déplacement choisi soit atteint
                tableau_ordi->grille[bateau[deplacement.choix_bateau].ligne + 1][bateau[deplacement.choix_bateau].colonne +bateau[deplacement.choix_bateau].taille_bateau -i + 1] = ' ';    // La case du bateau la plus à droite disparait sur le tableau de l'ordinateur
                tableau_ordi->grille[bateau[deplacement.choix_bateau].ligne + 1][bateau[deplacement.choix_bateau].colonne -i +1] = bateau[deplacement.choix_bateau].identification;         // La case du bateau la plus à gauche plus un décalage de 1 est remplacée par la lettre du bateau sur le tableau de l'ordinateur
            }
            bateau[deplacement.choix_bateau].colonne = bateau[deplacement.choix_bateau].colonne - deplacement.mouvement_bateau;             // On remplace l'ancienne position sur la colonne par la nouvelle
        } else {                                                                                                                            // Sinon le bateau se déplacera vers la droite
            for (i = 0; i < (deplacement.mouvement_bateau - deplacement.max_gauche); i++) {                                                 // On répète le décalage du bateau jusqu'à ce que le déplacement choisi soit atteint
                tableau_ordi->grille[bateau[deplacement.choix_bateau].ligne + 1][bateau[deplacement.choix_bateau].colonne +i +1] = ' ';     // La case du bateau la plus à gauche disparait sur le tableau de l'ordinateur
                tableau_ordi->grille[bateau[deplacement.choix_bateau].ligne + 1][bateau[deplacement.choix_bateau].colonne +bateau[deplacement.choix_bateau].taille_bateau +i +1] = bateau[deplacement.choix_bateau].identification; // La case du bateau la plus à droite plus un décalage de 1 est remplacée par la lettre du bateau sur le tableau de l'ordinateur

            }
            bateau[deplacement.choix_bateau].colonne = bateau[deplacement.choix_bateau].colonne + (deplacement.mouvement_bateau - deplacement.max_gauche); // On remplace l'ancienne position sur la colonne par la nouvelle
        }
        // On a pas besoin de changer la ligne du bateau pour un déplacement horizontal car le bateau se déplace sur la même ligne

    } else {                                                                                         // Sinon le bateau à déplacer est vertical
        deplacement.mouvement_bateau = rand() % (deplacement.max_bas + deplacement.max_haut) + 1;    // On choisit aléatoirement le déplacement du bateau sur la verticale
        if (deplacement.mouvement_bateau <= deplacement.max_haut) {                                  // Si le déplacement choisi est inférieur au déplacement maximal vers le haut, le bateau se déplacera vers le haut
            for (i = 1; i < (deplacement.mouvement_bateau + 1); i++) {                               // On répète le décalage du bateau jusqu'à ce que le déplacement choisi soit atteint
                tableau_ordi->grille[bateau[deplacement.choix_bateau].ligne +bateau[deplacement.choix_bateau].taille_bateau -i + 1][bateau[deplacement.choix_bateau].colonne + 1] = ' ';    // La case du bateau la plus en bas disparait sur le tableau de l'ordinateur
                tableau_ordi->grille[bateau[deplacement.choix_bateau].ligne - i + 1][bateau[deplacement.choix_bateau].colonne +1] = bateau[deplacement.choix_bateau].identification;        // La case du bateau la plus en haut plus un décalage de 1 est remplacée par la lettre du bateau sur le tableau de l'ordinateur
            }
            bateau[deplacement.choix_bateau].ligne =bateau[deplacement.choix_bateau].ligne - deplacement.mouvement_bateau;  // On remplace l'ancienne position sur la colonne par la nouvelle
        } else {                                                                                                                                                        // Sinon le bateau se déplacera vers le bas
            for (i = 0; i < (deplacement.mouvement_bateau - deplacement.max_haut); i++) {                                                                               // On répète le décalage du bateau jusqu'à ce que le déplacement choisi soit atteint
                tableau_ordi->grille[bateau[deplacement.choix_bateau].ligne + i + 1][bateau[deplacement.choix_bateau].colonne +1] = ' ';                                // La case du bateau la plus en haut disparait sur le tableau de l'ordinateur
                tableau_ordi->grille[bateau[deplacement.choix_bateau].ligne +bateau[deplacement.choix_bateau].taille_bateau +i + 1][bateau[deplacement.choix_bateau].colonne +1] = bateau[deplacement.choix_bateau].identification; // La case du bateau la plus en bas plus un décalage de 1 est remplacée par la lettre du bateau sur le tableau de l'ordinateur
            }
            bateau[deplacement.choix_bateau].ligne =bateau[deplacement.choix_bateau].ligne + (deplacement.mouvement_bateau - deplacement.max_haut); // On remplace l'ancienne position sur la colonne par la nouvelle
        }
        // On a pas besoin de changer la colonne du bateau pour un déplacement vertical car le bateau se déplace sur la même colonne
    }
    //printf("Un bateau de taille %d s'est deplace en nouvelle position : %c %d \n",bateau[choix_bateau].taille_bateau, 'A' + bateau[choix_bateau].colonne,bateau[choix_bateau].ligne); // Ligne à décommenter si vous voulez voir la nouvelle position du bateau choisi
    printf("Un bateau s'est deplace");

    return bateau[deplacement.choix_bateau];
}


int fin_partie(Boat bateau[],Inventory missile,int NB_bateau){
    int i;
    int touche=0;
    int partie;
    for (i=0;i<NB_bateau;i++){                              // On répète cette boucle pour chaque bateau
        if (bateau[i].touche == bateau[i].taille_bateau) {  // Si un bateau est touché autant de fois qu'il a de cases (si il est coulé)
            touche++;                                       // On incremente le nombre de bateaux coulés de 1
        }
    }
    if(touche == 5 && (missile.tactique != 0 || missile.simple!=0 || missile.artillerie != 0 || missile.bombe != 0)){       // Si tous les bateaux sont touchés et qu'il lui reste au moins une munition
        partie = 1;                                                                                                         // On renvoie le chiffre 1
    }else if(touche == 5 && missile.tactique == 0 && missile.simple==0 && missile.artillerie == 0 && missile.bombe == 0){   // Si tous les bateaux sont touchés à la dernière munition de l'utilisateur
        partie = 2;                                                                                                         // On renvoie le chiffre 2
    } else if(touche != 5 && missile.tactique == 0 && missile.simple==0 && missile.artillerie == 0 && missile.bombe == 0){  // Si toutes les munitions ont été utilisées mais qu'il reste des bateaux non coulés
        partie = 3;                                                                                                         // On renvoie le chiffre 3
    } else {                                                                                                                // Sinon la partie continue
        partie = 0;                                                                                                         // On renvoie le chiffre 0
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
    while(rejouer != 'O' && rejouer != 'N')                             //Tant que l'utilisateur ne saisi pas une lettre correcte, on redemande
    {
        printf("Veuillez saisir une reponse valide (O/N).\n");
        scanf(" %c", &rejouer);
        rejouer = toupper(rejouer);
    }
    return rejouer;
}
