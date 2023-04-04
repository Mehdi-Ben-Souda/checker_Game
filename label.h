#pragma once
#include "common.h"
typedef struct {
	GtkWidget* leLabel;
	char text[250];//Le texte que continet le label
	char name[NB_Cara_titre];
	coordonne X_Y;//Ses cordonnees
}Label;

Label* Init_label(char text[250], char name[NB_Cara_titre], int X, int Y)
{
	Label* ptr = (Label*)malloc(sizeof(Label));

	if (!ptr)
	{
		printf("Erreur lors de l'Allocattion de label \n\n");
		return (Label*)ptr;
	}

	//Copie du texte
	strcpy(ptr->text,text);
	//Copie du nom
	strcpy(ptr->name, name);

	//Copie des cordonée

	ptr->X_Y.X = X;
	ptr->X_Y.Y = Y;

	//Creation du widget label
	ptr->leLabel= gtk_label_new(name);
	return (Label*)ptr;
}

