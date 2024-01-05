#ifndef SAE_C_FINAL_FONCTION_H
#define SAE_C_FINAL_FONCTION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAILLE_MAX 1024

struct passager {
    char nom[50];
    char prenom[50];
    char date_naissance[100];
    char numero_siege[10];
    char prix_billet[10];
};

struct Vol {
    char numero_vol[1000];
    char compagnie[1000];
    char destination[1000];
    char numero_comptoir[1000];
    char heure_debut_enregistrement[1000];  //int
    char heure_fin_enregistrement[1000];  //int
    char salle_embarquement[1000];
    char heure_debut_embarquement[1000];   //int
    char heure_fin_embarquement[1000];  //int
    char heure_decollage[1000];    //int
    char etat[1000];    //int
};

// Déclarations des fonctions pour la gestion des vols
void affichage_general();
void afficherVolsJournee();
void rechercherVolCompany(struct Vol tab[], int taille_tab);
void afficherPassagersSalleEmbarquement();
void choix_recherche_vol();
void rechercherVolDestination();
void rechercherVolHorraire();
void rechercheVol2();
void chemin_access();


#endif //SAE_C_FINAL_FONCTION_H
