#include <stdio.h>
#include <stdlib.h>

#include "interface.h"
#include "uvsqgraphics_2.h"

typedef struct {
    POINT g;
    POINT d;
} COUPLE;

typedef struct {
    COUPLE *tab;
    int n;
    int cap;
} LISTE;

static void erreur(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

static void liste_init(LISTE *L) {
    L->n = 0;
    L->cap = 16;
    L->tab = malloc(L->cap * sizeof(COUPLE));
    if (!L->tab) erreur("malloc");
}

static void liste_ajout(LISTE *L, POINT g, POINT d) {
    if (L->n == L->cap) {
        L->cap *= 2;
        L->tab = realloc(L->tab, L->cap * sizeof(COUPLE));
        if (!L->tab) erreur("realloc");
    }
    L->tab[L->n].g = g;
    L->tab[L->n].d = d;
    L->n++;
}

static void liste_free(LISTE *L) {
    free(L->tab);
}

static int dans_rectangle(POINT p, POINT hg, POINT bd) {
    return (p.x >= hg.x && p.x <= bd.x &&
            p.y >= hg.y && p.y <= bd.y);
}

/* 5.4.1 */
static void creer_fenetre(int W, int H) {
    init_graphics(W, H);
    affiche_auto_off();
    fill_screen(noir);
    affiche_all();
}

static int to255(int x, int range) {
    if (x < 0) x = 0;
    if (x > range) x = range;
    return (x * 255) / range;
}

static void afficher_image_local(IMAGE I, int x0, int y0) {
    for (int i = 0; i < I.hauteur; i++) {
        for (int j = 0; j < I.largeur; j++) {
            COULEUR c = couleur_RGB(
                to255(I.tab[i][j].r, I.range),
                to255(I.tab[i][j].v, I.range),
                to255(I.tab[i][j].b, I.range)
            );
            POINT p = {x0 + j, y0 + i};
            pixel(p, c);
        }
    }
}

static void dessiner_bouton(POINT hg, POINT bd, const char *texte) {
    draw_fill_rectangle(hg, bd, gris);
    draw_rectangle(hg, bd, blanc);
    POINT c = {(hg.x + bd.x) / 2, (hg.y + bd.y) / 2};
    aff_pol_centre(texte, 22, c, noir);
}

static void sauvegarder(const char *nom, LISTE *L) {
    FILE *f = fopen(nom, "w");
    if (!f) erreur("fopen");

    fprintf(f, "%d\n", L->n);
    for (int i = 0; i < L->n; i++) {
        fprintf(f, "%d %d %d %d\n",
                L->tab[i].g.x, L->tab[i].g.y,
                L->tab[i].d.x, L->tab[i].d.y);
    }
    fclose(f);
}

void interface_couples_points(IMAGE G, IMAGE D,
                              int espace, const char *nom_fichier) {

    int xG = 0;
    int xD = G.largeur + espace;

    int Himg = (G.hauteur > D.hauteur) ? G.hauteur : D.hauteur;
    int W = G.largeur + espace + D.largeur;
    int H = Himg + 90;

    creer_fenetre(W, H);

    POINT btn_save_hg = {W/2 - 170, Himg + 20};
    POINT btn_save_bd = {btn_save_hg.x + 140, btn_save_hg.y + 40};

    POINT btn_quit_hg = {W/2 + 30, Himg + 20};
    POINT btn_quit_bd = {btn_quit_hg.x + 140, btn_quit_hg.y + 40};

    POINT zG_hg = {0, 0};
    POINT zG_bd = {G.largeur - 1, G.hauteur - 1};

    POINT zD_hg = {xD, 0};
    POINT zD_bd = {xD + D.largeur - 1, D.hauteur - 1};

    LISTE L;
    liste_init(&L);

    /* Ajout des 4 coins en tête (projet/TD) */
    liste_ajout(&L, (POINT){0,0}, (POINT){xD,0});
    liste_ajout(&L, (POINT){G.largeur-1,0}, (POINT){xD+D.largeur-1,0});
    liste_ajout(&L, (POINT){0,G.hauteur-1}, (POINT){xD,D.hauteur-1});
    liste_ajout(&L, (POINT){G.largeur-1,G.hauteur-1},
                    (POINT){xD+D.largeur-1,D.hauteur-1});

    int attendre_gauche = 1;
    POINT dernier_gauche = {0,0};

    while (1) {
        fill_screen(noir);

        afficher_image_local(G, 0, 0);
        afficher_image_local(D, xD, 0);

        dessiner_bouton(btn_save_hg, btn_save_bd, "Sauver");
        dessiner_bouton(btn_quit_hg, btn_quit_bd, "Quitter");

        affiche_all();

        POINT clic = wait_clic();

        if (dans_rectangle(clic, btn_save_hg, btn_save_bd)) {
            sauvegarder(nom_fichier, &L);
            continue;
        }
        if (dans_rectangle(clic, btn_quit_hg, btn_quit_bd)) {
            sauvegarder(nom_fichier, &L);
            liste_free(&L);
            return;
        }

        if (attendre_gauche && dans_rectangle(clic, zG_hg, zG_bd)) {
            dernier_gauche = clic;
            attendre_gauche = 0;
        } else if (!attendre_gauche && dans_rectangle(clic, zD_hg, zD_bd)) {
            liste_ajout(&L, dernier_gauche, clic);
            attendre_gauche = 1;
        }
    }
}
