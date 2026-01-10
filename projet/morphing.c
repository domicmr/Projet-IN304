#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lire_ecrire.h"
#include "interface.h"

static const char* basename_simple(const char *path) {
    const char *p = strrchr(path, '/');
    return (p != NULL) ? (p + 1) : path;
}

static void sans_extension_ppm(char *dst, size_t dstsz, const char *src) {
    const char *base = basename_simple(src);
    size_t n = strlen(base);

    if (n >= 4 && strcmp(base + (n - 4), ".ppm") == 0) n -= 4;

    if (n + 1 > dstsz) {
        fprintf(stderr, "Erreur: nom trop long\n");
        exit(EXIT_FAILURE);
    }

    memcpy(dst, base, n);
    dst[n] = '\0';
}

static void construire_nom_sortie(char *out, size_t outsz, const char *f1, const char *f2) {
    char n1[512], n2[512];
    sans_extension_ppm(n1, sizeof(n1), f1);
    sans_extension_ppm(n2, sizeof(n2), f2);

    int needed = snprintf(out, outsz, "%s_%s.couplesdepoints", n1, n2);
    if (needed < 0 || (size_t)needed >= outsz) {
        fprintf(stderr, "Erreur: nom de sortie trop long\n");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage : %s nom1.ppm nom2.ppm\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *img1 = argv[1];
    const char *img2 = argv[2];

    char fichier_couples[1024];
    construire_nom_sortie(fichier_couples, sizeof(fichier_couples), img1, img2);

    IMAGE I1 = lire_fichier((char*)img1);
    IMAGE I2 = lire_fichier((char*)img2);

    interface_couples_points(I1, I2, 20, fichier_couples);

    liberer_image(I1);
    liberer_image(I2);

    printf("Couples de points sauvegardes dans %s\n", fichier_couples);
    return EXIT_SUCCESS;
}
