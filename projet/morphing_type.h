#ifndef MORPHING_TYPE_H
#define MORPHING_TYPE_H

#include <stdlib.h>

typedef struct {
    int r, v, b;
} COULEUR;

typedef struct {
    int hauteur, largeur;
    int range;
    COULEUR **tab;   /* tab[i][j] */
} IMAGE;

/* Allocation/libération */
IMAGE allouer_pixels(int largeur, int hauteur, int range);
void liberer_image(IMAGE I);

#endif
