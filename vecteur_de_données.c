/*
 *  Déclaration du structure de vecteur de données
 */

struct vecteur
	{
        double *vecteur;
        char *name;
        double norm;
	};

typedef struct vecteur vecteur;


/*
 *  calculer la normalisation
 */

void normalisation(vecteur * tab,int NbLigneVec, int NbCompVec){
    for(int i = 0; i < NbLigneVec; i++){
        for(int j = 0; j < NbCompVec; j++){
            tab[i].vecteur[j] = (tab[i].vecteur[j])/(tab[i].norm) ; 
        }
    }
}

/*
 *  Afficher le vecteur du données.
 */

void afficheVec(vecteur * tab,int NbLigneVec, int NbCompVec){
	for(int i=0;i<NbLigneVec;i++){
		for(int j=0;j<NbCompVec;j++){
			printf("%i\t", i);
			printf("%f\t", tab[i].vecteur[j]);}
			printf("%s\n", tab[i].name);
			printf("%lf\n", tab[i].norm);}}


/*
 *  Chargement des données source dans un tableau.
 */


void chargement_donnees(vecteur * tab,int NbLigneVec, int NbCompVec)
{
    FILE * fichier; 

    fichier=fopen("iris.data","r"); 

    size_t num_ligne = 0; 
    char *str; 
    char *token;
    char *dbl; 
    double sum; 

	for(int i=0;i<NbLigneVec;i++) 
	{
		sum=0;
                tab[i].vecteur = malloc(NbCompVec*sizeof(double)); /* louer un espace mémoire pour les vecteurs */
		
	        getline(&str, &num_ligne, fichier);  /* récupérer la premiére ligne du fichier. */
	        token = strtok(str,","); 

		/* Remplir les vecteurs avec les 4 flottants  */
		for(int j=0;j<NbCompVec;j++){ 
		    tab[i].vecteur[j] = strtod(token,&dbl);		  
                    sum+= pow(tab[i].vecteur[j],2); 
		    token = strtok(NULL, ",");
		}

		/* Remplir le champ nom */
		tab[i].name = strdup(token); 

		if (tab[i].name[strlen(tab[i].name) - 1] == '\n'){ 
			tab[i].name[strlen(tab[i].name) - 1] = tab[i].name[strlen(tab[i].name)];
			}

		tab[i].norm = sqrt(sum); /* Calculer la norm */
	}
	normalisation(tab, NbLigneVec, NbCompVec); /* Normaliser les vecteurs */	
	free(str);  
	fclose(fichier); /* libérer la mémoire */
}




