#include <stdio.h>
#include <stdlib.h>

#include "interpolation.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s fichier.couplesdepoints N\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *couples = argv[1];
    int N = atoi(argv[2]);

    generer_interpolation_ppm(couples, N, "interp");

    printf("Images creees dans le dossier interp (img_000.ppm ... img_%03d.ppm)\n", N);
    return EXIT_SUCCESS;
}
