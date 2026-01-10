#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lire_ecrire.h"

static void die(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

IMAGE allouer_pixels(int largeur, int hauteur, int range) {
    IMAGE I;
    I.hauteur = hauteur;
    I.largeur = largeur;
    I.range = range;

    I.tab = malloc(hauteur * sizeof(COULEUR *));
    if (!I.tab) die("malloc tab");

    for (int i = 0; i < hauteur; i++) {
        I.tab[i] = malloc(largeur * sizeof(COULEUR));
        if (!I.tab[i]) die("malloc tab[i]");
    }
    return I;
}

void liberer_image(IMAGE I) {
    if (I.tab) {
        for (int i = 0; i < I.hauteur; i++) {
            free(I.tab[i]);
        }
        free(I.tab);
    }
}

IMAGE lire_fichier(char *nom) {
    FILE *f = fopen(nom, "r");
    if (!f) die("fopen lecture");

    char magic[3];
    if (fscanf(f, "%2s", magic) != 1) die("lecture magic");

    if (strcmp(magic, "P3") != 0) {
        fprintf(stderr, "Erreur: format attendu P3, trouvé %s\n", magic);
        exit(EXIT_FAILURE);
    }

    int largeur, hauteur, range;
    if (fscanf(f, "%d %d", &largeur, &hauteur) != 2) die("lecture dimensions");
    if (fscanf(f, "%d", &range) != 1) die("lecture range");

    IMAGE img = allouer_pixels(largeur, hauteur, range);

    for (int i = 0; i < hauteur; i++) {
        for (int j = 0; j < largeur; j++) {
            if (fscanf(f, "%d %d %d",
                       &img.tab[i][j].r,
                       &img.tab[i][j].v,
                       &img.tab[i][j].b) != 3) {
                die("lecture pixel");
            }
        }
    }

    fclose(f);
    return img;
}

void ecrire_fichier(IMAGE I, char *nom) {
    FILE *f = fopen(nom, "w");
    if (!f) die("fopen ecriture");

    fprintf(f, "P3\n");
    fprintf(f, "%d %d\n", I.largeur, I.hauteur);
    fprintf(f, "%d\n", I.range);

    for (int i = 0; i < I.hauteur; i++) {
        for (int j = 0; j < I.largeur; j++) {
            fprintf(f, "%d %d %d\n",
                    I.tab[i][j].r,
                    I.tab[i][j].v,
                    I.tab[i][j].b);
        }
    }

    fclose(f);
}

void fusionner(IMAGE A, IMAGE B, char *nom_sortie) {
    if (A.largeur != B.largeur || A.hauteur != B.hauteur) {
        fprintf(stderr, "Erreur: tailles des images différentes\n");
        exit(EXIT_FAILURE);
    }
    if (A.range != B.range) {
        fprintf(stderr, "Erreur: range différents (A=%d, B=%d)\n", A.range, B.range);
        exit(EXIT_FAILURE);
    }

    IMAGE F = allouer_pixels(A.largeur, A.hauteur, A.range);

    for (int i = 0; i < A.hauteur; i++) {
        for (int j = 0; j < A.largeur; j++) {
            F.tab[i][j].r = (A.tab[i][j].r + B.tab[i][j].r) / 2;
            F.tab[i][j].v = (A.tab[i][j].v + B.tab[i][j].v) / 2;
            F.tab[i][j].b = (A.tab[i][j].b + B.tab[i][j].b) / 2;
        }
    }

    ecrire_fichier(F, nom_sortie);
    liberer_image(F);
}
