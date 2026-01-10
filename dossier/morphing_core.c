#include <stdio.h>
#include <stdlib.h>

#include "morphing_core.h"
#include "triangulation.h"

/* clamp composante */
static int clampi(int x, int a, int b) {
    if (x < a) return a;
    if (x > b) return b;
    return x;
}

/* échantillonnage nearest-neighbor */
static COULEUR sample_nn(IMAGE I, P2 p) {
    int x = clampi(p.x, 0, I.largeur - 1);
    int y = clampi(p.y, 0, I.hauteur - 1);
    return I.tab[y][x];
}

/* Trouve triangle contenant P (dans l'image intermédiaire) */
static int trouver_triangle(P2 P, const P2 *pts, const TRI *tris, int T) {
    for (int t = 0; t < T; t++) {
        P2 A = pts[tris[t].a];
        P2 B = pts[tris[t].b];
        P2 C = pts[tris[t].c];
        if (point_dans_triangle(P, A, B, C)) return t;
    }
    return -1;
}

IMAGE calculer_image_intermediaire(
    IMAGE dep, IMAGE arr,
    const COUPLE *couples, int M,
    const P2 *pts_int,
    const TRI *tris, int T,
    double alpha
) {
    /* Taille image intermédiaire : interpolation linéaire des tailles (idée TD6) */
    int W = (int)((1.0 - alpha) * dep.largeur + alpha * arr.largeur + 0.5);
    int H = (int)((1.0 - alpha) * dep.hauteur + alpha * arr.hauteur + 0.5);
    if (W < 1) W = 1;
    if (H < 1) H = 1;

    IMAGE out = allouer_pixels(W, H, 255);

    for (int y = 0; y < H; y++) {
        for (int x = 0; x < W; x++) {
            P2 P = {x, y};

            int tid = trouver_triangle(P, pts_int, tris, T);
            if (tid < 0) {
                /* fond noir si hors triangulation (ne devrait pas arriver si coins corrects) */
                out.tab[y][x] = (COULEUR){0,0,0};
                continue;
            }

            TRI tr = tris[tid];
            P2 A = pts_int[tr.a];
            P2 B = pts_int[tr.b];
            P2 C = pts_int[tr.c];

            double lambda, mu;
            if (!lambda_mu(P, A, B, C, &lambda, &mu)) {
                out.tab[y][x] = (COULEUR){0,0,0};
                continue;
            }

            /* Calcul PD dans image départ:
               PD = AD + lambda*(BD-AD) + mu*(CD-AD) :contentReference[oaicite:8]{index=8} */
            P2 AD = couples[tr.a].dep;
            P2 BD = couples[tr.b].dep;
            P2 CD = couples[tr.c].dep;

            double pdx = (double)AD.x + lambda*((double)BD.x - (double)AD.x) + mu*((double)CD.x - (double)AD.x);
            double pdy = (double)AD.y + lambda*((double)BD.y - (double)AD.y) + mu*((double)CD.y - (double)AD.y);

            /* Calcul PA dans image arrivée */
            P2 AA = couples[tr.a].arr;
            P2 BA = couples[tr.b].arr;
            P2 CA = couples[tr.c].arr;

            double pax = (double)AA.x + lambda*((double)BA.x - (double)AA.x) + mu*((double)CA.x - (double)AA.x);
            double pay = (double)AA.y + lambda*((double)BA.y - (double)AA.y) + mu*((double)CA.y - (double)AA.y);

            COULEUR cD = sample_nn(dep, (P2){(int)(pdx + 0.5), (int)(pdy + 0.5)});
            COULEUR cA = sample_nn(arr, (P2){(int)(pax + 0.5), (int)(pay + 0.5)});

            /* Interpolation couleur (1-alpha)*cD + alpha*cA :contentReference[oaicite:9]{index=9} */
            int r = (int)((1.0 - alpha) * (double)cD.r + alpha * (double)cA.r + 0.5);
            int v = (int)((1.0 - alpha) * (double)cD.v + alpha * (double)cA.v + 0.5);
            int b = (int)((1.0 - alpha) * (double)cD.b + alpha * (double)cA.b + 0.5);

            out.tab[y][x].r = clampi(r, 0, 255);
            out.tab[y][x].v = clampi(v, 0, 255);
            out.tab[y][x].b = clampi(b, 0, 255);
        }
    }

    return out;
}
