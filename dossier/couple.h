#ifndef COUPLES_H
#define COUPLES_H

typedef struct { int x, y; } P2;

typedef struct {
    P2 dep;  /* point dans l'image de départ */
    P2 arr;  /* point dans l'image d'arrivée */
} COUPLE;

/* Lit un fichier .couplesdepoints
   Retour: nombre de couples M, et *out pointe vers un tableau alloué de M couples */
int lire_couples(const char *filename, COUPLE **out);

#endif
