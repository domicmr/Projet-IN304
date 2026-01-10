#include <stdio.h>
#include <stdlib.h>

#include "triangulation.h"

static void die(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

int trianguler(const P2 *pts_int, int nb_pts, TRI **out_tris) {
    if (nb_pts < 5) {
        fprintf(stderr, "Erreur: nb_pts doit etre >= 5\n");
        exit(EXIT_FAILURE);
    }

    /* Nombre final attendu: 2N - 6 :contentReference[oaicite:5]{index=5} */
    int nb_tris = 0;
    int cap = 4 * nb_pts;
    TRI *T = (TRI*)malloc((size_t)cap * sizeof(TRI));
    if (!T) die("malloc tris");

    /* Étape point 5 : 4 triangles (0-1-4), (1-3-4), (3-2-4), (2-0-4)
       On suppose coins: 0 (HG), 1 (HD), 2 (BG), 3 (BD) ou un ordre équivalent cohérent.
       Même si l’ordre diffère, l’algo marche tant que 0-1-3-2 est le rectangle autour. */
    int P = 4;
    T[nb_tris++] = (TRI){0, 1, P};
    T[nb_tris++] = (TRI){1, 3, P};
    T[nb_tris++] = (TRI){3, 2, P};
    T[nb_tris++] = (TRI){2, 0, P};

    /* Pour chaque nouveau point i >= 5:
       trouver un triangle qui le contient, le supprimer, et ajouter 3 triangles. :contentReference[oaicite:6]{index=6} */
    for (int i = 5; i < nb_pts; i++) {
        int found = -1;
        for (int t = 0; t < nb_tris; t++) {
            P2 A = pts_int[T[t].a];
            P2 B = pts_int[T[t].b];
            P2 C = pts_int[T[t].c];
            if (point_dans_triangle(pts_int[i], A, B, C)) {
                found = t;
                break;
            }
        }
        if (found == -1) {
            fprintf(stderr, "Erreur: point %d hors triangulation\n", i);
            exit(EXIT_FAILURE);
        }

        TRI old = T[found];

        /* supprimer old: swap avec dernier */
        T[found] = T[nb_tris - 1];
        nb_tris--;

        /* ajouter (A,B,i), (B,C,i), (C,A,i) */
        if (nb_tris + 3 >= cap) {
            cap *= 2;
            TRI *tmp = (TRI*)realloc(T, (size_t)cap * sizeof(TRI));
            if (!tmp) die("realloc tris");
            T = tmp;
        }

        T[nb_tris++] = (TRI){old.a, old.b, i};
        T[nb_tris++] = (TRI){old.b, old.c, i};
        T[nb_tris++] = (TRI){old.c, old.a, i};
    }

    *out_tris = T;
    return nb_tris;
}
