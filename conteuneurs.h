#pragma once
#include "common.h"


/*-----------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------      Box	    -----------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------*/

typedef enum
{
	BoxPositionInsertion_Debut,//0 ---> pour l'insertion au debut
	BoxPositionInsertion_Fin//1 ---> pour l'insertion a la fin
}BoxPositionInsertion;

typedef enum
{
	ORIENTATION_HORIZONTAL,
	ORIENTATION_VERTICAL
}Orientation;

typedef struct
{
	GtkWidget* mon_box;//le pointeur sur le conteneur box
	/*
		Orientation: 
		ORIENTATION_HORIZONTAL
		ORIENTATION_VERTICAL
	*/
	Orientation orientation;
	int espacement;//l'espacement entre les elements

}Box;//Struture du widget BOX

/*
	Nom Fonction : Allouer_Box

	Entree :_enumeration pour determiner l'orientation
				(soit horizontal , soit vertical)
			_un entier servant a determiner l'espacement
				entre les elements du box

	Sortie :Pointeur sur la structure cree

	Description :On fait une allocation d'une structure de
					Type Box avec les paramatres passes
*/
Box* Allouer_Box(Orientation orientation, int espacement)
{
	Box* boite = (Box*)malloc(sizeof(Box));

	if (!boite)
	{
		printf("!!!\nErreur dans l'Allocation du Box!!!\n");
		return (Box*)boite;
	}
	boite->mon_box = NULL;
	boite->orientation = orientation;
	boite->espacement = espacement;

	return (Box*)boite;
}
/*
	Nom Fonction : Creer_Box

	Entree :_pointeur sur une structure
			_pointeur sur le widget parent au quel 
				on va l'ajouter

	Sortie :VOID

	Description :On cree le conteneur BOX avec les paramatres 
		passee dans la structure et on l'assosie a un conteneur
		parent
*/
void Creer_Box(Box* boite, GtkWidget* parent)
{

	/*
		Ici on va creer un contenuer de type box , qui lui
		va nous permettre de mettre plusieurs widget

		Parametres:
			1) l'orientation :
				_GTK_ORIENTATION_HORIZONTAL :pour aligner 
				les elements du conteneur Horizontallement
				_GTK_ORIENTATION_VERTICAL : pour aligner 
				les elements verticallement
			2) spacing: (entier/ int)
				le nombre de pixels à placer par défaut entre
				les enfants.

	*/
	boite->mon_box = gtk_box_new(boite->orientation, 
									boite->espacement);

	if (parent)
	{
		/*
		On met le conteuneur box a l'interieur de l'element
		parent 
		*/
		gtk_container_add(GTK_CONTAINER(parent), 
							boite->mon_box);
	}
}
/*____________________________________________________________*/

/*
	Nom Fonction : Ajouter_Box

	Entree :_pointeur sur une structure
			_pointeur sur le widget fils qu'on
				va ajouter
			_la position d'insertion (debut ou fin)
			_Un booleen indiquant si le widget doit être etire
				pour remplir l'espace disponible dans la boîte
			_ Un booléen indiquant si le widget doit être rempli
				pour occuper tout l'espace disponible dans 
				la direction de l'axe principal de la boîte
			_La quantité d'espace à ajouter autour du widget, 
				en pixels.

	Sortie :VOID

	Description :On ajoute un widget a un conteneur parent de type
		BOX
*/
void Ajouter_Box(Box* boite, GtkWidget* fils, 
			BoxPositionInsertion position, gboolean expension, 
					gboolean remplissage, int padding)
{
	if (fils)
	{
		if (position == BoxPositionInsertion_Debut)
		{
			/*
				On ajoute les bouttons aux conteneur
				La methode pack_start permet d'ajouter au 
				debut des elements

				Les Parametres:
				3) expand : TRUE ---> Si il y a un espace 
				supplementaire alloué ,
				les enfants de box vont le prendre de maniere
				egales

				4) fill

				5) pading : l'espace exterieur
			*/
			gtk_box_pack_start(GTK_BOX(boite->mon_box), fils, 
				expension, remplissage, padding);
		}
		else if (position == BoxPositionInsertion_Fin)
		{
			gtk_box_pack_end(GTK_BOX(boite->mon_box), fils, 
				expension, remplissage, padding);
		}
	}
}


/*-----------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------	  fixed     -----------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------*/
typedef struct 
{
	GtkWidget* mon_fixed;//le pointeur sur le conteneur fixed
	char name[20];//Le nom du conteneur

}Fixed;


/*
	Nom Fonction : Allouer_fixed

	Entree :une chaine de caractere qui identifie le 
				conteneur que nous allons allouer

	Sortie :Pointeur sur la structure cree

	Description :On fait une allocation d'une structure de
					Type Fixed
*/

Fixed* Allouer_fixed(char name[20])
{
	Fixed* ptr;

	//Allocation de la structure
	ptr = (Fixed*)malloc(sizeof(Fixed));
	if (!ptr)
	{
		printf("!!!\nErreur dans l'Allocation du Fixed!!!\n");
		
		return (Fixed*)ptr;
	}

	//Creation du fixed
	ptr->mon_fixed = gtk_fixed_new();

	//Ajout du nom du conteneur servant au ciblage CSS
	if (!name)
	{
		printf("\n\nErreur vous avez oubilier le nom"
			"du fixed\n\n");
		exit(12);
	}
	else
		strcpy(ptr->name, name);

	return(Fixed*)ptr;
}
/*____________________________________________________________*/


/*
	Nom Fonction : Ajouter_Fixed

	Entree :_pointeur sur le fils que nous desirons ajouter
				au fixed
			_entiers x et y qui sont la position selons les
				abssices et les ordonee dans le conteneur
			_pointuer sur le conteneur 

	Sortie :_pointeur sur une srtructure de type Fixed

	Description :
			_On ajoute l'element qu'on veux ajouter 
				au conteneur fixed 
			
*/

Fixed* Ajouter_Fixed(GtkWidget* fils,int x,int y, Fixed * lefixed)
{
	//Si les elements existent 
	if (fils && lefixed)
	{
		//On ajoute le widget au fixed
		gtk_fixed_put(GTK_FIXED(lefixed->mon_fixed), fils,x, y);
	}
	return (Fixed*)lefixed;
}

/*____________________________________________________________*/


/*
	Nom Fonction : Deplacer_Fixed

	Entree :_pointeur sur le fils que nous desirons deplacer
				a l'interieur du fixed
			_entiers x et y qui sont la position selons les
				abssices et les ordonee dans le conteneur
			_pointuer sur le conteneur

	Sortie :_pointeur sur une srtructure de type Fixed

	Description :
			_On change la place du widget dans le fixed

*/
Fixed* Deplacer_Fixed(GtkWidget* fils, int new_x, int new_y, 
		Fixed* lefixed)
{
	//Si les elements existent 
	if (fils && lefixed)
	{
		//On deplace le widget dans le conteneur
		gtk_fixed_move(GTK_FIXED(lefixed->mon_fixed), 
			GTK_WIDGET(fils), new_x, new_y);
	}
	return (Fixed*)lefixed;
}
/*____________________________________________________________*/


