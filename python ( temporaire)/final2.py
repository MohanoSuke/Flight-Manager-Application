from numpy import *
from random import randint

def tabindice(tab,cpt):
    """
    entree/sortie tab : [int]
    pré-cond : len(tab) >= 1
    post-cond : rempli le tableau pourtoutes les cases du tableau soient égales à tab[indice]=indice
    """
    i=0
    cpt+= 1
    while i < len(tab):
        tab[i]=i
        i=i+1
        cpt += 5
    cpt += 5
    return cpt


def indice_par_dichotomie(tab,tab_indice ,val,cpt):
    """
    entrée tab : [int]
    entrée tab_indice :[int]
    entrée val : int
    pré-cond : ∀ i ∈ [1, len(tab) [, tab[i-1] < tab[i]
    sortie m = int
    post-cond : Lorsque val est dans tab, on a tab[m] = val, dans le cas contraire, ind vaut -1
    """
    m=-1
    d=0
    f=len(tab)-1
    cpt += 4
    while d <= f :
        m=(d+f)//2
        cpt += 4
        if tab[tab_indice[m]]== val :
            cpt += 3
            return m, cpt
        else :
            cpt += 3
            if tab[tab_indice[m]] < val :
                d=m+1
                cpt += 2
            else:
                f=m-1
                cpt += 2
            cpt+= 3
    cpt+= 4
    return m, cpt


def age( age,cpt):      #on definit la date actuelle comme le 12/01/2024
    jour= (age //1000000)%100
    mois = (age //10000)%100
    annee = age %10000
    cpt += 8

    cpt += 1
    if mois > 1:
        age = 2024 - annee 
        cpt += 2
    else : 
        cpt += 1
        if mois == 1:
            cpt += 1
            if jour >= 12:
                age = 2024 - annee 
                cpt += 2
            else :
                age = 2023 - annee
                cpt += 2
        else :
            age = 2023 - annee
            cpt += 2

    return age, cpt


def fusionner_bis(tab, i_debut, i_mil, i_fin, tab_indice,cpt):
    """
    entrée/sortie tab_indice : [int]
    pré-cond : len(tab)= len(tab_indice) ; len(tab)>= 1 ; 0<= i_debut<= i_mil <= i_fin <= len(tab)-1
               tab[tab_indice[i_deb:i_mil]] et tab[tab_indice[i_mil+1: i_fin]] sont triés
    post-cond : tab[tab_indice[i_deb:i_fin]] est trié
    """
    temp = zeros(i_fin - i_debut + 1, int)
    cpt += i_fin - i_debut +1
    i = i_debut
    j = i_mil + 1
    k = 0

    cpt += 4

    while i <= i_mil and j <= i_fin:
        cpt += 3
        
        age_i,cpt =age(tab[tab_indice[i]][0],cpt)
        age_j, cpt = age(tab[tab_indice[j]][0],cpt)
        cpt += 6


        cpt += 7  #pour le if
        if (age_i < 12 and age_j < 12) or (age_i > 12 and age_j > 12):
            cpt += 5
            if tab[tab_indice[i]][1] >  tab[tab_indice[j]][1] :
                temp[k] = tab_indice[i]
                i = i + 1
                cpt += 5
            else :
                cpt += 5
                if tab[tab_indice[i]][1] <  tab[tab_indice[j]][1] :
                    temp[k] = tab_indice[j]
                    j = j + 1
                    cpt += 5
                else :
                    cpt += 5
                    if tab[tab_indice[i]][2] >  tab[tab_indice[j]][2] :
                        temp[k] = tab_indice[j]
                        j = j + 1
                        cpt += 5
                    else :
                        temp[k] = tab_indice[i]
                        i = i + 1
                        cpt += 5
        else:
            cpt += 3
            if tab[tab_indice[i]][0] < 12 :
                temp[k] = tab_indice[i]
                i = i + 1
                cpt += 5
            else :
                temp[k] = tab_indice[j]
                j = j + 1
                cpt += 5
        k = k + 1
        cpt += 2
    cpt += 3
    while i <= i_mil:
        cpt += 1
        temp[k] = tab_indice[i]
        i = i + 1
        k = k + 1
        cpt += 7
    cpt += 1

    while j <= i_fin:
        cpt += 1
        temp[k] = tab_indice[j]
        j = j + 1
        k = k + 1
        cpt += 7
    cpt += 1

    k = 0
    cpt += 1
    while k < len(temp):
        cpt += 1
        tab_indice[i_debut + k] = temp[k]
        k = k + 1
        cpt += 6
    cpt += 1
    return cpt

def tri_fusion(tab, i_debut, i_fin, tab_indice,cpt):
    """
    entrée /sortie tab : [int]
    pré-cond : len(tab)= len(tab_indice) ; len(tab) >=1
    post-cond : les éléments de tab sont triés avec leur indice depuis tab_indice 
                qui contient l'ordre dans lequel les éléments de tab sont triés dans l'ordre de passage des passgers
    """
    i_mil = (i_debut + i_fin) // 2
    cpt += 3
    cpt+= 1
    if i_debut < i_fin:
        cpt  = tri_fusion(tab, i_debut, i_mil, tab_indice,cpt)
        cpt  = tri_fusion(tab, i_mil + 1, i_fin, tab_indice,cpt)
        cpt  = fusionner_bis(tab, i_debut, i_mil, i_fin, tab_indice,cpt)
    return cpt











#!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
def affichage(tab , tab_indice,cpt):
    """ 
    entrée tab : [int]
    entrée tab_indice : [int]
    pre-condition : len(tab_indice) = len(tab)
    post-condition : le tableau tab aura été affiché selon l'ordre de tab_indice
    """
    print("ordre")
    i=0
    cpt += 1
    while i < len(tab):
        cpt += 1
        print("-",i + 1," ",tab[tab_indice[i]])
        i=i+1
        cpt += 4
    cpt +=1
    return cpt






def liste_passager(tab):
    """
    entrée tab : [int]
    pre_condition : len(tab) >= 1
    post-condition : la liste des passagers aura été affiché selon un certain tri
    """
    cpt = 0
    tab_indice=zeros( len(tab), int)
    cpt += len(tab)
    cpt  = tabindice(tab_indice,cpt)
    cpt = tri_fusion(tab,0,len(tab)-1,tab_indice,cpt)
    cpt = affichage(tab, tab_indice,cpt)
    print(cpt)
    return cpt








liste_passagers = array([[71,88,68],[6,59,678],[45,56,679],[23,78,678],[3,55,678],[56,55,678],[78,56,68],[66,57,678],[3,88,767]])




liste_passager(liste_passagers)


#-----------------------------------------------------------------------------

print("espace")


def recherche_linéaire_1(tab, indice_tab,val,cpt):
    """
    entrée tab : [int]
    entrée indice_tab : int
    entrée val : int
    pre-condition : 0 <= tab_indice < len(tab)
    sortie tab1 : [int]
    post-condition : tab1 contient les indices + 1 qui indiquent où se trouve val dans tab[indice_tab]. Le reste de tab1 est constitué de 0
    """
    tab1= zeros( len(tab[indice_tab]), int)
    cpt += len(tab[indice_tab])
    y=0
    i=0
    cpt += 2


    while i < len(tab[indice_tab]):
        cpt += 2
        if tab[indice_tab][i] == val :
            tab1[y]=i+1
            y=y+1
            cpt += 5
        i=i+1
        cpt += 4
    cpt += 2
    return tab1, cpt



def recherche_linéaire_2(tab, indice_tab1,val1,indice_tab2,val2,cpt):
    """
    entrée tab : [int]
    entrée indice_tab1 : int
    entrée val1 : int
    entrée indice_tab2 : int
    entrée val2 : int
    pre-condition : 0 <= indice_tab1  < len(tab) :  0 <= indice_tab2  < len(tab)
    sortie tab1 : [int]
    post-condition : tab1 contient le(s) indices()) + 1 qui indique(nt) où se trouve val1 dans tab[indice_tab1] et val2 dans tab[indice_tab2]. Le reste de tab1 est constitué de 0
    """
    tab1= zeros( len(tab[indice_tab1]), int)
    cpt += len(tab[indice_tab1])
    y=0
    i=0

    cpt += 2
    while i < len(tab[indice_tab1]):
        cpt += 2
        if tab[indice_tab1][i] == val1 :
            if tab[indice_tab2][i] == val2 :
                
                tab1[y]=i+1
                y= y +1
                cpt += 5
            cpt += 2
        cpt += 2
        i=i+1
        cpt += 2
    return tab1, cpt






#!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
def affichage_recherche(tab,tab1,cpt):
    """ 
    entrée tab : [int]
    entrée tab1 : [int]
    post-condition : les colonnes de tab sont affichés selon le tableau d'indice tab1
    """
    i=0
    cpt += 1
    while tab1[i] != 0 and i < len(tab1):
        cpt += 4
        y=0
        cpt +=1
        while y < len(tab):
            cpt += 1
            print(tab[y][tab1[i]-1])
            y= y +1
            cpt += 4
        cpt += 1
        print("-------------")
        i= i +1
        cpt += 1
    cpt += 4
    return cpt
    

    
    
    
    



def recherche_vol(tab,indice1,valeur1,indice2,valeur2):
    """
    entrée tab : [int]
    entrée indice1 : int
    entrée valeur1 : int
    entrée indice2 : int
    entrée valeur2 : int
    pre-condition : 0 <= indice1  < len(tab) :  0 <= indice2  < len(tab)
    post-condition : les resultats de la recherche seront affichés sinon rien ne sera affiché
    """
    cpt  = 0
    #tab1,cpt = recherche_linéaire_1(tab, indice1, valeur1)
    tab1,cpt = recherche_linéaire_2(tab, indice1, valeur1, indice2, valeur2,cpt)
    cpt =affichage_recherche(tab, tab1,cpt)
    print(cpt)
    return cpt
    

    



    

   
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




#-----------------------------------------------------------------------------

print("espace")





def fusionner(tab, i_debut, i_mil, i_fin, tab_indice,cpt):
    """
    entrée/sortie tab_indice : [int]
    pré-cond : len(tab)= len(tab_indice) ; len(tab)>= 1 ; 0<= i_debut<= i_mil <= i_fin <= len(tab)-1
               tab[tab_indice[i_deb:i_mil]] et tab[tab_indice[i_mil+1: i_fin]] sont triés
    post-cond : tab[tab_indice[i_deb:i_fin]] est trié
    """
    temp = zeros(i_fin - i_debut + 1, int)
    cpt += i_fin -i_debut +1
    i = i_debut
    j = i_mil + 1
    k = 0

    cpt += 4

    while i <= i_mil and j <= i_fin:
        cpt+= 3
        cpt += 5
        if tab[tab_indice[i]] < tab[tab_indice[j]]:
            temp[k] = tab_indice[i]
            i = i + 1
            cpt += 5
        else:
            temp[k] = tab_indice[j]
            j = j + 1
            cpt += 5
        k = k + 1
        cpt += 2
    cpt += 3
    while i <= i_mil:
        cpt += 1
        temp[k] = tab_indice[i]
        i = i + 1
        k = k + 1
        cpt += 7
    cpt += 1
    while j <= i_fin:
        cpt += 1
        temp[k] = tab_indice[j]
        j = j + 1
        k = k + 1
        cpt += 7
    cpt += 1

    k = 0
    cpt += 1


    while k < len(temp):
        cpt += 1
        tab_indice[i_debut + k] = temp[k]
        k = k + 1
        cpt += 6
    cpt += 1
    return cpt

def tri_fusion(tab, i_debut, i_fin, tab_indice,cpt):
    """
    entrée /sortie tab : [int]
    pré-cond : len(tab)= len(tab_indice) ; len(tab) >=1
    post-cond : les éléments de tab sont triés avec leur indice depuis tab_indice 
                qui contient l'ordre dans lequel les éléments de tab sont triés dans l'ordre croissant
    """
    i_mil = (i_debut + i_fin) // 2
    cpt += 4
    if i_debut < i_fin:
        cpt  = tri_fusion(tab, i_debut, i_mil, tab_indice,cpt)
        cpt  = tri_fusion(tab, i_mil + 1, i_fin, tab_indice,cpt)
        cpt =fusionner(tab, i_debut, i_mil, i_fin, tab_indice,cpt)
    return cpt


def indice_par_dichotomie_vol(tab,tab_indice ,heure,cpt):
    d=0
    f=len(tab)-1
    cpt += 3
    while d <= f :
        m=(d+f)//2
        cpt += 4
        if tab[tab_indice[m]]== heure :
            cpt += 3
            return m, cpt
        else :
            cpt += 3
            if tab[tab_indice[m]] < heure :
                d=m+1
                cpt += 2
            else:
                f=m-1
                cpt += 2
            cpt+= 3
    cpt+= 4
    return m, cpt




def affichagevol(tab1, tab, tab_indice,cpt):
    """
    entrée tab1 : [int]
    entrée tab : [int]
    entrée tab_indice : [int]
    pre-condition : len(tab1) >= 1 ; len(tab) = len(tab_indice)
    post-condition : affiche les vols de tab1 compris entre heure et heure + 3 heures dans l'ordre croissant 
                    en fonction des valeurs de tab_indice qui contient les indices de tab dans l'ordre croissant.
    """
    #!!!!!!!!!
    heure = 1200             #mettre l'heure en paramètre
    #!!!!!!!!!!!
    indice , cpt = indice_par_dichotomie_vol(tab,tab_indice,heure,cpt)
    T= False
    cpt += 1
    while indice < len(tab) and not T :
        cpt += 3

        cpt += 3
        if tab[tab_indice[indice ]] < heure :
            indice = indice +1
            cpt += 2
        else:
            T=True
            cpt += 1
    cpt += 3
    print("---------autre--vol")
    
    while indice < len(tab_indice) and tab[tab_indice[indice]] <= heure + 300 :
        cpt += 6
        i=0
        cpt += 1
        while  i < len(tab1):
            cpt += 1
            print(tab1[i][tab_indice[indice]])
            i=i+1
            cpt += 4
        cpt += 1

        indice = indice + 1
        cpt += 1
        print("---------autre--vol")
    cpt += 6
    print("---------fin--vol")
    return cpt
        

    



def affichage_vol(tab1):   
    """
    entrée : [int]
    pre-cond : len(tab) >= 1
    post-condition : affiche les vols de tab compris entre heure et heure + 3 heures dans l'ordre croissant
                     en focntion de leur heure de decollage qui est stocké dans tab1[0]
    """
    cpt = 0
    tab= tab1[0]

    tab_indice=zeros( len(tab), int)

    cpt = tabindice(tab_indice,cpt)
    
    cpt =tri_fusion(tab,0,len(tab)-1,tab_indice,cpt)
    
    cpt = affichagevol(tab1, tab,tab_indice,cpt)
    print(cpt)
    return cpt
    

    

    
    


    
    
    
    
    
tab1=[[678,1356,78,1200,2,4],
      [678,45,4,1,2,5],
      [2,6,8,1,2,4],
      [0,0,0,1,2,4],
      [678,5678,78,1,2,4],
      [678,45,4,1,2,4],
      [2,6,8,1,2,4],
      [678,5678,78,1,2,4],
      [678,45,4,1,2,4],
      [700,1200,1700,1100,1000,1500]]




affichage_vol(tab1)


#-----------------------------------------------------------------------------

print("espace")







tab = array([
    [0, 8, 1, -1, 7, 0, 0, 0, 0, 0],
    [1600, 1890, 1602, 1606, 1612, 1623, 1636, 1643, 1657, 1703]
])


def reprogrammation_vol(tab1, indice_vol_base):
    """
    entrée tab1 : [int]
    entrée indice_vol_base : int
    pre-condition : len(tab1) >= 1 ;len(tab1[0]) >= 1 ; 0 <= indice_vol_base < len(tab1[0])
    post-condition : le vol choisi est reporgammé si il possède du retard, son horaire de decollage et son état sont chnagés 
                     si le vol ne s'annule pas en cours de reprogrammation, sinon rien ne se passe; 
    """
    print(tab1)
    cpt = 0
    tab=tab1[1]
    cpt += 2
    tab_indice=zeros( len(tab), int)
    cpt += len(tab)

    cpt =tabindice(tab_indice,cpt)
    cpt =tri_fusion(tab,0,len(tab)-1,tab_indice,cpt)
    heure= tab[indice_vol_base]
    compteur = tab1[0][indice_vol_base]
    cpt += 4

    cpt += 3
    print(compteur)
    if compteur == -1 or compteur == 0:
        

        print(cpt)

    else :

        print("feru")
        indice_vol, cpt= indice_par_dichotomie(tab, tab_indice, heure,cpt)
        i=indice_vol
        heure_min  = (heure% 100) + (heure // 100)*60 + tab1[0][indice_vol_base]
        heure_de_depart_minimum = heure_min
        T = False
        cpt += 10


        
        indice_vol= indice_vol -1
        y=0
        cpt += 3

        
        vol_precedent = (tab[tab_indice[indice_vol]] // 100 )*60 + (tab[tab_indice[indice_vol ]] %100)
        cpt += 9

        
        while indice_vol > 0 and vol_precedent <= heure_min - 5:
            cpt += 5
            indice_vol= indice_vol -1
            vol_precedent = (tab[tab_indice[indice_vol ]] // 100 )*60 + (tab[tab_indice[indice_vol]] %100)
            y=y+1
            cpt += 13
        cpt += 5


        indice_vol = i+1
        x= heure_min -vol_precedent
        cpt += 4

        cpt += 3
        if x < 5 and x >= 0:
            heure_min = heure_min + 5 - x
            cpt += 3
        

        while not T and indice_vol < len(tab_indice)- 1 and compteur < 60:
            cpt += 6
            vol_suivant = (tab[tab_indice[indice_vol ]] // 100 )*60 + (tab[tab_indice[indice_vol ]] %100)
            cpt += 9
            cpt += 2
            if vol_suivant - heure_min >= 5:
                
                
                tab1[1][indice_vol_base] = (heure_min )%60 + ((heure_min )// 60)* 100
                tab1[0][indice_vol_base] = 0
                T= True
                cpt += 9
            else:
                heure_min = vol_suivant + 5
                compteur  = heure_min - heure_de_depart_minimum
                indice_vol = indice_vol + 1
                cpt += 6
        cpt += 6

        cpt += 1
        if compteur >= 60 :
            tab1[0][indice_vol_base] = -1
            cpt += 2
        cpt += 8
        if indice_vol < len(tab_indice)- 1 and (22*60 - heure_min) > 1 and not T:
            tab1[1][indice_vol_base] = (heure_min )%60 + ((heure_min )// 60)* 100
            tab1[0][indice_vol_base] = 0
            cpt +=8
        print(cpt)


    print(tab1)
    return cpt

    #trie les vols par heure de decollage
    #regarder au cas par cas si heure de decollage[i + 1] - heure_de_decollage[i] > 5;

    #si retard > 60 ou heure de decollage + retard > 2200 
    #alors le vol est annulé: la valeur du retard = -1
    
reprogrammation_vol(tab, 2)




def reprogrammation_vol_rapide(tab1, indice_vol_base):
    """
    entrée tab1 : [int]
    entrée indice_vol_base : int
    pre-condition : len(tab1) >= 1 ;len(tab1[0]) >= 1 ; 0 <= indice_vol_base < len(tab1[0])
    post-condition : le vol choisi est reporgammé si il possède du retard, son horaire de decollage et son état sont chnagés 
                     si le vol ne s'annule pas en cours de reprogrammation, sinon rien ne se passe; 
    """
    print(tab1)
    cpt = 0
    tab=tab1[1]
    cpt += 2
    tab_indice=zeros( len(tab), int)
    cpt += len(tab)

    cpt =tabindice(tab_indice,cpt)
    cpt =tri_fusion(tab,0,len(tab)-1,tab_indice,cpt)
    heure= tab[indice_vol_base]
    compteur = tab1[0][indice_vol_base]
    cpt += 4

    cpt += 3
    print(compteur)
    if compteur == -1 or compteur == 0:
        

        return cpt

    else :
        print("feru")
        indice_vol, cpt= indice_par_dichotomie(tab, tab_indice, heure,cpt)
        
        heure_min  = (heure% 100) + (heure // 100)*60 + compteur
        heure_de_depart_minimum = heure_min
        if indice_vol != len(tab[0]):
            indice_vol = indice_vol +1


        x= tab1[1][indice_vol] 
        heure_avant = x%100 + (x//100)*60
        while heure_avant < heure_min - 5 and indice_vol < len(tab_indice) -1:
            indice_vol = indice_vol +1
            x= tab1[1][indice_vol] 
            heure_avant = x%100 + (x//100)*60
        T = False   


        while heure_avant == heure_min and indice_vol < len(tab_indice) -1 and compteur <60:
            heure_min = heure_min +5
            indice_vol = indice_vol +1
            x= tab1[1][indice_vol] 
            heure_avant = x%100 + (x//100)*60
            compteur = compteur + 5

        tab
        


        while T and indice_vol < len(tab_indice) -1 and heure_min < 22*60:
            
            

            cpt += 6
            vol_suivant = (tab[tab_indice[indice_vol + 1]] // 100 )*60 + (tab[tab_indice[indice_vol + 1]] %100)
            cpt += 11
            cpt += 2
            if vol_suivant - heure_min >= 5:
                
                
                tab1[1][indice_vol_base] = (heure_min )%60 + ((heure_min )// 60)* 100
                tab1[0][indice_vol_base] = 0
                T= True
                cpt += 9
            else:
                heure_min = vol_suivant + 5
                compteur  = heure_min - heure_de_depart_minimum
                indice_vol = indice_vol + 1
                cpt += 6
        cpt += 6

        cpt += 1
        if compteur >= 60 :
            tab1[0][indice_vol_base] = -1
            cpt += 2
        cpt += 8
        if indice_vol == len(tab_indice)- 1 and (22*60 - heure_min) > 1 and not T:
            tab1[1][indice_vol_base] = (heure_min )%60 + ((heure_min )// 60)* 100
            tab1[0][indice_vol_base] = 0
            cpt +=8
        return cpt


    
    print(tab1)
    #trie les vols par heure de decollage
    #regarder au cas par cas si heure de decollage[i + 1] - heure_de_decollage[i] > 5;

    #si retard > 60 ou heure de decollage + retard > 2200 
    #alors le vol est annulé: la valeur du retard = -1
    


def generate_date_naissance():
    jour = randint(1, 31)
    mois = randint(1, 12)
    annee = randint(1900, 2022)

    date_naissance = jour * 1000000 + mois * 10000 + annee
    return date_naissance

def passager():
    x = [generate_date_naissance(), randint(1, 100), randint(1, 100)]
    return x

""""
#affichage_ordre_passagers
cpt = 0
for i in range(10):
    print("feyr")
    array_of_passagers = [passager() for _ in range(200)]
    cpt += liste_passager(array_of_passagers)
print("affiche_vol_10",cpt/10)
#print(array_of_passagers)

"""

""""
#----------------
cpt = 0
#RECHERCHE VOL
for i in range(10):  
    liste_vols_recherche = array([random.randint(1, 600, size=200) for y in range(10)])
    print("Liste vols:")
    print(liste_vols_recherche)
    print("\n------------------------\n")
    cpt += recherche_vol(liste_vols_recherche,random.randint(0, 10),random.randint(1, 600),random.randint(0, 10),random.randint(1, 600))
print(cpt/10)
"""

#------------------------
def generate_hour():
    hour = random.randint(6, 21)
    minute = random.randint(0, 59)
    return hour * 100 + minute

"""
#AFFICHAGE_VOL
cpt =0
for i in range(10):
    liste_vols_aff = array([[generate_hour() if i == 0 else random.randint(1, 600) for j in range(200)] for i in range(10)])   
    print(liste_vols_aff)
    cpt += affichage_vol(liste_vols_aff)
print(cpt/10)

"""
def generate_etat():
    x = random.randint(-1, 59)
    return x
    

#--------------------------

#REPROGRAMMATION_VOL
cpt =0
for i in range(10):
    liste_vols_aff =  array([[generate_etat() if i == 0 else generate_hour() for j in range(2000000)] for i in range(2)])  
    print("Liste vols etat:")
    print(liste_vols_aff)
    cpt += reprogrammation_vol(liste_vols_aff, 1)
    print("\n------------------------\n")
print(cpt/10)

