#include "stdlib.h"
#include "stdio.h"
#include "lecture_fichier_ppm.h"
#include "liste_chainee.h"
#include "calculs.h"

//------------------------------------------------------------

POINT pos_point_intermediaire(POINT depart, POINT arrivee){
	static int num_image = 1;
	POINT intermediaire;
	intermediaire.x = (1-ALPHA(num_image))*(depart.x) + ALPHA(num_image)*depart.x;
	intermediaire.y = (1-ALPHA(num_image))*(depart.y) + ALPHA(num_image)*depart.y;
	num_image++;
	return intermediaire;
}

//------------------------------------------------------------

LISTE_POINTS *intermediaire(){
	LISTE_POINTS *liste_intermediaire;
	liste_intermediaire = malloc(sizeof(LISTE_POINTS));
	init_liste_points(liste_intermediaire);
	FILE *coord_dep = fopen("sauvegarde_points_depart.txt", "r");
	FILE *coord_arr = fopen("sauvegarde_points_arrivee.txt", "r");
	if ((!coord_dep) || (!coord_arr)) return NULL;
	POINT pt_dep;
	POINT pt_arr;
	POINT res;
	while (!feof(coord_dep)){
		fscanf(coord_dep, "%d", &(pt_dep.x));
		fscanf(coord_dep, "%d", &(pt_dep.y));
		fscanf(coord_arr, "%d", &(pt_arr.x));
		fscanf(coord_arr, "%d", &(pt_arr.y));
		res = pos_point_intermediaire(pt_dep, pt_arr);
		inserer_point(liste_intermediaire, res);
	}
	return liste_intermediaire;
}

//------------------------------------------------------------

LISTE_TRIANGLE *premiers_triangles(){
	printf("Transition\n");
	short cpt = 1;
	LISTE_POINTS *a_trianguler = intermediaire();
	if (!a_trianguler) exit(0);
	LISTE_TRIANGLE *res;
	res = malloc(sizeof(LISTE_TRIANGLE));
	init_liste_triangles(res);
	POINT A;
	POINT B;
	POINT C;
	NOEUD *rechercher_pt = a_trianguler -> head;
	while (cpt != 5){
		rechercher_pt = rechercher_pt -> next;
		cpt ++;}
	cpt = 0;
	C.x = rechercher_pt -> value.x;
	C.y = rechercher_pt -> value.y;
	rechercher_pt = a_trianguler -> head;
	while (cpt != 3){
		A.x = rechercher_pt -> next -> value.x;
		A.y = rechercher_pt -> next -> value.y;
		B.x = rechercher_pt -> next -> next -> value.x;
		B.y = rechercher_pt -> next -> next -> value.y;
		inserer_triangle(res, &A, &B, &C);
		rechercher_pt = rechercher_pt -> next;
		cpt ++;}
		B.x = rechercher_pt -> next -> next -> value.x;
		B.y = rechercher_pt -> next -> next -> value.y;
		A.x = a_trianguler -> head -> value.x;
		A.y = a_trianguler -> head -> value.y;
		inserer_triangle(res, &A, &B, &C);
		afficher_liste_triangles(res);
		return res;
	}
		


		
		
