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
    int prix_billet;
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
    int heure_decollage;    //int
    char etat[1000];    //int
};

// Déclarations de nos fonctions

void affichage_general();
void afficherVolsJournee();
void afficherPassagersSalleEmbarquement();
void choix_recherche_vol(struct Vol tab[], int taille);
void rechercherVolHorraire();
void rechercheVol2();
void chemin_access();
void echanger(struct Vol tab[], int i, int j);
int indice_du_plus_petit_a_partir_de(int i, int taille, struct Vol tab[]);
void tri_selection_croissante(struct Vol tab[], int taille);
void affiche_ligne(struct Vol vol);
void affichage(int taille, struct Vol vol[], int heure);
int affichage_vol();
void reprogrammation_vol(struct Vol tab1[], int indice_vol_base, int taille);
void rechercherVolDestination(struct Vol vols[], int taille);
void rechercherVolCompagnie(struct Vol vols[], int taille);
int HeureFormattee();
int calculerage(char* datenaissance);
void affichage2(struct passager tab[], int taille);
void echanger2(struct passager tab[], int i, int j);
void tri_selection2(struct passager tab[], int taille);



#endif //SAE_C_FINAL_FONCTION_H


