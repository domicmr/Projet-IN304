#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "interpolation.h"

typedef struct { int x, y; } POINT;

typedef struct {
    POINT g;
    POINT d;
} COUPLE;

static void die(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

static int i_round(double x) {
    return (int)(x + (x >= 0 ? 0.5 : -0.5));
}

static int clamp(int x, int a, int b) {
    if (x < a) return a;
    if (x > b) return b;
    return x;
}

static void mkdir_if_needed(const char *dir) {
    mkdir(dir, 0777);
}

static void ecrire_ppm_points(const char *filename, int W, int H, const POINT *pts, int nb_pts) {
    FILE *f = fopen(filename, "w");
    if (!f) die("fopen sortie ppm");

    fprintf(f, "P3\n");
    fprintf(f, "%d %d\n", W, H);
    fprintf(f, "255\n");

    unsigned char *mask = (unsigned char*)calloc((size_t)W * (size_t)H, 1);
    if (!mask) die("calloc mask");

    for (int i = 0; i < nb_pts; i++) {
        int cx = pts[i].x;
        int cy = pts[i].y;
        for (int dy = -1; dy <= 1; dy++) {
            for (int dx = -1; dx <= 1; dx++) {
                int x = cx + dx;
                int y = cy + dy;
                if (x >= 0 && x < W && y >= 0 && y < H) {
                    mask[y * W + x] = 1;
                }
            }
        }
    }

    for (int y = 0; y < H; y++) {
        for (int x = 0; x < W; x++) {
            if (mask[y * W + x]) fprintf(f, "255 255 255\n");
            else                fprintf(f, "0 0 0\n");
        }
    }

    free(mask);
    fclose(f);
}

void generer_interpolation_ppm(const char *couples_file, int N, const char *out_dir) {
    if (N <= 0) {
        fprintf(stderr, "Erreur: N doit etre >= 1\n");
        exit(EXIT_FAILURE);
    }

    FILE *f = fopen(couples_file, "r");
    if (!f) die("fopen couples_file");

    int M = 0;
    if (fscanf(f, "%d", &M) != 1 || M <= 0) {
        fprintf(stderr, "Erreur: fichier couples invalide\n");
        exit(EXIT_FAILURE);
    }

    COUPLE *couples = (COUPLE*)malloc((size_t)M * sizeof(COUPLE));
    if (!couples) die("malloc couples");

    for (int i = 0; i < M; i++) {
        if (fscanf(f, "%d %d %d %d",
                   &couples[i].g.x, &couples[i].g.y,
                   &couples[i].d.x, &couples[i].d.y) != 4) {
            fprintf(stderr, "Erreur: lecture couple %d\n", i);
            exit(EXIT_FAILURE);
        }
    }
    fclose(f);

    if (M < 4) {
        fprintf(stderr, "Erreur: il faut au moins 4 couples (coins)\n");
        exit(EXIT_FAILURE);
    }

    int Wg = 0, Hg = 0, Wd = 0, Hd = 0;
    for (int i = 0; i < 4; i++) {
        if (couples[i].g.x + 1 > Wg) Wg = couples[i].g.x + 1;
        if (couples[i].g.y + 1 > Hg) Hg = couples[i].g.y + 1;
        if (couples[i].d.x + 1 > Wd) Wd = couples[i].d.x + 1;
        if (couples[i].d.y + 1 > Hd) Hd = couples[i].d.y + 1;
    }

    mkdir_if_needed(out_dir);

    POINT *pts = (POINT*)malloc((size_t)M * sizeof(POINT));
    if (!pts) die("malloc pts");

    for (int k = 0; k <= N; k++) {
        double t = (double)k / (double)N;

        for (int i = 0; i < M; i++) {
            double x = (1.0 - t) * (double)couples[i].g.x + t * (double)couples[i].d.x;
            double y = (1.0 - t) * (double)couples[i].g.y + t * (double)couples[i].d.y;
            pts[i].x = i_round(x);
            pts[i].y = i_round(y);
        }

        int Wk = i_round((1.0 - t) * (double)Wg + t * (double)Wd);
        int Hk = i_round((1.0 - t) * (double)Hg + t * (double)Hd);
        Wk = clamp(Wk, 1, 1000000);
        Hk = clamp(Hk, 1, 1000000);

        char filename[1024];
        snprintf(filename, sizeof(filename), "%s/img_%03d.ppm", out_dir, k);
        ecrire_ppm_points(filename, Wk, Hk, pts, M);
    }

    free(pts);
    free(couples);
}
