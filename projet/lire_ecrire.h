#ifndef LIRE_ECRIRE_H
#define LIRE_ECRIRE_H

#include "morphing_type.h"

/* Lecture / écriture PPM (P3) */
IMAGE lire_fichier(char *nom);
void ecrire_fichier(IMAGE I, char *nom);

/* Fusion (TD5) - utile pour test, pas forcément utilisé dans le projet final */
void fusionner(IMAGE A, IMAGE B, char *nom_sortie);

#endif
