#ifndef MORPHING_CORE_H
#define MORPHING_CORE_H

#include "morphing_type.h"
#include "couples.h"
#include "geom.h"

/* Calcule l'image intermédiaire (alpha = k/N) selon le sujet. :contentReference[oaicite:7]{index=7}
   - dep, arr : images
   - couples[0..M-1]
   - tris[0..T-1] triangulation sur les points intermédiaires
   - pts_int : points intermédiaires (taille M)
*/
IMAGE calculer_image_intermediaire(
    IMAGE dep, IMAGE arr,
    const COUPLE *couples, int M,
    const P2 *pts_int,
    const TRI *tris, int T,
    double alpha
);

#endif
