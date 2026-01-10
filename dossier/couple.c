#include <stdio.h>
#include <stdlib.h>
#include "couples.h"

static void die(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

int lire_couples(const char *filename, COUPLE **out) {
    FILE *f = fopen(filename, "r");
    if (!f) die("fopen couples");

    int M = 0;
    if (fscanf(f, "%d", &M) != 1 || M <= 0) {
        fprintf(stderr, "Erreur: fichier couples invalide (premiere ligne)\n");
        exit(EXIT_FAILURE);
    }

    COUPLE *T = (COUPLE*)malloc((size_t)M * sizeof(COUPLE));
    if (!T) die("malloc couples");

    for (int i = 0; i < M; i++) {
        int gx, gy, dx, dy;
        if (fscanf(f, "%d %d %d %d", &gx, &gy, &dx, &dy) != 4) {
            fprintf(stderr, "Erreur: lecture couple %d\n", i);
            exit(EXIT_FAILURE);
        }
        T[i].dep.x = gx; T[i].dep.y = gy;
        T[i].arr.x = dx; T[i].arr.y = dy;
    }

    fclose(f);
    *out = T;
    return M;
}
