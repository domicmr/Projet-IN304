#include "afficher.h"
#include "uvsqgraphics_2.h"

static int to_255(int x, int range) {
    if (range <= 0) return 0;
    if (x < 0) x = 0;
    if (x > range) x = range;
    return (x * 255) / range;
}

void afficher_image(IMAGE I, int x0, int y0) {
    for (int i = 0; i < I.hauteur; i++) {
        for (int j = 0; j < I.largeur; j++) {
            int r = to_255(I.tab[i][j].r, I.range);
            int v = to_255(I.tab[i][j].v, I.range);
            int b = to_255(I.tab[i][j].b, I.range);

            COULEUR c = couleur_RGB(r, v, b);

            POINT p;
            p.x = x0 + j;
            p.y = y0 + i;

            pixel(p, c);
        }
    }
}

void afficher_deux_images(IMAGE A, IMAGE B, int espace) {
    int W = A.largeur + espace + B.largeur;
    int H = (A.hauteur > B.hauteur) ? A.hauteur : B.hauteur;

    init_graphics(W, H);
    fill_screen(noir);

    afficher_image(A, 0, 0);
    afficher_image(B, A.largeur + espace, 0);

    affiche_all();
    wait_escape();
}
