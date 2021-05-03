
/* la structure de notre neurone gagnant, le best matche unit  */
struct bmu{
	double distance; /* la distance eculd */
	int ligne; /*La ligne ou se trouve le neurone gagnant */
	int colonne; /* la colonne ou se trouve le neurone gagnant */
};
typedef struct bmu bmu;


/*
 * le shuffle 
 */

int *shuffle(int NbLigneVec)
{
	int *tableau = NULL;
	tableau = malloc(NbLigneVec * sizeof(int));

	for (int i=0; i<NbLigneVec; i++)
	{
		tableau[i] = i;
	}

	for(int i=0;i<NbLigneVec;i++)
	{	int j = rand()%NbLigneVec;
		int k = tableau[i];
		tableau[i]=tableau[j];
		tableau[j]=k;
	}
	return tableau;
}


/*
 * Calculer la distance euclidin entre deux vecteurs.
 */

double distanceEucledienne(double *vec1, double *vec2, int NbCompVec)
{
	double sum=0;
	for(int i=0;i<NbCompVec;i++)
	{
		sum+=pow((vec1[i] - vec2[i]),2);
	}
	return sqrt(sum);
}


/*
 * Calculer le best match unit.
 */

bmu* BestMatchUnit(Neurones **Nrn, double *vec, int NbLigneNrn, int NbColNrn, int NbCompVec)
{
	double DistanceEuc;
	double DistanceEuc_Min = 1000;
	bmu *BMU=malloc(sizeof(bmu)); /* louer un espace mémoire pour notre neurone gagnant*/

	for(int i=0;i<NbLigneNrn;i++)
	{
		for(int j=0;j<NbColNrn;j++)
		{
			DistanceEuc = distanceEucledienne(vec,Nrn[i][j].vecNrn, NbCompVec); /* calculer la distance eucledienne */
			if(DistanceEuc < DistanceEuc_Min)
			{	
				DistanceEuc_Min = DistanceEuc;
				BMU->distance=DistanceEuc_Min;
				BMU->ligne=i;
				BMU->colonne=j;
			}
		}
	}
	return BMU;

}

/*
 * L'Apprentissage
 */

void Apprentissage(vecteur *tab, ResNrn *ResNrn, int NbLigneVec,int NbCompVec, int NbLigneNrn, int NbColNrn,int NombreIter, int Rayon, double Coef)
{
	int *tabShfl = NULL; /* intialiser le tableau qu'on va swapper */

	bmu *BMU=malloc(sizeof(bmu));  /* louer un espace mémoire pour notre neurone gagnant*/
       
	double a = Coef; /* intialiser notre alpha */
        
	for(int i=1; i<=NombreIter; i++)
	{
		Coef = a * (1.0 - (double)(i / (double)NombreIter)); /* modifier notre alpha au fur et à mesure des itérations */
		tabShfl = shuffle(NbLigneVec); /* swapper le tableau qu'on a intialiser */

		if((Rayon > 0) && ((i%(NombreIter / Rayon))==0)) {
					Rayon--;} /* Modifier le rayon au fur et à mesure des itérations */
                  
		for(int j=0;j<NbLigneVec;++j)
		{
			BMU=BestMatchUnit(ResNrn->neurones,tab[tabShfl[j]].vecteur,NbLigneNrn,NbColNrn, NbCompVec);//calculer le best match// 

			/* calculer la ligne ou va commencer et ou va s'arreter le voisinage,
			le cadrer également pour rester dans les limites de notre réseau de neurones*/
			int lMin = BMU->ligne - Rayon;   if (lMin < 0){ lMin=0 ;} 
			int lMax = BMU->ligne + Rayon;   if (lMax >= NbLigneNrn){ lMax = NbLigneNrn - 1 ;}	
		
			/* calculer la colonne ou va commencer et ou va s'arreter le voisinage,
			le cadrer également pour rester dans les limites de notre réseau de neurones*/
			int colMin = BMU->colonne - Rayon;  if (colMin < 0){ colMin=0 ;}
			int colMax = BMU->colonne + Rayon;  if (colMax >= NbColNrn){ colMax = NbColNrn - 1 ;}

			/* Etape de mise à jour */			
		        for(int l=lMin; l<=lMax; l++)
			{ 
				for(int col=colMin; col<=colMax; col++)
				{
					for (int v=0; v< NbCompVec; v++)	
					{
                                           /*appliquer la régles d'apprentissage*/     
     				 ResNrn->neurones[l][col].vecNrn[v] += 
						Coef*(tab[tabShfl[j]].vecteur[v] - ResNrn->neurones[l][col].vecNrn[v]);

					}
				}
			}                        
		}
	} 
}


/*
 * Labeling
 */

void labeling(vecteur *tab, ResNrn *ResNrn, int NbLigneVec , int NbLigneNrn , int NbColNrn, int NbCompVec)
{
    int indice = 0;

    for (int l = 0; l < NbLigneNrn; l++)
    {
        for (int c = 0; c < NbColNrn; c++)
        {
            double DistanceEuc_Min = 1000.0;
            for (int i = 1; i < NbLigneVec; i++)
            {
                double DistanceEuc = distanceEucledienne(tab[i].vecteur, ResNrn->neurones[l][c].vecNrn, NbCompVec); /*calculer la dist Eucldienne*/
                if (DistanceEuc < DistanceEuc_Min)
                {
                    DistanceEuc_Min = DistanceEuc;
                    indice = i;
                }
            }
            
		ResNrn->neurones[l][c].nameNrn = tab[indice].name; /* Récupérer le nom du fleure à partir du vecteur de données */

		/* Affichage des résultats finale
			Iris-setosa = S
			Iris-versicolor = V
			Iris-virginica = Vi */

		if(strcmp(ResNrn->neurones[l][c].nameNrn, "Iris-setosa") == 0){
			printf(" A");
		}

		if(strcmp(ResNrn->neurones[l][c].nameNrn,"Iris-versicolor") == 0){
			printf(" B");
		}

		if(strcmp (ResNrn->neurones[l][c].nameNrn,"Iris-virginica") == 0){
			printf(" C");
		}

        }
	printf("\n");
    }
}

