#ifndef GEOM_H
#define GEOM_H

#include "couples.h"

/* Triangle défini par indices de sommets dans un tableau de points */
typedef struct { int a, b, c; } TRI;

/* Aire orientée 2D (produit vectoriel) */
double cross2(P2 A, P2 B, P2 C);

/* Test "P est dans le triangle ABC" (inclus bords) */
int point_dans_triangle(P2 P, P2 A, P2 B, P2 C);

/* Calcule (lambda, mu) tels que:
   P = A + lambda*(B-A) + mu*(C-A)
   Retour 1 si OK, 0 si triangle dégénéré. */
int lambda_mu(P2 P, P2 A, P2 B, P2 C, double *lambda, double *mu);

#endif
