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


    rewind(file); //on remonte le curseur en haut du fichier
    fgets(temp, 20, file); // on saisit la première valeur du fichier
    charger = atoi(temp); // on convertit cette valeur en entier (ce sera soit 0 soit 1)

    printf("\n\n=======================================\nMENU\n=======================================\n\n"
           "Que voulez vous faire : \n"
           "-Demarrer une nouvelle partie (D)\n");
    if(charger == 1){ // si le fichier contient une sauvegarde (sinon, l'utilisateur ne peut que démarrer ou quitter)
        printf("-Charger votre derniere partie (C)\n");
    }
    printf("-Quitter (Q)\n\n");
    scanf(" %c", &demarrer); // on réupère le choix de l'utilisateur
    demarrer = toupper(demarrer); // on le met en majuscule (pour qu'il puisse écrire en majuscule ou minuscule)
    if(charger == 0){ //si il n'y a pas de sauvegarde dans le fichier
        while(demarrer != 'D' && demarrer != 'Q') { //on lui demande de recommencer tant qu'il n'a pas saisit de valeur valide
            printf("Veuillez saisir une reponse valide (D/Q):\n");
            scanf(" %c", &demarrer); // on récupère le choix de l'utilisateur
            demarrer = toupper(demarrer); // on met son choix en majuscule
        }
    } else {
        while(demarrer != 'D' && demarrer != 'Q' && demarrer != 'C'){ //on lui demande de recommencer tant qu'il n'a pas saisit de valeur valide
            printf("Veuillez saisir une reponse valide (D/C/Q):\n");
            scanf(" %c", &demarrer); // on récupère le choix de l'utilisateur
            demarrer = toupper(demarrer); //on le met en majuscule
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
    scanf(" %c", &mode); // on récupère le choix de l'utilsateur
    mode = toupper(mode); // on le met en majuscule
    while(mode != 'C' && mode != 'B' && mode != 'A') { //on lui demande de recommencer tant que la valeur saisie n'est pas correcte
        printf("Veuillez saisir une reponse valide (C/B/A):\n");
        scanf(" %c", &mode); //on récupère le choix de l'utilisateur
        mode = toupper(mode); // on le met en majuscule
    }
    return mode; //on renvoie son choix
}


char demande_difficulte()
{
    char rep;
    printf("\n\n=======================================\nDIFFICULTE\n=======================================\n\n"
           "\nQuelle difficulte voulez-vous ?\n"
           "-Facile (F)\n"
           "-Moyen (M)\n"
           "-Difficile (D)\n");
    scanf(" %c", &rep); // on récupère le choix de l'utilisateur
    rep = toupper(rep); // on le met en majuscule
    while(rep != 'F' && rep != 'M' && rep != 'D') { // boucle tant que valeur saisie non valide
        printf("Veuillez saisir une reponse valide (F/M/D):\n");
        scanf(" %c", &rep); // récupère choix utilisateur
        rep = toupper(rep); //met en majuscule
    }
    return rep; //retourne le choix de l'utilisateur
}

int game(Grid tableau_joueur, Grid tableau_ordi, Inventory missile, Boat bateau[], int NB_bateau, char mode, int nombre_tour, int charger){
    int partie;
    char missile_utilise,sauvegarde;
    Actif deplacement_actif={0};
    Impact point_impact;

    if (nombre_tour == 1) { //on donne ces informations si on est au premier tour
        affichage_missile_depart(missile);
        printf("Voici le nombre de bateaux que l'ordinateur va placer aleatoirement:\n\n");
        affichage_nb_bateau(bateau, NB_bateau);
        affichage_tableau(tableau_joueur);
    } else if(charger == 1){ //si on charge une partie existante
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
        if (mode == 'C' || mode == 'A') { //on affiche le tableau sauf si on est en mode Blind
            affichage_tableau(tableau_joueur);
            affichage_tableau(tableau_ordi); //Décommenter pour voir le tableau de l'ordinateur en même temps que le tableau du joueur et comparer
        }
    }

    do {
        printf("\n\n=======================================\nTOUR %d\n=======================================\n\n",
               nombre_tour);

        if(nombre_tour!=1 && mode=='A') {
            deplacement_actif.decision = rand()%3; // Decision de l'ordi si il veut bouger un bateau ou pas
            if(deplacement_actif.decision != 0) { //Nous avons choisi que le bateau avait 2 chances sur 3 de bouger
                deplacement_actif = verification_deplacement_bateau_mode_active(tableau_ordi,tableau_joueur, bateau ,NB_bateau);
                if (deplacement_actif.tableau_active[deplacement_actif.choix_bateau] == bateau[deplacement_actif.choix_bateau].identification && deplacement_actif.verification_mode_active!=5){
                    //Si le bateau choisi est bien identifié dans le tableau de verfication des bateaux pouvant se déplacer ET qu'au moins un bateau peut se déplacer
                    bateau[deplacement_actif.choix_bateau] = deplacement_bateau_mode_active(&tableau_ordi,bateau,deplacement_actif); // On déplace un bateau
                }
            }
        }

        missile_utilise = demande_missile(missile);
        point_impact = saisie_tir(tableau_joueur);
        printf("Le missile tombera en %c%d.\n\n", 'A' + point_impact.colonne, point_impact.ligne);

        if (missile_utilise == 'A') { //si l'utilisateur utilise un missile d'artillerie

            missile.artillerie = missile.artillerie - 1; //il en pert un de son inventaire
            tir_artillerie(&tableau_joueur, &tableau_ordi, point_impact, NB_bateau, bateau,mode);

        } else if (missile_utilise == 'T') { //si l'utilisateur utilise un missile tactique

            missile.tactique = missile.tactique - 1; //il en pert un de son inventaire
            tir_tactique(&tableau_joueur, &tableau_ordi, point_impact,NB_bateau,bateau,mode);

        } else if (missile_utilise == 'B') { //si l'utilisateur utilise une bombe

            missile.bombe = missile.bombe - 1; //il en pert une de son inventaire
            tir_bombe(&tableau_joueur, &tableau_ordi, point_impact, NB_bateau, bateau,mode);

        } else { //si l'utilisateur utilise un missile simple

            missile.simple = missile.simple - 1;  //il en pert un de son inventaire
            tir_simple(&tableau_joueur, &tableau_ordi,point_impact,mode,NB_bateau,bateau);

        }

        nombre_tour++; //le tour est fini, on l'incrémente donc de 1
        partie = fin_partie(bateau, missile, NB_bateau);

        if (partie==0){ // si il reste munitions à l'utilisateur, des bateaux à détruire et qu'il veut continuer
            printf("\nVoici le nombre de bateaux qu'il vous reste a detruire:\n\n");
            affichage_nb_bateau(bateau, NB_bateau);
            affichage_missile(missile);
            if (mode == 'C' || mode == 'A') { //on affiche le tableau sauf en mode blind
                affichage_tableau(tableau_joueur);
                printf("\n");
                affichage_tableau(tableau_ordi); //Décommenter pour voir le tableau de l'ordinateur en même temps que le tableau du joueur et comparer
            }
            printf("\nVoulez continuer ou sauvegarder et quitter (C/S)?\n");
            scanf(" %c", &sauvegarde); // on récupère le choix de l'utilisateur
            sauvegarde = toupper(sauvegarde);
            while (sauvegarde != 'C' && sauvegarde != 'S') { //on le demande de recommencer tant que la valeur saisie est non valide
                printf("\nVeuillez saisir C pour continuer ou S pour sauvegarder.\n");
                scanf(" %c", &sauvegarde); // récupère choix utilisateur
                sauvegarde = toupper(sauvegarde); // met en majuscule
            }
            if (sauvegarde == 'S') { // si l'utilisateur veut sauvegarder
                FILE *file = fopen("sauvegarde_jeu.txt", "r"); // on ouvre le fichier en mode lecture
                partie = demande_sauvegarde(file, tableau_joueur, tableau_ordi, missile, bateau, NB_bateau, nombre_tour, mode);
            }
        }
    } while (partie == 0); // on répète ceci tant que l'utilisateur peut et veut continuer à jouer

    if (partie<=3) { // on affiche le tableau sauf si il sauvegarde
        affichage_tableau(tableau_joueur);
    }

    return partie; // on retourne la situation de la partie (continue/gagnée/sauvegardée/perdue)
}

Impact saisie_tir(Grid tableau_joueur){
    Impact tir_actuel;
    char ligne[2]={0};
    char T[3]={0};
    char lettre;
    int chiffre;
    int verification;

    do{ //on fait ceci
        verification=0;
        printf("En quelle case voulez vous tirer ( de A0 a J9) ?\n");
        scanf(" %s", &T); // on récupère le choix de l'utilisateur
        lettre = toupper(T[0]); // on met la lettre en majuscule
        ligne[0] = T[1]; // on transmet le chiffre dans un autre tableau de caractère
        chiffre = atoi(ligne); // pour le convertir en entier
        tir_actuel.colonne= lettre-'A'; // on obtient un chiffre correspondant à la colonne
        tir_actuel.ligne= chiffre; // et un chiffre correspondant à la ligne
        while( tir_actuel.colonne < 0 || tir_actuel.colonne > 9 || tir_actuel.ligne <0 || tir_actuel.ligne>9 || T[2]!= '\0') // On vérifie que le tir est bien dans la grille de jeu
        {
            printf("Votre tir n'est pas valide (case inconnue), veuillez recommencer ...\n");
            scanf(" %s", &T);// on récupère le choix de l'utilisateur
            lettre = toupper(T[0]);// on met la lettre en majuscule
            ligne[0] = T[1]; // on transmet le chiffre dans un autre tableau de caractère
            chiffre = atoi(ligne);// pour le convertir en entier
            tir_actuel.colonne= lettre-'A';// on obtient un chiffre correspondant à la colonne
            tir_actuel.ligne= chiffre;// et un chiffre correspondant à la ligne
        }
        if (tableau_joueur.grille[1 + tir_actuel.ligne][1 + tir_actuel.colonne] == 'O' ||
            tableau_joueur.grille[1 + tir_actuel.ligne][1 + tir_actuel.colonne] == 'X') {   // On vérifie si l'utilisateur ne tire pas sur une case déjà touchée
            verification = 1;
            printf("Votre tir n'est pas valide (case deja touchee), veuillez recommencer ...\n");
        }
    }while(verification == 1); //jusqu'à ce que l'utilisateur choisisse une case valide

    return tir_actuel; // on retourne les coordonnes du tir
}

Actif verification_deplacement_bateau_mode_active(Grid tableau_ordi, Grid tableau_joueur, Boat bateau[],int NB_bateau){
    int i,j;
    Actif deplacement;

    deplacement.verification_mode_active = 0;
    for (i = 0; i < NB_bateau; i++) { //on fait ceci pour tout les bateaux
        if (bateau[i].touche == 0) { // si le bateau n'est pas touche
            deplacement.tableau_active[i] = bateau[i].identification; // il aura la possibilité de se déplacer
        } else { //sinon
            deplacement.tableau_active[i] = ' '; // il ne pourra pas se déplacer
            deplacement.verification_mode_active++;// On incrémente de 1 le nombre de bateaux non déplacables
        }
    }
    deplacement.tableau_active[i] = '\0'; // on rajoute le caractère de finde chaîne
    //printf("%s", tableau_active);

    if (deplacement.verification_mode_active != 5) { // si il reste au moins un bateau non touche

        do {
            do {
                deplacement.choix_bateau = rand() % 5;
            } while (deplacement.tableau_active[deplacement.choix_bateau] == ' '); // Choix d'un bateau aléatoire non touché

            //printf("bateau choisie : %c, H_V = %d", bateau[choix_bateau].identification,bateau[choix_bateau].H_V);
            deplacement.max_gauche = 0;
            deplacement.max_droite = 0;
            deplacement.max_haut = 0;
            deplacement.max_bas = 0;
            i = 1;
            j = 0;
            if (bateau[deplacement.choix_bateau].H_V == 0) { // si le bateau est horizontal
                do {
                    if (tableau_joueur.grille[bateau[deplacement.choix_bateau].ligne + 1][bateau[deplacement.choix_bateau].colonne -
                                                                                          i +
                                                                                          1] == '_' &&
                        tableau_ordi.grille[bateau[deplacement.choix_bateau].ligne + 1][bateau[deplacement.choix_bateau].colonne -
                                                                                        i +
                                                                                        1] ==
                        ' ') // si la case directement à gauche du bateau n'a pas été touché et ne contient pas un autre bateau dans le tableau de l'ordinateur
                    {
                        deplacement.max_gauche++; // on incrémente le déplacement maximal gauche de 1
                    }
                    i++;
                } while (i < 4 && deplacement.max_gauche + 1 == i); // jusqu'a ce que le déplacement max soit 3 ou qu'il y ait un bateau sur la route

                //printf("deplacement max gauche : %d", deplacement_max_gauche); // Ligne à décommenter si vous voulez voir le déplacement max gauche du bateau choisi

                do {
                    if (tableau_joueur.grille[bateau[deplacement.choix_bateau].ligne + 1][bateau[deplacement.choix_bateau].colonne +
                                                                                          bateau[deplacement.choix_bateau].taille_bateau +
                                                                                          j + 1] == '_' &&
                        tableau_ordi.grille[bateau[deplacement.choix_bateau].ligne + 1][bateau[deplacement.choix_bateau].colonne +
                                                                                        bateau[deplacement.choix_bateau].taille_bateau +
                                                                                        j + 1] == ' ') { //si la case directement à droite du bateau n'a pas été touché et ne contient pas un autre bateau
                        deplacement.max_droite++; // on incrémente le déplacement max droite de 1
                    }
                    j++;
                } while (j < 3 && deplacement.max_droite == j);//jusqu'a ce que le déplacement max soit 3 ou qu'il y ait un bateau sur la route

                //printf("deplacement max droite : %d", deplacement_max_droite); // Ligne à décommenter si vous voulez voir le déplacement max droite du bateau choisi

            } else { // on fait la même démarche mais pour les bateaux verticaux ayant qui se déplaceront vers le haut ou le bas

                do {
                    if (tableau_joueur.grille[bateau[deplacement.choix_bateau].ligne - i + 1][
                                bateau[deplacement.choix_bateau].colonne +
                                1] == '_' &&
                        tableau_ordi.grille[bateau[deplacement.choix_bateau].ligne - i + 1][
                                bateau[deplacement.choix_bateau].colonne +
                                1] == ' ') {
                        deplacement.max_haut++;
                    }
                    i++;
                } while (i < 4 && deplacement.max_haut + 1 == i);

                //printf("deplacement max haut : %d", deplacement_max_haut); // Ligne à décommenter si vous voulez voir le déplacement max haut du bateau choisi

                do {
                    if (tableau_joueur.grille[bateau[deplacement.choix_bateau].ligne +
                                              bateau[deplacement.choix_bateau].taille_bateau +
                                              j + 1][bateau[deplacement.choix_bateau].colonne + 1] == '_' &&
                        tableau_ordi.grille[bateau[deplacement.choix_bateau].ligne +
                                            bateau[deplacement.choix_bateau].taille_bateau +
                                            j + 1][bateau[deplacement.choix_bateau].colonne + 1] == ' ') {
                        deplacement.max_bas++;
                    }
                    j++;
                } while (j < 3 && deplacement.max_bas == j);

                //printf("deplacement max bas : %d", deplacement_max_bas); // Ligne à décommenter si vous voulez voir le déplacement max bas du bateau choisi

            }


            if (deplacement.max_droite == 0 && deplacement.max_gauche == 0 && deplacement.max_bas == 0 &&
                deplacement.max_haut == 0) { // si la baeatu choisi n'a pas de déplacement possible
                deplacement.tableau_active[deplacement.choix_bateau] = ' '; // on enlève le bateau choisi des bateaux déplaçables
                deplacement.verification_mode_active++; // on incrémente de 1 le nombre de bateaux non déplaçables
            }

        } while (deplacement.tableau_active[deplacement.choix_bateau] == ' ' && deplacement.verification_mode_active != 5); // tant qu'on a pas trouvé de bateau déplaçable et qu'il en reste au moins 1
    } else{
        deplacement.choix_bateau = 0;
    }
    return deplacement;
}


Boat deplacement_bateau_mode_active(Grid *tableau_ordi, Boat bateau[], Actif deplacement){

    int i;

    if (bateau[deplacement.choix_bateau].H_V == 0) {    // Si le bateau à déplacer est horizontal
        deplacement.mouvement_bateau = rand() % (deplacement.max_gauche + deplacement.max_droite) + 1; // On choisi aléatoirement le déplacement du bateau par rapport à l'horizontal
        if (deplacement.mouvement_bateau <= deplacement.max_gauche) {   //Si le déplacement choisi est inférieur au déplcement max gauche, le bateau se déplacera à gauche
            for (i = 1; i < (deplacement.mouvement_bateau + 1); i++) {  // On répète le décalage du bateau jusqu'à ce que le déplacement choisi soit atteint
                tableau_ordi->grille[bateau[deplacement.choix_bateau].ligne + 1][bateau[deplacement.choix_bateau].colonne +bateau[deplacement.choix_bateau].taille_bateau -i + 1] = ' '; // La case du bateau la plus à droite disparais sur le tableau ordi
                tableau_ordi->grille[bateau[deplacement.choix_bateau].ligne + 1][bateau[deplacement.choix_bateau].colonne -i +1] = bateau[deplacement.choix_bateau].identification; // La case du bateau la plus à gauche plus un décalage de 1 est remplacé par la lettre du bateau sur le tableau ordi
            }
            bateau[deplacement.choix_bateau].colonne = bateau[deplacement.choix_bateau].colonne - deplacement.mouvement_bateau; // On remplace l'ancienne position sur la colonne par la nouvelle
        } else { //Sinon le bateau se déplacera à droite
            for (i = 0; i < (deplacement.mouvement_bateau - deplacement.max_gauche); i++) { // On répète le décalage du bateau jusqu'à ce que le déplacement choisi soit atteint
                tableau_ordi->grille[bateau[deplacement.choix_bateau].ligne + 1][bateau[deplacement.choix_bateau].colonne +i +1] = ' '; // La case du bateau la plus à gauche disparais sur le tableau ordi
                tableau_ordi->grille[bateau[deplacement.choix_bateau].ligne + 1][bateau[deplacement.choix_bateau].colonne +bateau[deplacement.choix_bateau].taille_bateau +i +1] = bateau[deplacement.choix_bateau].identification; // La case du bateau la plus à droite plus un décalage de 1 est remplacé par la lettre du bateau sur le tableau ordi

            }
            bateau[deplacement.choix_bateau].colonne = bateau[deplacement.choix_bateau].colonne + (deplacement.mouvement_bateau - deplacement.max_gauche); // On remplace l'ancienne position sur la colonne par la nouvelle
        }
        // On a pas besoin de changer la ligne du bateau pour un déplacement horizontal car le bateau se déplace sur la même ligne
    } else {    // Sinon le bateau a déplacer est vertical
        deplacement.mouvement_bateau = rand() % (deplacement.max_bas + deplacement.max_haut) + 1;// On choisi aléatoirement le déplacement du bateau sur la verticale
        if (deplacement.mouvement_bateau <= deplacement.max_haut) {
            for (i = 1; i < (deplacement.mouvement_bateau + 1); i++) {
                tableau_ordi->grille[bateau[deplacement.choix_bateau].ligne +bateau[deplacement.choix_bateau].taille_bateau -i + 1][bateau[deplacement.choix_bateau].colonne + 1] = ' ';
                tableau_ordi->grille[bateau[deplacement.choix_bateau].ligne - i + 1][bateau[deplacement.choix_bateau].colonne +1] = bateau[deplacement.choix_bateau].identification;
            }
            bateau[deplacement.choix_bateau].ligne =bateau[deplacement.choix_bateau].ligne - deplacement.mouvement_bateau;
        } else {
            for (i = 0; i < (deplacement.mouvement_bateau - deplacement.max_haut); i++) {
                tableau_ordi->grille[bateau[deplacement.choix_bateau].ligne + i + 1][bateau[deplacement.choix_bateau].colonne +1] = ' ';
                tableau_ordi->grille[bateau[deplacement.choix_bateau].ligne +bateau[deplacement.choix_bateau].taille_bateau +i + 1][bateau[deplacement.choix_bateau].colonne +1] = bateau[deplacement.choix_bateau].identification;
            }
            bateau[deplacement.choix_bateau].ligne =bateau[deplacement.choix_bateau].ligne + (deplacement.mouvement_bateau - deplacement.max_haut);
        }
        // On a pas besoin de changer la colonne du bateau pour un déplacement vertical car le bateau se déplace sur la même colonne
    }
    //printf("Un bateau de taille %d s'est deplace en nouvelle position : %c %d \n",bateau[choix_bateau].taille_bateau, 'A' + bateau[choix_bateau].colonne,bateau[choix_bateau].ligne);
    // Ligne à décommenter si vous voulez voir la nouvelle position du bateau choisi
    printf("Un bateau s'est deplace");

    return bateau[deplacement.choix_bateau];
}


int fin_partie(Boat bateau[],Inventory missile,int NB_bateau){
    int i;
    int touche=0;
    int partie;
    for (i=0;i<NB_bateau;i++){ //on répète cette boucle pour chaque bateau
        if (bateau[i].touche == bateau[i].taille_bateau) { // si un bateau est touché autant de fois qu'il a de cases (si il est coulé)
            touche++; //on incremente le nombre de bateaux coulés de 1
        }
    }
    if(touche == 5 && (missile.tactique != 0 || missile.simple!=0 || missile.artillerie != 0 || missile.bombe != 0)){ //si tout les bateaux sont touches et qu'il lui reste au moins une munition
        partie = 1; // on renvoie le chiffre 1
    }else if(touche == 5 && missile.tactique == 0 && missile.simple==0 && missile.artillerie == 0 && missile.bombe == 0){ //si tout les bateaux sont touches à la dernière munition de l'utilisateur
        partie = 2; // on renvoie le chiffre 2
    } else if(touche != 5 && missile.tactique == 0 && missile.simple==0 && missile.artillerie == 0 && missile.bombe == 0){ //si toutes les munitions ont été utilisées mais qu'il reste des bateaux non coulés
        partie = 3; // on renvoie le chiffre 3
    } else {
        partie = 0; //on renvoie le chiffre 0
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
