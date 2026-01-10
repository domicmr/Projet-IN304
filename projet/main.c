#include "lecture_fichier_ppm.h"
#include "gui.h"
#include "liste_chainee.h"
#include "calculs.h"

int main(){
	affiche_auto_off();
	liste_depart = malloc(sizeof(LISTE_POINTS));
	liste_arrivee = malloc(sizeof(LISTE_POINTS));
	init_liste_points(liste_depart);
	init_liste_points(liste_arrivee);
	redimensionner_image();
	POINT P1 = {40, 20};
	int h1 = i1.hauteur;
	int L1 = i1.largeur;
	int h2 = i2.hauteur;
	int L2 = i2.largeur;
	int pt_depart_im2 = 2*max(L1, L2);
	POINT P2 = {pt_depart_im2, 20};
	init_graphics(3*max(L1, L2)+40, max(h1, h2)+100);
	fenetre();
	printf("C'est correct\n");
	premiers_triangles();
	wait_escape();
}
