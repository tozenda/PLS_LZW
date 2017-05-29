/**
* @file main.c
* @brief Fichier contenant la plante du programme.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "compression.h"
#include "decompression.h"
#include "dictionnaire.h"

int *tab_zip;
int taille_zip;

void dispError()
{
	printf("Syntaxe : \n");
	printf("\t./lzw -c fichier_a_compresser\n");
	printf("\t./lzw -d fichier_a_decompresser\n");
}

int main(int argc, char *argv[]){

	int tmp;
	FILE *f = NULL;
	int i = 0, tailleInput;
	char c;
	char *input;
	int *inputZip;

	if(argc != 3){
		dispError();
		return 1;
	}

	if(argv[1][0] == '-')
	{
		switch(argv[1][1])
		{
			case 'c':

				f = fopen(argv[2],"r");
				if (f == NULL){
					printf("Erreur lors de l'ouverture du fichier %s\n",argv[2]);
					return 1;
				}

				/* Lecture du fichier */
				while (!feof(f)) {
					c = fgetc(f);
					if(c != -1){
						i++;
					}
				}

				rewind(f);

				tailleInput = i;
				input = malloc(tailleInput*sizeof(char));

				i = 0;
				while (!feof(f)) {
					c = fgetc(f);
					if(c != -1){
						input[i] = c;
						i++;
					}
				}

				fclose(f);

				 /* Appel à codage */

				int *tab=malloc(MAX*sizeof(int));
				int *ind=malloc(sizeof(int));
				codage(input,tailleInput,tab,ind);

				//printf("Codes que donne codage :\n");
				tab_zip = malloc((*ind)*sizeof(int));
				taille_zip = *ind;
				for(int i=0;i<*ind;i++){
					printf("%d\n",tab[i]);
				}
				//printf("------------------------\n");

				//printf("Codes que donne codage :\n");
				//for(int i=0;i<*ind;i++){
					//printf("%d\n",tab_zip[i]);
				//}
				//printf("\n");

				 /*printf("DICTIONNAIRE APRES CODAGE :\n");
				 printf("-------------------------------\n");
				 dico_print_small();
				 printf("-------------------------------\n");*/


				break;

			case 'd':

				/* Lecture du fichier à decompresser */
				 f = fopen(argv[2], "r");
				 if (f == NULL){
				 	printf("Erreur lors de l'ouverture du fichier %s\n",argv[2]);
				 	return 1;
				 }

				 while (!feof(f)) {
				  fscanf(f,"%d",&tmp);
				 	if(tmp != -1){
				 		i++;
				 	}
				 }
				 rewind(f);

				 tailleInput = i;
				 inputZip = malloc(tailleInput*sizeof(int));

				 i = 0;
				 while (!feof(f)) {
				 	fscanf(f,"%d",&tmp);
				 	if(tmp != -1){
				 		inputZip[i] = tmp;
				 		i++;
				 	}
				 }

				 fclose(f);

				/* Appel à décompression */

				decompression(inputZip,tailleInput);

				 /*printf("DICTIONNAIRE :\n");
				 printf("-------------------------------\n");
				 dico_print_small();
				 printf("-------------------------------\n");*/

				break;

			default:
				dispError();
				return 1;
				break;
		}
	}else dispError();

	return 0;
}
