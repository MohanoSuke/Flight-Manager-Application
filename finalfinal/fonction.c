#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAILLE 1024

#include "fonction.h"

char fichierCSV[TAILLE];

int taille_tabVols = 192;


void chemin_access(){
    printf("Veuillez entrer le chemin du fichier CSV: ");
    fgets(fichierCSV, TAILLE, stdin); // Permet la saisie au clavier de l'user (char)
    fichierCSV[strcspn(fichierCSV, "\n")] = 0; // retire le saut de ligne
}

void affichage_general(){

    struct Vol tab[taille_tabVols];
    FILE* fp = fopen(fichierCSV, "r");

    if (fp == NULL) {
        perror("Impossible d'ouvrir le fichier");
        return;
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
                    printf("Une valeur inattendue a ete saisie.\n");
            }

            k++;
        }
        taille_tableau++;
        i++;
    }

    fclose(fp);

    struct tm heureActuelle;
    time_t tempActuel;
    time(&tempActuel);
    heureActuelle = *localtime(&tempActuel);

    char choix[100];
    int ok = 0;
    long val;

    do {
        printf("\033[1;34m"); // Texte en bleu
        printf("Projet GESTION'AIR - L'heure actuelle est : %02d:%02d\n\n", heureActuelle.tm_hour, heureActuelle.tm_min);
        printf("\033[0m"); // Rétablir la couleur par défaut

        printf("1. Affichage des vols de la journee\n"
            "2. Recherche de votre vol\n"
            "3. Afficher la liste des passagers d'un vol selon l'ordre d'embarquement\n"
            "4. Reprogrammer un vol\n"
            "5. Afficher l'ordre des passgers pour l'embarquement et l'enregistrement");

        // Utilise les codes ANSI pour imprimer la ligne en rouge
        printf("\033[1;31m5. Fermer le programme\n\n\033[0m");
        printf("Veuillez selectionner une option avec le numero correspondant : ");
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
                affichage_vol(tab, taille_tableau);
                break;
            case 2:
                choix_recherche_vol(tab, taille_tableau);
                break;
            case 3:
                //afficherPassagersSalleEmbarquement();
                embarquement(tab, taille_tableau);
                printf("------------------------");
                enregistrement(tab, taille_tableau);
                break;
            case 4:
                reprogrammation_vol(tab, taille_tableau);
                break;
            case 5:
                embarquement(tab, taille_tableau);
                printf("------------------------");
                enregistrement(tab, taille_tableau);
            case 6:
                printf("Fermeture du programme\n");
                break;

            default:
                printf("Erreur : Option invalide. Veuillez selectionner une option valide.\n");
        }
    } while (!ok);

}

void choix_recherche_vol(struct Vol tab[], int taille) {

    char choix[100];
    int ok = 0;
    long val;

    do {
        ok = 0;
        printf("\033[1;34m"); // Texte en bleu
        printf("\nGESTION'AIR - Recherche vol  \n\n");
        printf("\033[0m"); // Retablir la couleur par defaut
        printf("1. Rechercher votre vol avec le nom de votre compagnie \n"
               "2. Rechercher votre vol avec votre destination \n"
               "3. Rechercher votre vol avec votre heure de decollage\n"
               "4. Rechercher votre vol avec une recherche avancée\n");
        printf("\033[1;31m5. Fermer le programme\n\n\033[0m");
        printf("Veuillez selectionner une option avec le numero correspond: ");
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
                rechercherVolCompagnie(tab, taille);
                break;
            case 2:
                rechercherVolDestination(tab, taille);
                break;
            case 3:
                rechercherVolHorraire(tab, taille);
                break;
            case 4:
                rechercherVolAvancee(tab,taille);
            case 5:
                printf("Fermeture du programme\n");
                break;
            default:
                printf("Erreur : Option invalide. Veuillez selectionner une option valide.\n");
        }
    } while (!ok);

}

void rechercherVolCompagnie(struct Vol vols[], int taille) {
    char compagnieRecherchee[TAILLE];
    printf("Entrer le nom de la compagnie aerienne : ");

    fgets(compagnieRecherchee, TAILLE, stdin);
    compagnieRecherchee[strcspn(compagnieRecherchee, "\n")] = 0;

    int trouve = 0;
            printf("\n\033[1;36m"); // Titre en cyan
            printf(" --------------------------------------------------------------------------------------------------------------------------------------\n");
            printf("| Numero | Compagnie       | Destination | Comptoir | debutEnr | finEnr | SalleEmb | debutEmb | finEmb | Decollage | EtatVol           |\n");
            printf(" --------------------------------------------------------------------------------------------------------------------------------------\n");
            printf("\033[0m"); // Retablir la couleur par defaut
    for (int i = 0; i < taille; i++) {
        if (strcmp(vols[i].compagnie, compagnieRecherchee) == 0) {
            printf(" --------------------------------------------------------------------------------------------------------------------------------------\n");
            printf("| %-6s | %-15s | %-11s | %-8s | %-8s | %-6s | %-8s | %-8s | %-6s | %-9d | %-17s |\n",
                   vols[i].numero_vol, vols[i].compagnie, vols[i].destination,
                   vols[i].numero_comptoir, vols[i].heure_debut_enregistrement,
                   vols[i].heure_fin_enregistrement, vols[i].salle_embarquement,
                   vols[i].heure_debut_embarquement, vols[i].heure_fin_embarquement,
                   vols[i].heure_decollage, vols[i].etat);
            printf(" --------------------------------------------------------------------------------------------------------------------------------------\n");

            trouve = 1;
        }
    }

    if (!trouve) {
        printf("\nAucun vol trouve pour la compagnie '%s'.\n", compagnieRecherchee);
    }
}

void rechercherVolDestination(struct Vol vols[], int taille) {
    char destinationRecherchee[TAILLE];
    printf("Entrer le nom de la de votre destination : ");

    fgets(destinationRecherchee, TAILLE, stdin);
    destinationRecherchee[strcspn(destinationRecherchee, "\n")] = 0;

    int trouve = 0;
            printf("\n\033[1;36m"); // Titre en cyan
            printf(" --------------------------------------------------------------------------------------------------------------------------------------\n");
            printf("| Numero | Compagnie       | Destination | Comptoir | debutEnr | finEnr | SalleEmb | debutEmb | finEmb | Decollage | EtatVol           |\n");
            printf(" --------------------------------------------------------------------------------------------------------------------------------------\n");
            printf("\033[0m"); // Retablir la couleur par defaut
    for (int i = 0; i < taille; i++) {
        if (strstr(vols[i].destination, destinationRecherchee) != NULL) {
            printf(" --------------------------------------------------------------------------------------------------------------------------------------\n");
            printf("| %-6s | %-15s | %-11s | %-8s | %-8s | %-6s | %-8s | %-8s | %-6s | %-9d | %-17s |\n",
                   vols[i].numero_vol, vols[i].compagnie, vols[i].destination,
                   vols[i].numero_comptoir, vols[i].heure_debut_enregistrement,
                   vols[i].heure_fin_enregistrement, vols[i].salle_embarquement,
                   vols[i].heure_debut_embarquement, vols[i].heure_fin_embarquement,
                   vols[i].heure_decollage, vols[i].etat);
            printf(" --------------------------------------------------------------------------------------------------------------------------------------\n");

            trouve = 1;
        }
    }

    if (!trouve) {
        printf("Aucun vol trouve pour la compagnie '%s'.\n", destinationRecherchee);

    }
}

void rechercherVolHorraire(struct Vol vols[], int taille){
    char VolHorraire[TAILLE];
    printf("Entrer l'horaire de vol (HHMM) : ");

    fgets(VolHorraire, TAILLE, stdin);
    VolHorraire[strcspn(VolHorraire, "\n")] = 0;

    int horraire = atoi(VolHorraire);

    int trouve = 0;
            printf("\n\033[1;36m"); // Titre en cyan
            printf(" --------------------------------------------------------------------------------------------------------------------------------------\n");
            printf("| Numero | Compagnie       | Destination | Comptoir | debutEnr | finEnr | SalleEmb | debutEmb | finEmb | Decollage | EtatVol           |\n");
            printf(" --------------------------------------------------------------------------------------------------------------------------------------\n");
            printf("\033[0m"); // R�tablir la couleur par d�faut
    for (int i = 0; i < taille; i++) {
        if (vols[i].heure_decollage == horraire) {
            printf(" --------------------------------------------------------------------------------------------------------------------------------------\n");
            printf("| %-6s | %-15s | %-11s | %-8s | %-8s | %-6s | %-8s | %-8s | %-6s | %-9d | %-17s |\n",
                   vols[i].numero_vol, vols[i].compagnie, vols[i].destination,
                   vols[i].numero_comptoir, vols[i].heure_debut_enregistrement,
                   vols[i].heure_fin_enregistrement, vols[i].salle_embarquement,
                   vols[i].heure_debut_embarquement, vols[i].heure_fin_embarquement,
                   vols[i].heure_decollage, vols[i].etat);
            printf(" --------------------------------------------------------------------------------------------------------------------------------------\n");

            trouve = 1;
        }
    }

    if (!trouve) {
        printf("Aucun vol trouve pour l'horaire %d.\n", horraire);
    }
}

void rechercherVolAvancee(struct Vol vols[], int taille){
    char saisie[TAILLE];
    printf("Entrer le nom de la compagnie et votre destination : ");
    fgets(saisie, TAILLE, stdin);
    saisie[strcspn(saisie, "\n")] = 0;

    char compagnieRecherchee[TAILLE];
    char destinationRecherchee[TAILLE];

    if (sscanf(saisie, "%s %s", compagnieRecherchee, destinationRecherchee) != 2) {
        printf("Format de saisie incorrect.\n");
        return;
    }

    int trouve = 0;
    printf("\n\033[1;36m"); // Titre en cyan
    printf(" --------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("| Numero | Compagnie       | Destination | Comptoir | debutEnr | finEnr | SalleEmb | debutEmb | finEmb | Decollage | EtatVol           |\n");
    printf(" --------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("\033[0m"); // Retablir la couleur par defaut
    for (int i = 0; i < taille; i++) {
        if ((strcmp(vols[i].compagnie, compagnieRecherchee) == 0) && (strcmp(vols[i].destination, destinationRecherchee) == 0)) {
            printf(" --------------------------------------------------------------------------------------------------------------------------------------\n");
            printf("| %-6s | %-15s | %-11s | %-8s | %-8s | %-6s | %-8s | %-8s | %-6s | %-9d | %-17s |\n",
                   vols[i].numero_vol, vols[i].compagnie, vols[i].destination,
                   vols[i].numero_comptoir, vols[i].heure_debut_enregistrement,
                   vols[i].heure_fin_enregistrement, vols[i].salle_embarquement,
                   vols[i].heure_debut_embarquement, vols[i].heure_fin_embarquement,
                   vols[i].heure_decollage, vols[i].etat);
            printf(" --------------------------------------------------------------------------------------------------------------------------------------\n");

            trouve = 1;
        }
    }

    if (!trouve) {
        printf("Aucun vol trouve pour la compagnie '%s'.\n", destinationRecherchee);

    }
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
            printf(" --------------------------------------------------------------------------------------------------------------------------------------\n");
            printf("| %-6s | %-15s | %-11s | %-8s | %-8s | %-6s | %-8s | %-8s | %-6s | %-9d | %-17s |\n",
           vol.numero_vol, vol.compagnie, vol.destination, vol.numero_comptoir,
           vol.heure_debut_enregistrement, vol.heure_fin_enregistrement,
           vol.salle_embarquement, vol.heure_debut_embarquement,
           vol.heure_fin_embarquement, vol.heure_decollage, vol.etat);
            printf(" --------------------------------------------------------------------------------------------------------------------------------------\n");


}


void affichage(int taille, struct Vol vol[], int heure){
    printf("\n\033[1;36m"); // Titre en cyan
    printf(" --------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("| Numero | Compagnie       | Destination | Comptoir | debutEnr | finEnr | SalleEmb | debutEmb | finEmb | Decollage | EtatVol           |\n");
    printf(" --------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("\033[0m"); // R�tablir la couleur par d�faut

    for (int j = 1; j < taille; j++) {
        if (vol[j].heure_decollage >= heure && vol[j].heure_decollage <= (heure + 300)){
            affiche_ligne(vol[j]);
        }
    }
}
void affichage_vol(struct Vol tab[], int taille) {
    char option[TAILLE];
    char choix[100];
    int ok = 0;
    long val;
    int heureFormattee;

    do {
        printf("\n1. Afficher les vols avec l'heure actuelle \n"
               "2. Saisir l'heure manuellement\n\n");
        printf("Veuillez selectionner une option avec le numero correspondant: ");
        fgets(option, sizeof(option), stdin);
        option[strcspn(option, "\n")] = 0;
        int option_val = atoi(option);

        switch (option_val) {
            case 1:
                heureFormattee = HeureFormattee();
                tri_selection_croissante(tab, taille);
                heureFormattee = heureFormattee - 10;
                if (heureFormattee % 100 >=  60){
                    heureFormattee -= 40;
                }
                if (heureFormattee < 600)
                    heureFormattee = 600;
                affichage(taille, tab, heureFormattee);
                ok = 1;

                break;
            case 2:
                printf("\nEntrer l'horaire de vol (HHMM) : ");
                fgets(choix, sizeof(choix), stdin);
                choix[strcspn(choix, "\n")] = 0;
                int option_m = atoi(choix);
                tri_selection_croissante(tab, taille);
                option_m = option_m - 10;
                if (option_m % 100 >=  60){
                    option_m -= 40;
                }
                if (option_m < 600)
                    option_m = 600;
                affichage(taille, tab, option_m);
                ok = 1;
                break;

            case 3:
                affichage_general();
                break;
            default:
                printf("Erreur : Option invalide. Veuillez selectionner une option valide.\n");
        }
    } while (!ok);
}

int HeureFormattee() {
    struct tm heureActuelle;
    time_t tempActuel;
    time(&tempActuel);
    heureActuelle = *localtime(&tempActuel);

    int heure = heureActuelle.tm_hour;
    int minute = heureActuelle.tm_min;

    int heureFormattee = heure * 100 + minute;

    return heureFormattee;
}


void reprogrammation_vol(struct Vol tab1[], int taille) {

    char numero_vol[TAILLE];
    printf("Entrer le numero de votre vol : ");

    fgets(numero_vol, TAILLE, stdin);
    numero_vol[strcspn(numero_vol, "\n")] = 0;

    int numero__vol = atoi(numero_vol);
    int indice_vol_base = atoi(numero_vol);
   // printf("feur");
   // printf("%s",tab1[indice_vol_base].numero_vol);

   // printf("%d",tab1[indice_vol_base].heure_decollage);
    char etat[1000] ;
    strcpy(etat, tab1[indice_vol_base].etat);
   // printf("%s\n",etat);

    int retard = 0;
    if (strcmp(etat, "A l'heure")== 0){
        printf("Le vol choisi est a l'heure, il ne necessite pas de reprogrammation\n");
        return;
    } else if (strcmp(etat, "Annule")== 0){
        printf("Le vol est annule, il n'est pas possible de le reprogrammer\n");
        return;
    } else {
        for (int i = 0; i < strlen(etat); i++) {
            if (etat[i] != '\0' && etat[i] >= '0' && etat[i] <= '9'){
                retard = retard * 10 + (etat[i] - '0');
            }
        }
    }

    int heure = tab1[indice_vol_base].heure_decollage;
    tri_selection_croissante(tab1, taille);
   // printf("****");
   // printf("%s\n",tab1[indice_vol_base].numero_vol);
   // affichage(taille,tab1,heure);
    int indice_vol;
    int T = 1;
    for (int i=0;(i<taille && T);i++){

        if (tab1[i].heure_decollage == heure ){
            T= 0;
            indice_vol = i;
            indice_vol_base  = i;
        }
    }
    affichage(taille,tab1,heure);

    int heure_min  = (heure% 100) + (heure / 100)*60 + retard;
    int heure_de_depart_minimum = heure_min;
    int cpt = retard;
    T = 1;
   // printf("Debut%d\n",tab1[indice_vol_base].heure_decollage);
    while ( indice_vol < taille - 1 && (tab1[indice_vol].heure_decollage% 100) + (tab1[indice_vol].heure_decollage/ 100)*60 < heure_min){
        indice_vol++;
    }
    int vol_suivant;

    printf("\033[1;32m"); // Texte en vert
    printf("\n|----------------------------------------------- Reprogramation du vol selectionne [%d] ------------------------------------------------|\n",numero__vol);
    printf("\033[0m"); // R�tablir la couleur par d�faut
   // printf("Depart%d\n",(heure_min ) % 60 + ((heure_min) / 60) * 100);
   // printf("%d\n",tab1[indice_vol].heure_decollage);

    for (; T && indice_vol < taille && cpt < 60; indice_vol++) {
        vol_suivant = tab1[indice_vol].heure_decollage;
        vol_suivant = (vol_suivant% 100) + (vol_suivant/ 100)*60;
     //   printf("%d.....%d\n",(vol_suivant) % 60 + ((vol_suivant) / 60) * 100,indice_vol);
        if (vol_suivant - heure_min >= 5){

     //       printf("%d\n",(heure_min ) % 60 + ((heure_min) / 60) * 100);
     //       printf("%d\n",(vol_suivant) % 60 + ((vol_suivant) / 60) * 100);
     //       printf("heure_min: %d\n", heure_min);
            tab1[indice_vol_base].heure_decollage = (heure_min ) % 60 + ((heure_min) / 60) * 100;
   //         printf("fin%d\n",tab1[indice_vol_base].heure_decollage);

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
    affichage(taille,tab1,heure);
}

int calculerage(const char *date_naissance) {
    int jour, mois, annee;

    sscanf(date_naissance, "%d/%d/%d", &jour, &mois, &annee); //sscanf permet de sparer les char

    time_t t = time(NULL); // permet d'avoir la date actuel
    struct tm tm = *localtime(&t);

    int age = tm.tm_year + 1900 - annee;

    if (tm.tm_mon + 1 < mois || (tm.tm_mon + 1 == mois && tm.tm_mday < jour)) { // gestion des cas
        age--;
    }

    return age;
}

void affichage2(struct passager tab[], int taille) {
    for (int i = 0; i < taille; i++) {
        printf("\n");
        printf("\033[0;32m"); // couleur verte
        printf("\nPassager %d \n", i + 1);
        printf("\033[0m");
        printf("Nom : %s\n", tab[i].nom);
        printf("Prenom : %s\n", tab[i].prenom);
        printf("Date de naissance : %s\n", tab[i].date_naissance);
        printf("Age : %d\n", calculerage(tab[i].date_naissance));
        printf("Numero de sige : %s\n", tab[i].numero_siege);
        printf("Prix du billet : %d\n", tab[i].prix_billet);
    }
}

void echanger2(struct passager tab[], int i, int j) {
    struct passager temp = tab[i];
    tab[i] = tab[j];
    tab[j] = temp;
}

void tri_selection2(struct passager tab[], int taille){
    int i, j, indice_mini, age_mini,age_j;
    for (i = 0; i< taille -1 ;i++){
        indice_mini = i;
        for (j=i+1; j < taille; j++){
            age_mini = calculerage(tab[indice_mini].date_naissance);
            age_j = calculerage(tab[j].date_naissance);

            if ((age_j < 12 && age_mini < 12) || (age_j >= 12&& age_mini >= 12)){
                if (tab[j].prix_billet > tab[indice_mini].prix_billet){
                    indice_mini= j;
                   // printf("--------Prix billet\n");

                } else if(tab[j].prix_billet == tab[indice_mini].prix_billet && strcmp(tab[j].nom, tab[indice_mini].nom) < 0){
                    indice_mini = j;
                    //printf("---------Prix egal");
                }
            } else{
                if (age_j < 12 ){
                    indice_mini= j;
                    //printf("--------------Age de j < 12");
                }


            }
        }
      // permet d'afficher avant le tri  printf("%d/%d\n",indice_mini,i);
    echanger2(tab,indice_mini,i);
    }


}


void afficherPassagersSalleEmbarquement(){
    FILE* fp = fopen(fichierCSV, "r");

    char numero_vol[TAILLE];
    printf("Entrer le numero de votre vol : ");

    fgets(numero_vol, TAILLE, stdin);
    numero_vol[strcspn(numero_vol, "\n")] = 0;
   int numero__vol = atoi(numero_vol);

    int indice = 0;
    struct passager tab[50];

    if (fp != NULL){
       // printf("feur");

        char chaine[1024];
        while (fgets(chaine, 1024 ,fp)!= NULL){

          //  printf("F");
            char *token = strtok(chaine,",");
            printf("%s",token);
            int tok = atoi(token);
            if (tok == numero__vol){
                for(int i=0;i<11;i++){
                    token= strtok(NULL,",");
                }
                printf("%s",token);
                int j=0;
                while (token != NULL){
                   // printf("gyat");
                    switch (j){
                        case 0 : strcpy(tab[indice].nom, token); j++; token = strtok(NULL, ",");  break;
                        case 1 : strcpy(tab[indice].prenom, token);j++;token = strtok(NULL, ",");   break;
                        case 2 : strcpy(tab[indice].date_naissance, token); j++; token = strtok(NULL, ",");  break;
                        case 3 : strcpy(tab[indice].numero_siege, token);j++;token = strtok(NULL, ";"); break;
                        case 4 : tab[indice].prix_billet = atoi(token);j=0;token = strtok(NULL, ",");indice++;break;
                        default : printf("Probleme"); break;

                    }
                }
            }
        }
    }



   // printf("fin\n");
    // printf("%d",tab[indice-1].prix_billet);
    char *chaine = tab[0].nom +1;
    strcpy(tab[0].nom, chaine);
   // printf("%s",tab[0].nom);
   // printf("%d",indice -1);
    // affichage2(tab,indice);


   // printf("-------------------------------------");
    /*
    char *chainee = tab[indice-1].prix_billet - 1;
    strcpy(tab[indice-1].prix_billet, chainee);
    printf("%s\n",chainee);
    printf("%s",tab[indice-1].prix_billet);
    */

    tri_selection2(tab, indice);
    affichage2(tab,indice);
    return;



}



void embarquement(struct Vol tab1[], int taille){
    //heure_actuelle :
    int heure = HeureFormattee();
    int heureD, heureF;
    int heure_deb;
    int heure_fin;

    heureD = heure -10;
    if ((heureD%100)>= 60){
        heureD = heureD -40;
    }
    if (heureD < 600){
        heureD = 600;
    }

    heureF = heure + 30;
    if ((heureF%100)>= 60){
        heureF += 40;
    }
    if ((heureF)>= 2200){
            heureF = 2200;

    }
    for (int i=0;i<taille;i++){
        heure_deb =  atoi(tab1[i].heure_debut_embarquement);
        if ((heureD <= heure_deb) && (heureF >= heure_deb)){
            printf("SAlle embarquement : %s\n",tab1[i].salle_embarquement);
            printf("numero de vol : %s\n",tab1[i].numero_vol);
            int numero_vol =atoi(tab1[i].numero_vol);
            afficherPassagersNUMVOL(numero_vol);
        }
    }
    printf("feur");


}


void enregistrement(struct Vol tab1[], int taille){
    //heure_actuelle :
    int heure = HeureFormattee();
    int heureD, heureF;
    int heure_deb;
    int heure_fin;

    heureD = heure -30;
    printf("%d\n",heureD%100);
    if ((heureD%100)>= 60){
        heureD -= 40;
    }
    if (heureD < 600){
        heureD = 600;
    }

    heureF = heure + 10;
    if ((heureF%100)>= 60){
        heureF += 40;
    }
    if ((heureF)>= 2200){
            heureF = 2200;

    }
    printf("%d/%d",heureD,heureF);
    for (int i=0;i<taille;i++){
        heure_deb =  atoi(tab1[i].heure_debut_enregistrement);
        if ((heureD <= heure_deb) && (heureF >= heure_deb)){
            printf("Numero comptoir : %s\n",tab1[i].numero_comptoir);
            printf("numero de vol : %s\n",tab1[i].numero_vol);
            int numero_vol =atoi(tab1[i].numero_vol);
            afficherPassagersNUMVOL(numero_vol);
        }
    }
    printf("feur");


}




void afficherPassagersNUMVOL( int numero_vol){
    struct passager *vol_array = (struct passager *)malloc(100 * sizeof(struct passager));


    if (vol_array == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return ;
    }





    FILE* fp = fopen(fichierCSV, "r");

    int indice = 0;
    struct passager tab[100];

    if (fp != NULL){
       // printf("feur");

        char chaine[1024];
        while (fgets(chaine, 1024 ,fp)!= NULL){

          //  printf("F");
            char *token = strtok(chaine,",");
            printf("%s",token);
            int tok = atoi(token);
            if (tok == numero_vol){
                for(int i=0;i<11;i++){
                    token= strtok(NULL,",");
                }
                printf("%s",token);
                int j=0;
                while (token != NULL){
                   // printf("gyat");
                    switch (j){
                        case 0 : strcpy(tab[indice].nom, token); j++; token = strtok(NULL, ",");  break;
                        case 1 : strcpy(tab[indice].prenom, token);j++;token = strtok(NULL, ",");   break;
                        case 2 : strcpy(tab[indice].date_naissance, token); j++; token = strtok(NULL, ",");  break;
                        case 3 : strcpy(tab[indice].numero_siege, token);j++;token = strtok(NULL, ";"); break;
                        case 4 : tab[indice].prix_billet = atoi(token);j=0;token = strtok(NULL, ",");indice++;break;
                        default : printf("Probleme"); break;

                    }
                }
            }
        }
    }



   // printf("fin\n");
    // printf("%d",tab[indice-1].prix_billet);
    char *chaine = tab[0].nom +1;
    strcpy(tab[0].nom, chaine);
   // printf("%s",tab[0].nom);
   // printf("%d",indice -1);
    // affichage2(tab,indice);


   // printf("-------------------------------------");
    /*
    char *chainee = tab[indice-1].prix_billet - 1;
    strcpy(tab[indice-1].prix_billet, chainee);
    printf("%s\n",chainee);
    printf("%s",tab[indice-1].prix_billet);
    */

    tri_selection2(tab, indice);
    affichage2(tab,indice);




}












