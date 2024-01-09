from random import randint
from numpy import zeros, array

def generate_date_naissance():
    jour = randint(1, 31)
    mois = randint(1, 12)
    annee = randint(1900, 2022)

    date_naissance = array([jour, mois, annee])
    return date_naissance

def tabindice(tab):
    for i in range(len(tab)):
        tab[i] = i
    return tab

def indice_par_dichotomie(tab, tab_indice, val):
    ind = -1
    d = 0
    f = len(tab) - 1
    while d <= f and ind == -1:
        m = (d + f) // 2
        if tab[tab_indice[m]][2] == val[2]:
            if tab[tab_indice[m]][1] == val[1]:
                if tab[tab_indice[m]][0] == val[0]:
                    ind = m
                elif tab[tab_indice[m]][0] < val[0]:
                    d = m + 1
                else:
                    f = m - 1
            elif tab[tab_indice[m]][1] < val[1]:
                d = m + 1
            else:
                f = m - 1
        elif tab[tab_indice[m]][2] < val[2]:
            d = m + 1
        else:
            f = m - 1
    return ind

def fusionner(tab, i_debut, i_mil, i_fin, tab_indice):
    temp = zeros(i_fin - i_debut + 1, int)
    i = i_debut
    j = i_mil + 1
    k = 0

    while i <= i_mil and j <= i_fin:
        if tab[tab_indice[i]][2] < tab[tab_indice[j]][2]:
            temp[k] = tab_indice[i]
            i = i + 1
        elif tab[tab_indice[i]][2] == tab[tab_indice[j]][2]:
            if tab[tab_indice[i]][1] < tab[tab_indice[j]][1]:
                temp[k] = tab_indice[i]
                i = i + 1
            elif tab[tab_indice[i]][1] == tab[tab_indice[j]][1]:
                if tab[tab_indice[i]][0] < tab[tab_indice[j]][0]:
                    temp[k] = tab_indice[i]
                    i = i + 1
                else:
                    temp[k] = tab_indice[j]
                    j = j + 1
            else:
                temp[k] = tab_indice[j]
                j = j + 1
        else:
            temp[k] = tab_indice[j]
            j = j + 1
        k = k + 1

    while i <= i_mil:
        temp[k] = tab_indice[i]
        i = i + 1
        k = k + 1

    while j <= i_fin:
        temp[k] = tab_indice[j]
        j = j + 1
        k = k + 1

    k = 0
    while k < len(temp):
        tab_indice[i_debut + k] = temp[k]
        k = k + 1

def tri_fusion(tab, i_debut, i_fin, tab_indice):
    i_mil = (i_debut + i_fin) // 2
    if i_debut < i_fin:
        tri_fusion(tab, i_debut, i_mil, tab_indice)
        tri_fusion(tab, i_mil + 1, i_fin, tab_indice)
        fusionner(tab, i_debut, i_mil, i_fin, tab_indice)

def affichage_dates(tab, tab_indice):
    print("Dates triées :")
    for i in range(len(tab)):
        print("-", i + 1, " ", tab[tab_indice[i]])

# Génére des dates de naissance aléatoires
liste_passagers = array([generate_date_naissance() for _ in range(10)])

print("Dates non triées :")
for date in liste_passagers:
    print("-", date)

# Tri des dates
tab_indice = zeros(len(liste_passagers), int)
tabindice(tab_indice)
tri_fusion(liste_passagers, 0, len(liste_passagers) - 1, tab_indice)



affichage_dates(liste_passagers, tab_indice)








#-----------------------------------------------------------------------------

print("espace")


def recherche_linéaire_1(tab, indice_tab,val):
    tab1= zeros( len(tab[indice_tab]), int)
    y=0
    i=0
    while i < len(tab[indice_tab]):
        if tab[indice_tab][i] == val :
            tab1[y]=i+1
            y+= 1
        i+=1
    return tab1



def recherche_linéaire_2(tab, indice_tab1,val1,indice_tab2,val2):
    tab1= zeros( len(tab[indice_tab1]), int)
    y=0
    i=0
    while i < len(tab[indice_tab1]):
        if tab[indice_tab1][i] == val1 :
            if tab[indice_tab2][i] == val2 :
                
                tab1[y]=i+1
                y+= 1
        i+=1
    return tab1







def affichage(tab,tab1):
    i=0
  
    while tab1[i] != 0 and i < len(tab1):
        y=0
        while y < len(tab):
            print(tab[y][tab1[i]-1])
            y= y +1
        print("-------------")
        i= i +1
    

    
    
    
    



def recherche_vol(tab,indice1,valeur1,indice2,valeur2):
    #tab1 = recherche_linéaire_1(tab, indice1, valeur1)
    tab1 = recherche_linéaire_2(tab, indice1, valeur1, indice2, valeur2)
    print(tab1)
    affichage(tab, tab1)
    

    



    

   
tab1 = array([
    [2, 5678, 78, 1, 2, 2],
    [678, 45, 4, 1, 2, 4],
    [4, 6, 8, 1, 2, 4],
    [0, 0, 0, 1, 2, 4],
    [678, 5678, 78, 1, 2, 4],
    [678, 45, 4, 1, 2, 4],
    [2, 6, 8, 1, 2, 4],
    [678, 5678, 78, 1, 2, 4],
    [678, 45, 4, 1, 2, 4],
    [700, 1200, 1700, 1100, 1000, 1500]
])

recherche_vol(tab1,0,2,2,4)







import numpy as np

def liste_passager(tab):
    tab_indice = zeros(len(tab), int)
    tabindice(tab_indice)
    tri_fusion(tab, 0, len(tab) - 1, tab_indice)
    affichage(tab, tab_indice)

# Générer plusieurs tableaux similaires
for _ in range(5):
    liste_passagers = np.array([np.random.randint(1, 600, size=6) for _ in range(10)])
    print("Liste passagers:")
    print(liste_passagers)
    print("\n------------------------\n")



#-----------------------------------------------------------------------------

print("espace")


from random import randint
from numpy import zeros, array

def generate_tab():
    return array([randint(1, 700) for _ in range(11)])

def tabindice(tab):
    for i in range(len(tab)):
        tab[i] = i
    return tab

def fusionner(tab, i_debut, i_mil, i_fin, tab_indice):
    temp = zeros(i_fin - i_debut + 1, int)
    i = i_debut
    j = i_mil + 1
    k = 0

    while i <= i_mil and j <= i_fin:
        if tab[tab_indice[i]] < tab[tab_indice[j]]:
            temp[k] = tab_indice[i]
            i = i + 1
        else:
            temp[k] = tab_indice[j]
            j = j + 1
        k = k + 1

    while i <= i_mil:
        temp[k] = tab_indice[i]
        i = i + 1
        k = k + 1

    while j <= i_fin:
        temp[k] = tab_indice[j]
        j = j + 1
        k = k + 1

    k = 0
    while k < len(temp):
        tab_indice[i_debut + k] = temp[k]
        k = k + 1

def tri_fusion(tab, i_debut, i_fin, tab_indice):
    i_mil = (i_debut + i_fin) // 2
    if i_debut < i_fin:
        tri_fusion(tab, i_debut, i_mil, tab_indice)
        tri_fusion(tab, i_mil + 1, i_fin, tab_indice)
        fusionner(tab, i_debut, i_mil, i_fin, tab_indice)

def indice_par_dichotomie(tab, tab_indice, val):
    ind = -1
    d = 0
    f = len(tab) - 1
    while d <= f and ind == -1:
        m = (d + f) // 2
        if tab[tab_indice[m]] >= val and tab[tab_indice[m]] <= val + 300:
            ind = m
        else:
            if tab[tab_indice[m]] < val:
                d = m + 1
            else:
                f = m - 1
    return ind

def affichage(tab1, tab, tab_indice):
    heure = 23
    indice = indice_par_dichotomie(tab, tab_indice, heure)

    T = False
    while indice > 1 and not T:
        if tab[tab_indice[indice - 1]] < heure:
            T = True
        else:
            indice = indice - 1
    while indice < len(tab_indice) and tab[tab_indice[indice]] <= heure + 3000:
        i = 0
        result = []
        while i < len(tab1):
            result.append(tab1[i][tab_indice[indice]])
            i = i + 1

        print(result)
        print("----------------")
        indice = indice + 1


def affichage_vol(tab1):
    tab = tab1[0]
    tab_indice = zeros(len(tab), int)
    tab_indice = tabindice(tab_indice)
    tri_fusion(tab, 0, len(tab) - 1, tab_indice)
    affichage(tab1, tab, tab_indice)

# Exemple d'utilisation
tab1 = [generate_tab() for _ in range(6)]
affichage_vol(tab1)



#-----------------------------------------------------------------------------

print("espace")


def indice_par_dichotomie(tab,tab_indice ,val):
    ind =-1
    d=0
    f=len(tab)-1
    while d <= f and ind == -1:
        m=(d+f)//2
        if tab[tab_indice[m]]== val :
            ind=m
        else :
            if tab[tab_indice[m]] < val :
                d=m+1
            else:
                f=m-1
    return ind



def fusionner(tab, i_debut, i_mil, i_fin, tab_indice):
    temp = zeros(i_fin - i_debut + 1, int)
    i = i_debut
    j = i_mil + 1
    k = 0

    while i <= i_mil and j <= i_fin:
        if tab[tab_indice[i]] < tab[tab_indice[j]]:
            temp[k] = tab_indice[i]
            i = i + 1
        else:
            temp[k] = tab_indice[j]
            j = j + 1
        k = k + 1

    while i <= i_mil:
        temp[k] = tab_indice[i]
        i = i + 1
        k = k + 1

    while j <= i_fin:
        temp[k] = tab_indice[j]
        j = j + 1
        k = k + 1

    k = 0
    while k < len(temp):
        tab_indice[i_debut + k] = temp[k]
        k = k + 1

def tri_fusion(tab, i_debut, i_fin, tab_indice):
    i_mil = (i_debut + i_fin) // 2
    if i_debut < i_fin:
        tri_fusion(tab, i_debut, i_mil, tab_indice)
        tri_fusion(tab, i_mil + 1, i_fin, tab_indice)
        fusionner(tab, i_debut, i_mil, i_fin, tab_indice)





tab = array([
    [0, 8, 1, -1, 7, 0, 0, 0, 0, 0],
    [1600, 1890, 1602, 1606, 1612, 1623, 1636, 1643, 1657, 1703]
])


def reprogrammation_vol(tab1, indice_vol_base):

    tab=tab1[1]
    
    tab_indice=zeros( len(tab), int)

    tabindice(tab_indice)
    tri_fusion(tab,0,len(tab)-1,tab_indice)
    heure= tab[indice_vol_base]
    print(tab_indice)
    indice_vol= indice_par_dichotomie(tab, tab_indice, heure)
    
    heure_min  = (heure% 100) + (heure // 100)*60 + tab1[0][indice_vol_base]
    heure_de_depart_minimum = heure_min
    print(heure)
    print(heure_min)
    cpt = tab1[0][2]
    T = False
    while not T and indice_vol < len(tab_indice)- 1 and cpt < 60:
        vol_suivant = (tab[tab_indice[indice_vol + 1]] // 100 )*60 + (tab[tab_indice[indice_vol + 1]] %100)
        if vol_suivant - heure_min >= 5:
            
            print(heure_min)
            tab1[1][indice_vol_base] = (heure_min )%60 + ((heure_min )// 60)* 100
            tab1[0][indice_vol_base] = 0
            T= True
        else:
            heure_min = vol_suivant + 5
            cpt  = heure_min - heure_de_depart_minimum
            indice_vol = indice_vol + 1
    if cpt >= 60 :
        tab1[0][indice_vol_base] = -1
    if indice_vol < len(tab_indice)- 1 and (22*60 - heure_min) > 1 and not T:
        tab1[1][indice_vol_base] = (heure_min )%60 + ((heure_min )// 60)* 100
        tab1[0][indice_vol_base] = 0


    

    #trie les vols par heure de decollage
    #regarder au cas par cas si heure de decollage[i + 1] - heure_de_decollage[i] > 5;

    #si retard > 60 ou heure de decollage + retard > 2200 
    #alors le vol est annulé: la valeur du retard = -1
    
reprogrammation_vol(tab, 2)



