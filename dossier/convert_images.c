#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Usage:
   ./convert_images in1.jpg in2.jpg
   -> crée ./avant/ et ./apres/
   -> convertit in1,in2 en PPM dans ./apres/ (P3)
   (tu peux aussi donner des .ppm : il recopie)
*/

static const char* basename_simple(const char *path) {
    const char *p = strrchr(path, '/');
    return (p != NULL) ? (p + 1) : path;
}

static void sans_ext(char *dst, size_t dstsz, const char *src) {
    const char *b = basename_simple(src);
    size_t n = strlen(b);
    /* retire dernière extension .xxx si présente */
    for (size_t i = n; i > 0; i--) {
        if (b[i-1] == '.') { n = i-1; break; }
        if (b[i-1] == '/') break;
    }
    if (n + 1 > dstsz) { fprintf(stderr, "nom trop long\n"); exit(1); }
    memcpy(dst, b, n);
    dst[n] = '\0';
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s image1 image2\n", argv[0]);
        return 1;
    }

    /* dossiers demandés par le sujet */
    system("mkdir -p avant");
    system("mkdir -p apres");

    /* copier les originaux dans avant/ */
    {
        char cmd[2048];
        snprintf(cmd, sizeof(cmd), "cp \"%s\" \"avant/%s\"", argv[1], basename_simple(argv[1]));
        system(cmd);
        snprintf(cmd, sizeof(cmd), "cp \"%s\" \"avant/%s\"", argv[2], basename_simple(argv[2]));
        system(cmd);
    }

    /* convertir vers PPM (P3) dans apres/ via ImageMagick */
    for (int i = 1; i <= 2; i++) {
        char base[512];
        sans_ext(base, sizeof(base), argv[i]);

        char out[1024];
        snprintf(out, sizeof(out), "apres/%s.ppm", base);

        char cmd[2048];

        /* "magick" est le plus courant ; si chez vous c’est "convert", remplace magick par convert */
        snprintf(cmd, sizeof(cmd), "magick \"%s\" -compress none ppm:%s", argv[i], out);
        int r = system(cmd);
        if (r != 0) {
            fprintf(stderr, "Erreur conversion (commande): %s\n", cmd);
            fprintf(stderr, "Astuce: si 'magick' n'existe pas, remplace par 'convert'.\n");
            return 1;
        }
    }

    printf("OK. Images converties dans ./apres/ en .ppm\n");
    return 0;
}
