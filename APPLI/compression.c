/**
* @file compression.c
* @brief Fichier contenant l'algorithme de compression.
* @author CHARLOT Servan
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "compression.h"
#include "dictionnaire.h"

/*
FIXME
	Peut etre mettre le type de w en int8 pour coller avec dictionnaire.
	out[i+1] = a[0];
	Revoir avec Thomas sequence vers code pour le passage de a.
*/

/**
* @fn void concat(char *w, int tailleW, char *a,char *out)
* @brief Fonction permettant de concatener une chaine de caractère et un caractère. Ce dernier doit être contenu dans un tableau à 1 case.
* @param[in] w Tableau de caractère reprsésantant le prefixe à concatener.
* @param[in] tailleW Entier contenant la taille du tableau w.
* @param[in] a Tableau de caractère de taille 1 contenant le caractère à concatener avec w.
* @param[in, out] out Tableau de taille tailleW + 1 contenant la concaténation de w et a.
*/
void concat(char *w, int tailleW, char *a,char *out)
{
	int i;
	for(i = 0; i < tailleW; i++)
	{
		out[i] = w[i];
	}
	out[i] = a[0];
}

/**
* @fn void codage(char *input, int taille, char *output)
* @brief Algorithme de compression LZW.
* @param[in] input Tableau de caractère contenant la totalité de l'information contenue dans le fichier à compresser.
* @param[in] taille Entier contant la taille du tableau input.
* @param[in, out] output Tableau de caractère contenant la compression des données.
*/
void codage(char *input, int taille, char *output)
{
	//char output[taille] à déclarer dans main TODO
 	//elem dico[MAX] -> déclaré dans dictionnaire.h
	char *w;
	char *wa;
	char a[1];
	int i, tailleW = 1, k = 0;

	initialiser();

	w = malloc(tailleW*sizeof(char));
	w[0] = input[0];

	for(i = 1 ; i < taille ; i++)
	{
		a[0] = input[i];

		free(wa);
		wa = malloc((tailleW+1)*sizeof(char));
		concat(w,tailleW,a,wa);	

		if(SequenceVersCode(wa,tailleW+1) != -1)
		{
			tailleW++;
			free(wa);
			w = malloc(tailleW*sizeof(char));
			for(int j = 0; j < tailleW; j++) w[j] = wa[j];
		}
		else
		{
			output[k] = SequenceVersCode(w,tailleW);
			Inserer(SequenceVersCode(w,tailleW),SequenceVersCode(a,1));
			tailleW = 1;
			free(w);
			w = malloc(tailleW*sizeof(char));
			w[0] = a[0];
			k++;
		}

	}

	output[k] = SequenceVersCode(w,tailleW);

}