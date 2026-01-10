/*Nom: TRENDEL
 * Prénom: Eliot
 * Groupe: TD1
 */

#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "errno.h"
#define DEBUG 0
#define COMP "convert "


//1.4 projet code avec conversion format

void exec_commande(char *prog){
	char commande[100];
	char *nom = malloc(sizeof(char)*strlen(prog));	
	char *extension = malloc(sizeof(char)*10);
	register int cpt;
	cpt = 0;
	while (prog[cpt] != '.'){
		cpt++;
	}
	printf("Tapez le format auquel vous voulez convertir l'image: ");
	scanf("%s", extension);
	strncpy(nom, prog, cpt);
	
	strcpy(commande, COMP);
	strcat(commande, prog);
	strcat(commande, " ");
	strcat(commande, "../output_pic/");
	strcat(commande, nom);
	strcat(commande, extension);
	if (!system){
		fprintf(stderr, "%s", strerror(EBUSY));
		exit(EXIT_FAILURE);
	}
	#if DEBUG == 1
	printf("La commande générée est: %s\n", commande);
	#endif
	system(commande);
}

int main(int argc, char **argv){
	exec_commande(argv[1]);
	return EXIT_SUCCESS;
}
	
	
	
