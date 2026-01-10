// Nom: Eliot
// Date: 9/01/2026
// Groupe: TD1

#include "stdio.h"
#include "stdlib.h"
#include "uvsqgraphics_2.h"


#define DEBUG 0

//------------------------------------//DÉCLARATION STRUCTURES POINTS//------------------------------------//
typedef struct PointNode{
	POINT value;
	struct  PointNode *next;
}NOEUD;

typedef struct liste_points{
	NOEUD *head;
} LISTE_POINTS;

//------------------------------------//DÉCLARATION STRUCTURES TRIANGLES//------------------------------------//
typedef struct Triangle{
	POINT *a;
	POINT *b;
	POINT *c;
	struct Triangle *next;
} TRIANGLE;

typedef struct liste_triangle{
	TRIANGLE *suiv;
} LISTE_TRIANGLE;

//------------------------------------//PARTIE GESTION LISTE DE POINTS//------------------------------------//


void init_liste_points(LISTE_POINTS* L){
	L->head = NULL;
}


void afficher_liste_points(LISTE_POINTS* L){
	NOEUD *arr;
	arr = L-> head;
	while (arr != NULL){
		printf("Point(%d, %d)\n", arr -> value.x, arr -> value.y);
		arr = arr -> next;
	}
}

void inserer_point(LISTE_POINTS* L, POINT P){
	NOEUD *n = malloc(sizeof(NOEUD));
	n -> value = P;
	n-> next = L -> head;
	L -> head = n;
}

int rechercher_point(LISTE_POINTS* liste_r, int x, int y){
	NOEUD *arr;
	arr = liste_r -> head;
	while (arr != NULL){
		if ((arr -> value.x == x) && (arr -> value.y == y)){
			printf("Le point existe\n");
			return 1;
		}
		arr= arr-> next;
	}
	printf("Le point recherché n'est pas dans la liste\n");
	return 0;
}

int supprimer_point(LISTE_POINTS* liste_s, int x, int y){
	NOEUD *pt2;
	pt2 = liste_s -> head;
	if (rechercher_point(liste_s, x, y)){
		while (pt2 != NULL){
		if ((pt2-> next -> value.x == x) && (pt2 -> next -> value.y == y)){
				pt2 -> next = pt2 -> next -> next;
				return 1;
			}
		pt2 = pt2 -> next;
		}
	}
	return 0;
}
				 
//------------------------------------//PARTIE GESTION LISTE DE TRIANGLES//------------------------------------//
void init_liste_triangles(LISTE_TRIANGLE* L){
	L -> suiv = NULL;
}

void afficher_liste_triangles(LISTE_TRIANGLE* L){
	TRIANGLE *arr;
	arr = L -> suiv;
	while (arr != NULL){
		printf("Points du triangle: (%d, %d)\t(%d, %d)\t(%d, %d)\n", arr -> a -> x, arr -> a -> y, arr -> b -> x, arr -> b -> y, arr -> c -> x, arr -> c -> y);
		arr = arr -> next;
	}
}

void inserer_triangle(LISTE_TRIANGLE* L, POINT *P1, POINT *P2, POINT *P3){
	TRIANGLE *n = malloc(sizeof(TRIANGLE));
	n -> a= P1;
	n -> b = P2;
	n -> c = P3;
	n -> next = L -> suiv;
	L -> suiv = n;
}

int rechercher_triangle(LISTE_TRIANGLE* liste_r, POINT *P1, POINT *P2, POINT *P3){
	TRIANGLE *arr;
	arr = liste_r -> suiv;
	while (arr != NULL){
		if ((arr -> a == P1) && (arr -> b == P2) && (arr -> c == P3)){
			printf("Le triangle existe\n");
			return 1;
		}
		arr= arr-> next;
	}
	printf("Le triangle recherché n'est pas dans la liste\n");
	return 0;
}

int supprimer_triangle(LISTE_TRIANGLE* liste_s, POINT *P1, POINT *P2, POINT *P3){
	TRIANGLE *pt2;
	pt2 = liste_s -> suiv;
	if (pt2 != NULL){
		if (pt2 -> next == NULL){	//Cas où la liste ne contient qu'un seul triangle
			liste_s -> suiv = NULL;
			return 1;
		}
		while (pt2 -> next != NULL){	//Tant que l'on a pas atteint la fin de la liste
			if (((pt2 -> a -> x == P1 -> x) && (pt2 -> a -> y == P1 -> y)) && ((pt2 -> b -> x == P2 -> x) && (pt2 -> b -> y == P2 -> y)) && ((pt2 -> c -> x == P3 -> x) && (pt2 -> c -> y == P3 -> y))){	//Cas où l'élément à supprimer est en première position
				liste_s -> suiv = pt2 -> next;
				return 1;}
				
			if (((pt2 ->next -> a -> x == P1 -> x) && (pt2 -> next -> a -> y == P1 -> y)) && ((pt2 ->next -> b -> x == P2 -> x) && (pt2 -> next -> b -> y == P2 -> y)) && ((pt2 ->next -> c -> x == P3 -> x) && (pt2 -> next -> c -> y == P3 -> y))){
	
				if ((pt2 -> next -> next == NULL)){ pt2 -> next = NULL;}	//Cas où l'élément à supprimer est en dernière position
				else{ pt2 -> next = pt2 -> next -> next;}
					return 1;
				}
			pt2 = pt2 -> next;
		}
	}
	return 0;
}

//------------------------------------//PROGRAMME PRINCIPAL//------------------------------------//
#if DEBUG == 1
int main(){
	LISTE_POINTS *test = malloc(sizeof(LISTE_POINTS));
	LISTE_TRIANGLE *test2 = malloc(sizeof(LISTE_TRIANGLE));
	POINT P1_test = {10, 20};
	POINT P2_test = {11, 21};
	POINT P3_test = {12, 22};
	
	POINT P4_test = {11, 20};
	POINT P5_test = {12, 21};
	POINT P6_test = {13, 22};
	
	//Partie liste points
	init_liste_points(test);
	inserer_point(test, P1_test);
	inserer_point(test, P2_test);
	inserer_point(test, P3_test);
	afficher_liste_points(test);
	rechercher_point(test, 20, 30);
	supprimer_point(test, 10, 20);
	afficher_liste_points(test);
	//Partie liste triangles
	init_liste_triangles(test2);
	inserer_triangle(test2, &P1_test, &P2_test, &P3_test);
	inserer_triangle(test2, &P4_test, &P5_test, &P6_test);
	afficher_liste_triangles(test2);
	supprimer_triangle(test2, &P4_test, &P5_test, &P6_test);
	rechercher_triangle(test2, &P4_test, &P5_test, &P6_test);
	afficher_liste_triangles(test2);
	return EXIT_SUCCESS;
}
#endif	
