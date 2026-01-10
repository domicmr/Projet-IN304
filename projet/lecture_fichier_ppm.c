/*Nom: TRENDEL
 * Prénom: Eliot
 * Groupe: TD1
 */


#include "stdlib.h"
#include "stdio.h"
#include "uvsqgraphics_2.h"
#define DEBUG 0


typedef struct image{
	int hauteur, largeur;
	int range;
	COULEUR **tab;	//Chaque ligne dans le fichier correspond à une liste chainée,
}IMAGE;				//chaque noeud correspond à un pixel

 
COULEUR **allouer_pixels(unsigned int haut, unsigned int larg){
	COULEUR **tab_l = malloc(haut * sizeof(COULEUR *));
	if (!tab_l){
		printf("Erreur d'allocation de tab");
		exit(1);
	}
	for (int i = 0; i<haut; i++){
		tab_l[i] = malloc(larg * sizeof(COULEUR));
		if (tab_l[i] == NULL){
			printf("Erreur d'allocation de tab[%d]", i);
			exit(1); 
	}
}
	return tab_l;
}

//------------------------------------------------------------

IMAGE lire_fichier(char *nom){
/* si nom du fichier n'existe pas, retourner une erreur
 * Sinon, utiliser fopen pour ouvrir le fichier
 */
 FILE *fichier;
 IMAGE I;
 fichier = fopen(nom, "r");
 if (fichier == NULL){		//Test succès ouverture fichier
	 printf("Ce fichier n'existe pas\n");
	 exit(1);
 }
 char *s = malloc(sizeof(char)*3);
 fscanf(fichier, "%s", s);
 #if DEBUG == 1
 printf("Format: %s", s);
 #endif 
 if (strcmp(s, "P3") != 0){		//Test format fichier
	 fprintf(stderr, "Mauvais format de fichier\n");
	 exit(1);
 }
 printf("Format: %s\n", s);
 fscanf(fichier, "%d", &(I.largeur));
 fscanf(fichier, "%d", &(I.hauteur));
 fscanf(fichier, "%d", &(I.range));
 printf("%d %d (%d)\n", I.largeur, I.hauteur, I.range);
 //Lecture des pixels + allocation mémoire
 int r, g, b;
 I.tab = allouer_pixels(I.hauteur, I.largeur);
 for (int i = 0; i< I.hauteur; i++){		//Récupère composantes RGB pixel et l'affecte 
	 for (int j = 0; j < I.largeur; j++){	//à tab
	 fscanf(fichier, "%d", &r);
	 fscanf(fichier, "%d", &g);
	 fscanf(fichier, "%d", &b);
	 I.tab[i][j] = couleur_RGB(r, g, b);
 }
}
 fclose(fichier);
 free(s);
 s = NULL;
 return I;
}

//------------------------------------------------------------

void ecrire_fichier(IMAGE I, char *nom){
	FILE *F = fopen(nom, "w");
	if (F == NULL){
		printf("Erreur");
		exit(1);
	}
	fprintf(F, "P3\n"); 
	fprintf(F, "%d %d\n", I.largeur, I.hauteur);
	fprintf(F, "%d\n", I.range);
	for (int i=0; i< I.hauteur; i++){
		for (int j = 0; j < I.hauteur; j++){
			COULEUR c = I.tab[i][j];
			int r = (c >> 16) & 0xFF;		//On fait un ET bit-à-bit avec la valeur 255
			int v = (c >> 8) & 0xFF;
			int b = c & 0xFF;
			fprintf(F, "%d %d %d",r, v, b);
		}
		fprintf(F,"\n");
	}
	fclose(F);
}

//------------------------------------------------------------
#if DEBUG == 1
int main(int argc, char **argv){
	//Lecture du fichier au format ppm
	lire_fichier(argv[1]);
}
#endif
