#include "stdlib.h"
#include "stdio.h"
#include "uvsqgraphics_2.h"
#include "liste_chainee.h"
#line 3

#ifndef LECTURE
#define LECTURE


typedef struct image{
	int hauteur, largeur;
	int range;
	COULEUR **tab;
	LISTE_TRIANGLE *triangles_image;
}IMAGE;	

COULEUR **allouer_pixels(unsigned int haut, unsigned int larg);

IMAGE lire_fichier(char *nom);

void ecrire_fichier(IMAGE I, char *nom);

#endif
