#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>


/*
 *  Déclaration du structure neurones
 */
struct Neurones
{
	double *vecNrn;
 	char *nameNrn;
};
typedef struct Neurones Neurones;

/*
 *  Structure du réseau de neurones
 */
struct Reseau_de_neurones
{
    Neurones** neurones; 
};
typedef struct Reseau_de_neurones ResNrn; 


/*
 *  calculer le vecteur moyen 
 */

double *vecteur_moyen(vecteur * tab, int NbLigneVec, int NbCompVec)
{
    double *vecteur_moyen = malloc(NbCompVec * sizeof(double));

    for (int i = 0; i < NbCompVec; i++)
    {
        for (int j = 0; j < NbLigneVec; j++)
        {
	    vecteur_moyen[i]+=tab[j].vecteur[i];
        }
        vecteur_moyen[i]/=NbLigneVec;
    }

    return vecteur_moyen;
}

/*
 * Initialiser le réseau des neurones.
 */

ResNrn *InitResNrn(double *Vecteur_moyen,int NbLigenNrn, int NbColNrn, int NbCompVec)
{
        ResNrn *ResNrn = malloc(sizeof(ResNrn));
	ResNrn->neurones = malloc(NbLigenNrn*sizeof(Neurones*));

	for(int i=0;i<NbLigenNrn;i++)
	{
		ResNrn->neurones[i]=malloc(NbColNrn*sizeof(Neurones));
		for(int j=0;j<NbColNrn;j++)
		{	
			ResNrn->neurones[i][j].vecNrn = malloc(NbCompVec*sizeof(double));
			ResNrn->neurones[i][j].nameNrn = NULL;

			for(int k=0;k<NbCompVec;k++)
			{					
				double MaxVecMyn = Vecteur_moyen[k] + 0.05;
				double MinVecMyn = Vecteur_moyen[k] - 0.05;				
				ResNrn->neurones[i][j].vecNrn[k] = (double)rand()/(double)RAND_MAX *(MaxVecMyn - MinVecMyn)+MinVecMyn;
			}

		}
	
	}

            return ResNrn;
}

/*
 * Afficher le réseau des neurones.
 */

void afficherResNrn(ResNrn *MatriceNrn,int NbLigenNrn, int NbColNrn, int NbCompVec)
{

	for(int i=0;i<NbLigenNrn;i++)
	{
		for(int j=0;j<NbColNrn;j++)
		{
			for(int k=0;k<NbCompVec;k++)
			{
				printf(" %f , ",MatriceNrn->neurones[i][j].vecNrn[k]);}
				printf(" %s \n",MatriceNrn->neurones[i][j].nameNrn ); 
		}
	}	
}

