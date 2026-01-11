#ifndef MORPH_DATA_H
#define MORPH_DATA_H

#include <stdlib.h>
#include "morphing_type.h"
#include "couples.h"
#include "geom.h"

/* Structure de données complète comme demandé :
   image + points de base + triangles. :contentReference[oaicite:4]{index=4} */
typedef struct {
    IMAGE img;        /* pixels */
    P2   *pts;        /* points (ex: intermédiaires) */
    int   n_pts;

    TRI  *tris;       /* triangles */
    int   n_tris;
} MORPH_IMAGE;

static inline void morph_image_init(MORPH_IMAGE *M, IMAGE img) {
    M->img = img;
    M->pts = NULL; M->n_pts = 0;
    M->tris = NULL; M->n_tris = 0;
}

static inline void morph_image_free(MORPH_IMAGE *M) {
    free(M->pts);
    free(M->tris);
    /* Les pixels (M->img.tab) sont libérés ailleurs via liberer_image(img) */
    M->pts = NULL; M->n_pts = 0;
    M->tris = NULL; M->n_tris = 0;
}

#endif
