#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "vecteur_de_données.c"
#include "réseau_de_neurones.c"
#include "apprentissage.c"


int main()
{
    srand(time(NULL));
    int NbLigneVec = 150; //Nombre de ligne des vecteur de données source, le fichier Iris.data contient 150 ligne//
    int NbCompVec = 4; // Nombre de données flottants dans un vecteur, nous avons 4 caractéristique //

    // Nous avons 5 * la racine (150) = 60, du coup j'ai choisi un réseau bidimensionnel de 10 lignes et 6 colonnes //
    int NbLigneNrn = 6; // Nombre de lignes de Réseau de neurones //
    int NbColNrn = 10; // Nombre de colonnes de Réseau de neurones //

    double Coef = 0.9; // Coefficient d'apprentissage //

    vecteur * tab=malloc(NbLigneVec*sizeof(struct vecteur));/* louer un espace mémoire pour le tableau qui va contenir les vecteurs des données sources*/
    chargement_donnees(tab, NbLigneVec,NbCompVec); /* Chargement des données source dans un tableau */

    /*afficheVec(NbLigneVec, NbCompVec); afficher les vecteurs des données source*/

    double * Vecteur_moyen = vecteur_moyen(tab, NbLigneVec, NbCompVec); /* calculer le vecteur moyen */

    ResNrn * ResNrn = InitResNrn(Vecteur_moyen, NbLigneNrn, NbColNrn, NbCompVec); /* Initaliser notre réseau de neurones */

    //afficherResNrn(ResNrn, NbLigneNrn, NbColNrn, NbCompVec); afficher la matrice de notre réseau de neurones avant l'apprentisage//

    Apprentissage(tab, ResNrn, NbLigneVec, NbCompVec, NbLigneNrn, NbColNrn, 500,3,Coef); /* l'étape de l'apprentissage */

    /*afficherResNrn(ResNrn); afficher la matrice de notre réseau de neurones avant l'apprentisage*/

    labeling(tab,ResNrn, NbLigneVec, NbLigneNrn, NbColNrn, NbCompVec); /* Etiquetage de neurones */ 

    return 0;
}
