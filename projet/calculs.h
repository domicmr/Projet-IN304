#ifndef CALCULS
#define CALCULS

#define NOMBRE_IMAGES 5
#define NUM_IMAGE 1
#define ALPHA(k) k/NOMBRE_IMAGES 
#define DEBUG 1

POINT pos_point_intermediaire(POINT depart, POINT arrivee);

LISTE_POINTS *intermediaire();

LISTE_TRIANGLE *premiers_triangles();

#endif
