#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAILLE 1024

#include "fonction.h"


char fichierCSV[TAILLE];

struct Vol tabVols[50];
int taille_tabVols = 0;

void chemin_access(){
    printf("Veuillez entrer le chemin du fichier CSV: ");
    fgets(fichierCSV, TAILLE, stdin);
    fichierCSV[strcspn(fichierCSV, "\n")] = 0;

}

void affichage_general(){

    struct tm heureActuelle;
    time_t tempActuel;
    time(&tempActuel);
    heureActuelle = *localtime(&tempActuel);

    int heure = heureActuelle.tm_hour;
    int minute = heureActuelle.tm_min;

    char choix[100];
    int ok = 0;
    long val;

    do {
        printf("Projet GESTION'AIR - L'heure actuelle est : %02d:%02d\n\n", heureActuelle.tm_hour, heureActuelle.tm_min );
        printf("1. Affichage des vols de la journée \n"
               "2. Rechecher votre vol\n"
               "3. Afficher la liste des passagers d'une salle d'embarquement\n"
               "4. Fermer le programme\n\n"
               "Veuillez sélectionner une option avec le numéro correspond: ");
        fgets(choix, sizeof(choix), stdin);
        choix[strlen(choix)-1] = '\0';
        char *res = choix;
        val = strtol(choix, &res, 10);
        if(val!=0){
            ok=1;
        } else if(res!=choix){ // Gestion du cas "0"
            ok=1;
        }
        switch (val) {
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
    } while (!ok);

}

void afficherVolsJournee() {
    struct Vol tab[50];
    FILE* fp = fopen(fichierCSV, "r");

    if (fp == NULL) {
        perror("Impossible d'ouvrir le fichier");
        return;
    }

    int i = 0;
    char ch[TAILLE];

    while (fgets(ch, TAILLE, fp) != NULL) {
        int k = 0;
        char* token = strtok(ch, ",");

        strcpy(tab[i].numero_vol, token);

        while (token != NULL && k < 10) {
            token = strtok(NULL, ",");

            switch (k) {
                case 0:
                    strcpy(tab[i].compagnie, token);
                    break;
                case 1:
                    strcpy(tab[i].destination, token);
                    break;
                case 2:
                    strcpy(tab[i].numero_comptoir, token);
                    break;
                case 3:
                    strcpy(tab[i].heure_debut_enregistrement, token);
                    break;
                case 4:
                    strcpy(tab[i].heure_fin_enregistrement, token);
                    break;
                case 5:
                    strcpy(tab[i].salle_embarquement, token);
                    break;
                case 6:
                    strcpy(tab[i].heure_debut_embarquement, token);
                    break;
                case 7:
                    strcpy(tab[i].heure_fin_embarquement, token);
                    break;
                case 8:
                    strcpy(tab[i].heure_decollage, token);
                    break;
                case 9:
                    strcpy(tab[i].etat, token);
                    break;
                default:
                    printf("Une valeur inattendue a été saisie.\n");
            }

            k++;
        }

        i++;
    }
    fclose(fp);

    for (int j = 0; j < i; j++) {
        printf("\nNuméro de vol: %s, Compagnie: %s, Destination: %s, Numéro comptoir: %s, Heure début enregistrement: %s, Heure fin enregistrement: %s, Salle embarquement: %s, Heure début embarquement: %s, Heure fin embarquement: %s, Heure décollage: %s, État: %s\n\n\n",
               tab[j].numero_vol, tab[j].compagnie, tab[j].destination, tab[j].numero_comptoir,
               tab[j].heure_debut_enregistrement, tab[j].heure_fin_enregistrement, tab[j].salle_embarquement,
               tab[j].heure_debut_embarquement, tab[j].heure_fin_embarquement, tab[j].heure_decollage, tab[j].etat);
    }
    return;
}


void rechercherVolCompany(struct Vol tab[], int taille_tab) {

    char compagnie[TAILLE];

    printf("Entrer le nom de la compagnie de votre vol : ");

    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }

    fgets(compagnie, TAILLE, stdin);
    compagnie[strcspn(compagnie, "\n")] = 0;

    for (int j = 0; j < taille_tab; j++) {
        if (strstr(tab[j].compagnie, compagnie) != NULL) {
            printf("\nNuméro de vol: %s, Compagnie: %s, Destination: %s\n", tab[j].numero_vol, tab[j].compagnie, tab[j].destination);
        }
    }
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
                rechercherVolCompany(tabVols, taille_tabVols);
                break;
            case 2:
                rechercherVolDestination();
                break;
            case 3:
                rechercheVol2();
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

    FILE* fp = fopen(fichierCSV, "r");
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
    FILE* fp = fopen(fichierCSV, "r");
    if (fp == NULL) {
        perror("Impossible d'ouvrir le fichier");
        return;
    }

    char ch[1024];
    while (fgets(ch, TAILLE, fp) != NULL) {

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

void rechercheVol2(){
    char ligne[TAILLE];
    int horraire;

    printf("Veuillez entrer l'heure de votre vol: ");
    scanf("%d", &horraire);

    char heureStr[6];
    sprintf(heureStr, "%d", horraire);

    FILE* fp = fopen(fichierCSV, "r");
    if (fp == NULL) {
        perror("Impossible d'ouvrir le fichier");
        return;
    }

    while (fgets(ligne, TAILLE, fp) != NULL) {
        if (strstr(ligne, heureStr) != NULL) {
            printf("\n%s\n\n", ligne);
        }
    }

    fclose(fp);
}




