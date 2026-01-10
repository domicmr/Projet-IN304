
#ifndef LIST_SET
#define LIST_SET

//------------------------------------//DÉCLARATION STRUCTURES POINTS//------------------------------------//
typedef struct PointNode{
	POINT value;
	struct  PointNode *next;
}NOEUD;

typedef struct liste_points{
	struct PointNode *head;
} LISTE_POINTS;

LISTE_POINTS *liste_depart;
LISTE_POINTS *liste_arrivee;

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
void init_liste_points(LISTE_POINTS* L);

void afficher_liste_points(LISTE_POINTS* L);

void inserer_point(LISTE_POINTS* L, POINT P);

int rechercher_point(LISTE_POINTS* liste_r, int x, int y);

void supprimer_point(LISTE_POINTS* liste_s, int x, int y);

//------------------------------------//PARTIE GESTION LISTE DE TRIANGLES//------------------------------------//
void init_liste_triangles(LISTE_TRIANGLE* L);

void afficher_liste_triangles(LISTE_TRIANGLE* L);

void inserer_triangle(LISTE_TRIANGLE* L, POINT *P1, POINT *P2, POINT *P3);

int rechercher_triangle(LISTE_TRIANGLE* liste_r, POINT *P1, POINT *P2, POINT *P3);

int supprimer_triangle(LISTE_TRIANGLE* liste_s, POINT *P1, POINT *P2, POINT *P3);

#endif
