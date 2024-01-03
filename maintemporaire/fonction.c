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
               "4. Reprogrammer un vol\n"
               "5. Fermer le programme\n\n"
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
                affichage_vol();
                break;
            case 2:
                choix_recherche_vol();
                break;
            case 3:
                afficherPassagersSalleEmbarquement();
                break;
            case 4:
                //reprogrammation_vol(tab, 8,taille_tableau);  il manque la taille du tableau qu on doit déclarer au préalable avec toutes les valeurs, puis demander dans la fonction quel vol doit etre reprogrammé
                break;
            case 5:
                printf("Fermeture du programme\n");
                break;
            default:
                printf("Erreur : Option invalide. Veuillez sélectionner une option valide.\n");
        }
    } while (!ok);

}
/*
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
*/

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


void echanger(struct Vol tab[], int i, int j) {
    struct Vol temp = tab[i];
    tab[i] = tab[j];
    tab[j] = temp;
}

int indice_du_plus_petit_a_partir_de(int i, int taille, struct Vol tab[]) {
    int i_min = i;
    for (int j = i + 1; j < taille; j++) {
        if (tab[j].heure_decollage < tab[i_min].heure_decollage) {
            i_min = j;
        }
    }

    return i_min;
}

void tri_selection_croissante(struct Vol tab[], int taille) {
    for (int i = 0; i < taille - 1; i++) {
        int i_min = indice_du_plus_petit_a_partir_de(i, taille, tab);
        echanger(tab, i, i_min);
    }
}



void affiche_ligne(struct Vol vol){
    printf("%s, %s, %s, %s, %s, %s, %s, %s, %s, %d, %s\n",
    vol.numero_vol, vol.compagnie, vol.destination, vol.numero_comptoir,
    vol.heure_debut_enregistrement, vol.heure_fin_enregistrement,
    vol.salle_embarquement, vol.heure_debut_embarquement,
    vol.heure_fin_embarquement, vol.heure_decollage, vol.etat);


}

void affichage(int taille, struct Vol vol[], int heure){
    for (int j = 1; j < taille; j++) {
        if (vol[j].heure_decollage >= heure && vol[j].heure_decollage <= (heure + 300)){
            affiche_ligne(vol[j]);
        }
    }

}

int affichage_vol() {
    struct Vol tab[50];
    const char* fname = "/Users/Robi6/Downloads/data_vols.csv";
    FILE* fp = fopen(fname, "r");

    if (fp == NULL) {
        perror("Impossible d'ouvrir le fichier");
        return 1;
    }

    int i = 0;
    char ch[TAILLE];
    int taille_tableau = 0;

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
                    tab[i].heure_decollage = atoi(token);
                    break;
                case 9:
                    strcpy(tab[i].etat, token);
                    break;
                default:
                    printf("Une valeur inattendue a été saisie.\n");
            }

            k++;
        }
        taille_tableau++;
        i++;
    }

    fclose(fp);



    tri_selection_croissante(tab, taille_tableau);
    affichage(taille_tableau, tab, 1000);   // la la qu'il faut mettre l'heure actuelle

}


void reprogrammation_vol(struct Vol tab1[], int indice_vol_base, int taille) {
    printf("%d",tab1[indice_vol_base].heure_decollage);
    char etat[1000] ;
    strcpy(etat, tab1[indice_vol_base].etat);
    printf("%s\n",etat);

    int retard = 0;
    if (strcmp(etat, "A l'heure")== 0){
        printf("Le vol choisi est à l'heure, il ne nécessite pas de reprogrammation\n");
        return 0;
    }else if (strcmp(etat, "Annule")== 0){
        printf("Le vol est annulé, il n'est pas possible de le reprogrammer\n");
        return 0;
    }else{
        for (int i = 0; i< strlen(etat); i++) {
            if (etat[i] != '\0' && etat[i] >= '0' && etat[i] <= '9'){

                retard = retard * 10 + (etat[i] - '0');
            }
        }

    }


    int heure = tab1[indice_vol_base].heure_decollage;
    tri_selection_croissante(tab1, taille);
    affichage(taille,tab1,700);
    int indice_vol;
    int T = 1;
    for (int i=0;(i<taille && T);i++){

        if (tab1[i].heure_decollage == heure ){
            T= 0;
            indice_vol = i;
            indice_vol_base  = i;
        }
    }

    int heure_min  = (heure% 100) + (heure / 100)*60 + retard;
    int heure_de_depart_minimum = heure_min;
    int cpt = retard;
    T = 1;
    printf("debut%d\n",tab1[indice_vol_base].heure_decollage);
    while ( indice_vol < taille - 1 && (tab1[indice_vol].heure_decollage% 100) + (tab1[indice_vol].heure_decollage/ 100)*60 < heure_min){
        indice_vol++;
    }
    int vol_suivant;
    printf("departttt%d\n",(heure_min ) % 60 + ((heure_min) / 60) * 100);
    printf("%d\n",tab1[indice_vol].heure_decollage);
    affichage(taille,tab1,700);
    for ( indice_vol; T && indice_vol < taille  && cpt < 60; indice_vol++) {
        vol_suivant = tab1[indice_vol].heure_decollage;
        vol_suivant = (vol_suivant% 100) + (vol_suivant/ 100)*60;
        printf("%d.....%d\n",(vol_suivant) % 60 + ((vol_suivant) / 60) * 100,indice_vol);
        if (vol_suivant - heure_min >= 5){

            printf("%d\n",(heure_min ) % 60 + ((heure_min) / 60) * 100);
            printf("%d\n",(vol_suivant) % 60 + ((vol_suivant) / 60) * 100);
            printf("heure_min: %d\n", heure_min);
            tab1[indice_vol_base].heure_decollage = (heure_min ) % 60 + ((heure_min) / 60) * 100;
            printf("fin%d\n",tab1[indice_vol_base].heure_decollage);

            strcpy(tab1[indice_vol_base].etat, "A l'heure");
            T = 0;
        } else {
            heure_min = vol_suivant + 5;
            cpt = heure_min - heure_de_depart_minimum;
        }
    }
    if (indice_vol == taille && (22*60)-heure_min >= 5){
        tab1[indice_vol_base].heure_decollage = (heure_min ) % 60 + ((heure_min) / 60) * 100;
        strcpy(tab1[indice_vol_base].etat, "A l'heure");
    }

}


