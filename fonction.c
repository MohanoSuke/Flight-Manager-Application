#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE 1024

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
                choix_recherche_vol();
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
    while (fgets(ch, TAILLE, fp) != NULL) {
        printf("%s\n\n", ch);
    }

    fclose(fp);
}

void rechercherVolCompany() {

    char compagnie[TAILLE];
    char ligne[TAILLE];
    printf("Entrer le nom de la compagnie de votre vol : ");

    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }

    fgets(compagnie, TAILLE, stdin);
    compagnie[strcspn(compagnie, "\n")] = 0;

    const char* fname = "/Users/angus/Documents/C/SAE/data_vols.csv";
    FILE* fp = fopen(fname, "r");
    if (fp == NULL) {
        perror("Impossible d'ouvrir le fichier");
        return;
    }

    while (fgets(ligne, TAILLE, fp) != NULL) {
        if (strstr(ligne, compagnie) != NULL) {
            printf("\n%s\n\n", ligne);
        }
    }

    fclose(fp);
}

void choix_recherche_vol(){
    int choix;

    do {
        printf("\nGESTION'AIR - Recherche vol  \n\n");
        printf("1. Rechercher votre vol avec le nom de votre companie \n"
               "2. Rechercher votre vol avec votre destination \n"
               "3. Rechercher votre vol avec votre heure de décollage\n"
               "4. Fermer le programme\n\n"
               "Veuillez sélectionner une option avec le numéro correspond: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                rechercherVolCompany();
                break;
            case 2:
                rechercherVolDestination();
                break;
            case 3:
                rechercherVolHorraire();
                break;
            case 4:
                printf("Fermeture du programme\n");
                break;
            default:
                printf("Erreur : Option invalide. Veuillez sélectionner une option valide.\n");
        }
    } while (choix < 1 || choix > 4);

}


void afficherPassagersSalleEmbarquement(){

}

void rechercherVolDestination(){

    char destination[TAILLE];
    char ligne[TAILLE];
    printf("Entrer le nom de la de votre destination : ");

    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }

    fgets(destination, TAILLE, stdin);
    destination[strcspn(destination, "\n")] = 0;

    const char* fname = "/Users/angus/Documents/C/SAE/data_vols.csv";
    FILE* fp = fopen(fname, "r");
    if (fp == NULL) {
        perror("Impossible d'ouvrir le fichier");
        return;
    }

    while (fgets(ligne, TAILLE, fp) != NULL) {
        if (strstr(ligne, destination) != NULL) {
            printf("\n%s\n\n", ligne);
        }
    }

    fclose(fp);
}

void rechercherVolHorraire(){
    int heure = 1200;
    const char* fname = "/Users/Robi6/Downloads/data_vols.csv";
    FILE* fp = fopen(fname, "r");
    if (fp == NULL) {
        perror("Impossible d'ouvrir le fichier");
        return;
    }

    char ch[1024];
    while (fgets(ch, taille, fp) != NULL) {

        char* token = strtok(ch, ",");
        int colonne = 1;

        
        while (token != NULL && colonne < 10) {
            token = strtok(NULL, ",");
            colonne++;
        }


        if (token != NULL) {

            int value = 0;
            int i = 0;
            while (token[i] != '\0') {
                if (token[i] >= '0' && token[i] <= '9') {
                    value = value * 10 + (token[i] - '0');
                }
                i++;
            }

            
            if (value >= heure && value <= heure + 300) {
                printf("%s\n\n", ch);
            }
        }





    }

    fclose(fp);

}
