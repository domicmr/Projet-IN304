#include <stdio.h>
#include <stdlib.h>

#include "interface.h"
#include "uvsqgraphics_2.h"

typedef struct {
    POINT g;
    POINT d;
} COUPLE_P;

typedef struct {
    COUPLE_P *tab;
    int n;
    int cap;
} LISTE;

static void erreur(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

static void liste_init(LISTE *L) {
    L->n = 0;
    L->cap = 32;
    L->tab = malloc(L->cap * sizeof(COUPLE_P));
    if (!L->tab) erreur("malloc");
}

static void liste_ajout(LISTE *L, POINT g, POINT d) {
    if (L->n == L->cap) {
        L->cap *= 2;
        L->tab = realloc(L->tab, L->cap * sizeof(COUPLE_P));
        if (!L->tab) erreur("realloc");
    }
    L->tab[L->n].g = g;
    L->tab[L->n].d = d;
    L->n++;
}

static void liste_free(LISTE *L) {
    free(L->tab);
    L->tab = NULL;
    L->n = 0;
    L->cap = 0;
}

static int dans_rectangle(POINT p, POINT hg, POINT bd) {
    return (p.x >= hg.x && p.x <= bd.x && p.y >= hg.y && p.y <= bd.y);
}

/* 5.4.1 : création fenêtre (étape 3 du sujet)  */
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

/* Sauvegarde au format demandé par le sujet : M puis gx gy dx dy :contentReference[oaicite:7]{index=7} */
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

/* Dessine cercles + numéros sur les points + liste en bas  */
static void afficher_couples_overlay(const LISTE *L, int xD, int Himg, int W, int panel_h) {
    /* Cercles + numéros sur images */
    for (int i = 0; i < L->n; i++) {
        int num = i + 1; /* affichage 1..n */
        POINT g = L->tab[i].g;
        POINT d = L->tab[i].d;

        draw_circle(g, 6, jaune);
        draw_circle(d, 6, jaune);

        POINT tg = {g.x + 8, g.y - 8};
        POINT td = {d.x + 8, d.y - 8};
        aff_int(num, 16, tg, jaune);
        aff_int(num, 16, td, jaune);
    }

    /* Panneau bas : liste des couples */
    POINT panel_hg = {0, Himg};
    POINT panel_bd = {W - 1, Himg + panel_h - 1};
    draw_fill_rectangle(panel_hg, panel_bd, noir);
    draw_rectangle(panel_hg, panel_bd, blanc);

    POINT title = {10, Himg + 10};
    aff_pol("Couples (num: (xg,yg) -> (xd,yd))", 18, title, blanc);

    int y = Himg + 35;
    int max_lines = (panel_h - 45) / 18; /* approx 18 px par ligne */
    int start = 0;
    if (L->n > max_lines) start = L->n - max_lines; /* afficher les derniers */

    for (int i = start; i < L->n; i++) {
        char buf[128];
        int num = i + 1;
        snprintf(buf, sizeof(buf), "%d: (%d,%d) -> (%d,%d)",
                 num,
                 L->tab[i].g.x, L->tab[i].g.y,
                 L->tab[i].d.x, L->tab[i].d.y);

        POINT p = {10, y};
        aff_pol(buf, 16, p, blanc);
        y += 18;
    }
}

void interface_couples_points(IMAGE G, IMAGE D, int espace, const char *nom_fichier) {
    int xG = 0;
    int xD = G.largeur + espace;

    int Himg = (G.hauteur > D.hauteur) ? G.hauteur : D.hauteur;
    int W = G.largeur + espace + D.largeur;

    int panel_h = 170; /* zone "milieu/bas" pour afficher les couples */
    int H = Himg + panel_h;

    creer_fenetre(W, H);

    POINT btn_save_hg = {W/2 - 170, Himg + panel_h - 60};
    POINT btn_save_bd = {btn_save_hg.x + 140, btn_save_hg.y + 40};

    POINT btn_quit_hg = {W/2 + 30, Himg + panel_h - 60};
    POINT btn_quit_bd = {btn_quit_hg.x + 140, btn_quit_hg.y + 40};

    POINT zG_hg = {0, 0};
    POINT zG_bd = {G.largeur - 1, G.hauteur - 1};

    POINT zD_hg = {xD, 0};
    POINT zD_bd = {xD + D.largeur - 1, D.hauteur - 1};

    LISTE L;
    liste_init(&L);

    /* Ajout des 4 coins au début (exigence sujet) :contentReference[oaicite:9]{index=9} */
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

        afficher_couples_overlay(&L, xD, Himg, W, panel_h);

        dessiner_bouton(btn_save_hg, btn_save_bd, "Sauver");
        dessiner_bouton(btn_quit_hg, btn_quit_bd, "Quitter");

        /* message d'aide */
        POINT aide = {10, Himg + panel_h - 95};
        if (attendre_gauche) aff_pol("Cliquez sur l'image de gauche", 16, aide, blanc);
        else                aff_pol("Cliquez sur l'image de droite", 16, aide, blanc);

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
