#include <stdio.h>
#include <stdlib.h>

#define taille 1024

#include "fonction.h"

void affichage_general(){
    int choix;

    do {
        printf("Projet GESTION'AIR \n\n");
        printf("1. Affichage des vols de la journée \n"
               "2. Rechecher votre vol\n"
               "3. Afficher la liste des passagers d'une salle d'embarquement\n"
               "4. Fermer le programme\n\n"
               "Veuillez sélectionner une option avec le numéro correspond: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                afficherVolsJournee();
                break;
            case 2:
                rechercherVol();
                break;
            case 3:
                afficherPassagersSalleEmbarquement();
                break;
            case 4:
                printf("Fermeture du programme\n");
                break;
            default:
                printf("Erreur : Option invalide. Veuillez sélectionner une option valide.\n");
        }
    } while (choix < 1 || choix > 4);

}

void afficherVolsJournee() {
    const char* fname = "/Users/angus/Documents/C/SAE/data_vols.csv";
    FILE* fp = fopen(fname, "r");
    if (fp == NULL) {
        perror("Impossible d'ouvrir le fichier");
        return;
    }

    char ch[1024];
    while (fgets(ch, taille, fp) != NULL) {
        printf("%s", ch);
    }

    fclose(fp);
}

void rechercherVol(){


}

void afficherPassagersSalleEmbarquement(){

}
