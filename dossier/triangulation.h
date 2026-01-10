#ifndef TRIANGULATION_H
#define TRIANGULATION_H

#include "couples.h"
#include "geom.h"

/* Construit la triangulation des points points intermédiaires (pts_int).
   Hypothèse sujet: pts_int[0..3] sont les coins du rectangle englobant,
   et il y a au moins 5 points. :contentReference[oaicite:4]{index=4}
   Retour:
   - *out_tris: tableau alloué de triangles
   - nb_tris: taille
   Le caller doit free(*out_tris).
*/
int trianguler(const P2 *pts_int, int nb_pts, TRI **out_tris);

#endif
