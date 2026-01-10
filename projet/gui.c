/*Nom: TRENDEL
 * Prénom: Eliot
 * Groupe: TD1
 */
 
#include "stdlib.h"
#include "stdio.h"
#include "uvsqgraphics_2.h"
#include "lecture_fichier_ppm.h"
#include "liste_chainee.h"
#include "gui.h"
#include "stdbool.h"

#define IMAGE_1 "./output_pic/test_image.ppm"
#define IMAGE_2 "./output_pic/test_image_arr.ppm"
#define CONVERT_COMMANDE "mogrify "

#define DEBUG 0

IMAGE i1;
IMAGE i2;

//------------------------------------------------------------
	
void sauver(){	//Affiche le bouton Sauver
	char sauver_texte[7] = "Sauver";
	POINT PS1 = {i1.largeur+40,HAUTEUR_FENETRE-20};
	POINT PS2 = {i1.largeur+150, HAUTEUR_FENETRE-55};
	POINT PSTEXT = {PS1.x +5, PS1.y -40};
	draw_fill_rectangle(PS1, PS2, gris);
	aff_pol(sauver_texte, 30, PSTEXT, noir);
}

//------------------------------------------------------------

void quitter(){	//Affiche le bouton Quitter
	char quitter_texte[7] = "Quitter";
	int x1 = 2*max(i1.largeur, i2.largeur);
	POINT PQ1 = {x1-110, HAUTEUR_FENETRE-20};
	POINT PQ2 = {x1, HAUTEUR_FENETRE-55};
	POINT PQTEXT = {PQ1.x +5, PQ1.y -40};
	draw_fill_rectangle(PQ1, PQ2, gris);
	aff_pol(quitter_texte, 30, PQTEXT, noir);
}

//------------------------------------------------------------

void redimensionner_image(){		//Fonction pour obtenir 2 images de tailles similaires
    //Déclaration des variables
    char commande1[120];
    char commande2[120];
    
    //Redimensionnement image de départ
	strcpy(commande1, "mogrify "); 
	strcat(commande1, "-resize 400x400 ");
	strcat(commande1, IMAGE_1);
	system(commande1);
	strcpy(commande1, "");
	strcpy(commande1, "convert "); 
	strcat(commande1, IMAGE_1);
	strcat(commande1, " -compress none ");
	strcat(commande1, IMAGE_1);
	system(commande1);
	
	//Redimensionnement image d'arrivée
	strcpy(commande2, "mogrify "); 
	strcat(commande2, "-resize 400x400 ");
	strcat(commande2, IMAGE_2);
	system(commande2);
	strcpy(commande2, "");
	strcpy(commande2, "convert "); 
	strcat(commande2, IMAGE_2);
	strcat(commande2, " -compress none ");
	strcat(commande2, IMAGE_2);
	system(commande2);
	i1 = lire_fichier(IMAGE_1);
	i2 = lire_fichier(IMAGE_2);
}

//------------------------------------------------------------

void fenetre(){		//Affiche tous les éléments graphiques de la fenêtre, sauf les points
	POINT P1 = {40, 20};
	int h1 = i1.hauteur;
	int L1 = i1.largeur;
	int h2 = i2.hauteur;
	int L2 = i2.largeur;
	int pt_depart_im2 = 2*max(L1, L2);
	POINT P2 = {pt_depart_im2, 20};
	fill_screen(antiquewhite);
	sauver();
	quitter();
	for (int i =0; i<h1-1; i++){
		P1.x = 40;
		for (int j = 0; j<L1; j++){
			P1.x = 40+ j;
			draw_pixel(P1, i1.tab[i][j]);
		}
		P1.y= 20 + i;
	}
	for (int Haut =0; Haut<h2-1; Haut++){
		P2.x = pt_depart_im2;
		for (int j2 = 0; j2<L2; j2++){
			P2.x = pt_depart_im2+ j2;
			draw_pixel(P2, i2.tab[Haut][j2]);
		}
		P2.y= 20 + Haut;
	}
	//printf("Test\n");
	
	afficher_point_fenetre();	
}

//------------------------------------------------------------

void action_sauver(LISTE_POINTS *parcours_depart, LISTE_POINTS *parcours_arrivee){		//Charge dans le fichier sauvegarde_points.txt les coordonnées des points
	FILE *sauvegarde_d = fopen("sauvegarde_points_depart.txt", "w");
	FILE *sauvegarde_a = fopen("sauvegarde_points_arrivee.txt", "w");
	NOEUD *P_d = malloc(sizeof(NOEUD));
	NOEUD *P_a = malloc(sizeof(NOEUD));
	afficher_liste_points(parcours_depart);
	printf("Liste points image d'arrivée\n");
	afficher_liste_points(parcours_arrivee);
	P_d = parcours_depart -> head;
	P_a = parcours_arrivee -> head;
	while (P_d != NULL){
		fprintf(sauvegarde_d, "%d %d ", P_d  -> value.x, P_d -> value.y);
		P_d = P_d -> next;
	}
	while (P_a != NULL){
		fprintf(sauvegarde_a, "%d %d ", P_a  -> value.x, P_a -> value.y);
		P_a = P_a -> next;
	}
	fclose(sauvegarde_d);
	fclose(sauvegarde_a);
	free(P_d);
	free(P_a);
	P_d = NULL;
	P_a = NULL;
}
	
//------------------------------------------------------------

void affiche_avant_clic(){		//Appelé une seule fois pour dessiner les éléments lors de l'ouverture de la fenêtre
	affiche_all();
	POINT P1 = {40, 20};
	int h1 = i1.hauteur;
	int L1 = i1.largeur;
	int h2 = i2.hauteur;
	int L2 = i2.largeur;
	int pt_depart_im2 = 2*max(L1, L2);
	POINT P2 = {pt_depart_im2, 20};
	fill_screen(antiquewhite);
	sauver();
	quitter();
	for (int i =0; i<h1-1; i++){
		P1.x = 40;
		for (int j = 0; j<L1; j++){
			P1.x = 40+ j;
			draw_pixel(P1, i1.tab[i][j]);
		}
		P1.y= 20 + i;
	}
	for (int Haut =0; Haut<h2-1; Haut++){
		P2.x = pt_depart_im2;
		for (int j2 = 0; j2<L2; j2++){
			P2.x = pt_depart_im2+ j2;
			draw_pixel(P2, i2.tab[Haut][j2]);
		}
		P2.y= 20 + Haut;
	}
}
	
//------------------------------------------------------------

void affiche_num_point(POINT point_affiche, int numero){
	POINT NUM;
	NUM.x = (point_affiche.x)+5;
	NUM.y = (point_affiche.y)-5;
	aff_int(numero, 20, NUM, lime);
}

//------------------------------------------------------------

void ajout_ptbase_depart(LISTE_POINTS *liste){
	POINT AJOUT = {40, 20};
	inserer_point(liste, AJOUT);
	AJOUT.x= i1.hauteur+40;
	AJOUT.y = 20;
	inserer_point(liste, AJOUT);
	AJOUT.x= 40;
	AJOUT.y = i1.hauteur+20;
	inserer_point(liste, AJOUT);
	AJOUT.x = i1.largeur+40;
	AJOUT.y = i1.hauteur+20;
	inserer_point(liste, AJOUT);
}

//------------------------------------------------------------

void ajout_ptbase_arrivee(LISTE_POINTS *liste_a){
	POINT AJOUT = {2*max(i1.hauteur, i2.hauteur), 20};
	inserer_point(liste_a, AJOUT);
	AJOUT.y = i2.hauteur+20;
	inserer_point(liste_a, AJOUT);
	AJOUT.x= (2*max(i1.largeur, i2.largeur))+i2.largeur;
	AJOUT.y = 20;
	inserer_point(liste_a, AJOUT);
	AJOUT.y = i2.hauteur+20;
	inserer_point(liste_a, AJOUT);
}

//------------------------------------------------------------
void afficher_point_fenetre(){		//Affiche les points et les stockent dans une liste chainée
	//Déclaration variables
	static int prem_aff = 0;
	if (!prem_aff){ 		//S'il s'agit du premier affichage des éléments de la fenêtre
		affiche_avant_clic();
		prem_aff++;}
		
	NOEUD *parcours_d;
	NOEUD *parcours_a;
	parcours_d = liste_depart -> head;
	parcours_a = liste_arrivee -> head;
	
	POINT VERIF;
	POINT centre = {LARGEUR_FENETRE/2, HAUTEUR_FENETRE/2};
	POINT aff = wait_clic();
	VERIF.x = aff.x;				//Copie des coordonnées de la zone cliquée
	VERIF.y = aff.y;				//pour vérifier si l'utilisateur a cliqué sur un des boutons
	
	int x1 = 2*max(i1.largeur, i2.largeur);
	short A_QUITTE = 0;
	static int compte_d = 0;
	static int compte_a = 0;
	short copie_d = compte_d;
	short copie_a = compte_a;
	char coordonnees[50];
	sprintf(coordonnees, "Coordonn"eacute"es: %d %d", aff.x, aff.y);
	bool dans_larg = ((i1.largeur+40<=VERIF.x) && (VERIF.x<=i1.largeur+150));
	bool dans_haut = ((HAUTEUR_FENETRE-55<=VERIF.y) && (VERIF.y<=HAUTEUR_FENETRE-20));
	
	//Actions en fonction des coordonnées du clic gauche
	if (((40<=aff.x) && (aff.x<=i1.largeur+40)) && ((20<=aff.y) && (aff.y<=i1.hauteur+20))){ 
		draw_fill_circle(aff, 8, rouge);
		inserer_point(liste_depart, aff);
		compte_d += 1;
		affiche_num_point(aff, compte_d);
		aff_pol_centre(coordonnees, 20, centre, noir);
		}
	else if (((x1<=VERIF.x) && (VERIF.x<=x1+i2.largeur)) && ((20<=VERIF.y) && (VERIF.y<=i2.hauteur+20))){
		draw_fill_circle(aff, 8, rouge);
		inserer_point(liste_arrivee, aff);
		compte_a += 1;
		affiche_num_point(aff, compte_a);
		aff_pol_centre(coordonnees, 20, centre, noir);
		}
	while ((parcours_d != NULL) && (copie_d > 0)){
		aff.x = parcours_d -> value.x;
		aff.y = parcours_d -> value.y;
		draw_fill_circle(aff, 8, rouge);
		affiche_num_point(aff, copie_d--);
		parcours_d = parcours_d -> next;
	}
	while ((parcours_a != NULL) && (copie_a > 0)){
		aff.x = parcours_a -> value.x;
		aff.y = parcours_a -> value.y;
		draw_fill_circle(aff, 8, rouge);
		affiche_num_point(aff, copie_a--);
		parcours_a = parcours_a -> next;
	}
	affiche_all();
	parcours_d = liste_depart -> head;
	if ( ((dans_larg && dans_haut) && (compte_d))){
		if ((compte_d == compte_a) && ( (compte_d) && (compte_a) )){
			ajout_ptbase_depart(liste_depart);
			ajout_ptbase_arrivee(liste_arrivee);
			action_sauver(liste_depart, liste_arrivee);
			A_QUITTE = 1;
			}
	}	
	if (((x1-110<=VERIF.x) && (VERIF.x<=x1)) && ((HAUTEUR_FENETRE-55<=VERIF.y) && (VERIF.y<=HAUTEUR_FENETRE-20))){
		A_QUITTE = 1;
	}
	while (!A_QUITTE){
	fenetre();
	}
}
	
//------------------------------------------------------------
#if DEBUG == 1
int main(){
	affiche_auto_off();
	liste_depart=malloc(sizeof(LISTE_POINTS));
	liste_arrivee=malloc(sizeof(LISTE_POINTS));
	redimensionner_image();
	init_liste_points(liste_depart);
	init_liste_points(liste_arrivee);
	POINT P1 = {40, 20};
	int h1 = i1.hauteur;
	int L1 = i1.largeur;
	int h2 = i2.hauteur;
	int L2 = i2.largeur;
	int pt_depart_im2 = 2*max(L1, L2);
	POINT P2 = {pt_depart_im2, 20};
	init_graphics(3*max(L1, L2)+40, max(h1, h2)+100);
	fenetre();
	wait_escape();
}
#endif
	
	
	
	
	
