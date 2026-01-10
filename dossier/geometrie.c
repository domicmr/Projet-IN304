#include "geom.h"

double cross2(P2 A, P2 B, P2 C) {
    /* (B-A) x (C-A) */
    double x1 = (double)B.x - (double)A.x;
    double y1 = (double)B.y - (double)A.y;
    double x2 = (double)C.x - (double)A.x;
    double y2 = (double)C.y - (double)A.y;
    return x1*y2 - y1*x2;
}

int point_dans_triangle(P2 P, P2 A, P2 B, P2 C) {
    /* Méthode signes des aires orientées */
    double c1 = cross2(A, B, P);
    double c2 = cross2(B, C, P);
    double c3 = cross2(C, A, P);

    int has_neg = (c1 < 0) || (c2 < 0) || (c3 < 0);
    int has_pos = (c1 > 0) || (c2 > 0) || (c3 > 0);

    return !(has_neg && has_pos);
}

int lambda_mu(P2 P, P2 A, P2 B, P2 C, double *lambda, double *mu) {
    /* Résout:
       P-A = lambda*(B-A) + mu*(C-A)
       2x2
    */
    double bx = (double)B.x - (double)A.x;
    double by = (double)B.y - (double)A.y;
    double cx = (double)C.x - (double)A.x;
    double cy = (double)C.y - (double)A.y;

    double px = (double)P.x - (double)A.x;
    double py = (double)P.y - (double)A.y;

    double det = bx*cy - by*cx;
    if (det == 0.0) return 0;

    *lambda = (px*cy - py*cx) / det;
    *mu     = (bx*py - by*px) / det;
    return 1;
}
