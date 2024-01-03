#ifndef SAE_C_FINAL_FONCTION_H
#define SAE_C_FINAL_FONCTION_H

#endif //SAE_C_FINAL_FONCTION_H


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
void rechercherVolCompany(struct Vol tab[], int taille_tab);
void afficherPassagersSalleEmbarquement();
void choix_recherche_vol();
void rechercherVolDestination();
void rechercherVolHorraire();
void rechercheVol2();
void chemin_access();


