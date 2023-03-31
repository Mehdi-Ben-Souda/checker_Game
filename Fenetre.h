#pragma once
#include "common.h"


/*typedef struct
{
	int X;//Postition sur l'axe des abscices
	int Y;//Postition sur l'axe des ordonnées
}coordonees;*/

	//Enumeration sur les types de fenetres
	//Possible
typedef enum
{
	WINDOW_TOPLEVEL,
	WINDOW_POPUP

}WindowType;


/*-----------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------    FENETRE    -----------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------*/
typedef struct
{
	GtkWidget* ma_fenetre;//pointeur sur une fenetre

	WindowType type;//entier indiquant le type du fenetre
	int Largeur;//largeur du fenetre
	int Hauteur;//hauteur du fenetre
	char Titre[NB_Cara_titre];//le titre du fenetre
	char chemin_icone[NB_Cara_chemin];//Icone de la fenetre
	coordonne x_y;//Les cordonees de la position 
	char couleur[8];//Couleur de fond en HEX
	char name[20];//le nom de la fenetre par la quelle on va la
			//cibler par le code CSS

}Fenetre;//structure d'une fenetre
/*____________________________________________________________*/

/*
	Nom Fonction : Allouer_Fenetre

	Entree :
			_Enumeration: type de la fenetre 
				(WINDOW_TOPLEVEL et WINDOW_POPUP)
			_la largeur de la fenetre (entier)
			_la haiteur de la fenetre (entier)
			_le titre de la fenetre (chaine de caractere)
			_chemin de l'icone (chaine de caractere)
			_la position selon l'axe des absicces sur l'ecrant
			_la position selon l'axe des ordonee sur l'ecrant
			_la couleur de fond (chaine de caractere)

	Sortie :_Pointeur sur une instance de type Fenetre

	Description : La focntion prends en paramatres les caracteristiques 
		de la fenetre qu'on desire creer ,instancie un element de type
		Fenetre et l'initialise aux paramatres qu'on a passee
*/
Fenetre* Allouer_Fenetre(WindowType type, int largeur, 
		int hauteur, char* titre,char* chemin_icone, int x,
			int y, int position, char couleur[8],char name[20])
{
	Fenetre* mafenetre;

	mafenetre = (Fenetre*)malloc(sizeof(Fenetre));

		//Tester si l'allocation c'est bien derouler
	if (!mafenetre)
	{
		printf("!!!\nErreur dans l'Allocation de la fenetre!!!\n");
		return (Fenetre*)mafenetre;
	}

	mafenetre->type = type;
	mafenetre->Largeur = largeur;
	mafenetre->Hauteur = hauteur;
		//Si le titre n'existe pas , on met "vide" dans 
			//le paramatre
	if (!titre) {
		strcpy(mafenetre->Titre, "vide");
	}
	else
		//Si non on le met on le met dans la structure
		strcpy(mafenetre->Titre, titre);

		//Si le l'icone n'existe pas , on met "vide" dans 
			//le paramatre
	if (!chemin_icone)
	{
		strcpy(mafenetre->chemin_icone, "vide");
	}
	else
		//Si non on le met on le chemin dans la structure
		strcpy(mafenetre->chemin_icone, chemin_icone);

	mafenetre->x_y.X = x;
	mafenetre->x_y.Y = y;

		//Si la couleur n'existe pas , on met "vide" dans 
			//le paramatre
	if (!couleur)
	{
		strcpy(mafenetre->couleur, "vide");
	}
	else
		//Si non on le met on la couleur dans la structure
		strcpy(mafenetre->couleur, couleur);
	

	if (!name)
	{
		printf("\n\nErreur vous avez oubilier le nom"
			"de la fenetre\n\n");
		exit(12);
	}
	else
		strcpy(mafenetre->name, name);

	return ((Fenetre*)mafenetre);
}
/*____________________________________________________________*/


/*
	Nom Fonction : Creer_Fenetre

	Entree :Pointeur sur un element de type Fenetre

	Sortie :Pointeur sur un element de type Fenetre

	Description :Cree un GtkWidget qui sera la fenetre , 
		qu'on desire creer et lui attribut les proprietes 
		que nous avons dans la structure 
*/

Fenetre* Creer_Fenetre(Fenetre* mafenetre)
{
	GdkPixbuf* icone1;
	int static nb_fenetr=0;

	char buffer[1024];

	GtkCssProvider* provider;
	GdkDisplay* display;
	GdkScreen* screen;

		//Test si la structure existe
	if (!mafenetre)
	{
		printf("\nFenetre n'existe pas !!!");
		exit(0);
	}

		//Creation de la fenetre
	mafenetre->ma_fenetre = gtk_window_new(
			(GtkWindowType)mafenetre->type);

		//ajustement de la taille de la fenetre
	if (mafenetre->Hauteur && mafenetre->Largeur)
			//Seulement si la longeur et la hauteur existe tous les deux
		gtk_window_set_default_size(GTK_WINDOW(mafenetre->ma_fenetre),
			mafenetre->Largeur, mafenetre->Hauteur);

		//Mettre un titre a la fenetre
	if (strcmp("vide", mafenetre->Titre))
		//Seulement si le titre n'est pas NULL    
		gtk_window_set_title(GTK_WINDOW(mafenetre->ma_fenetre),
			mafenetre->Titre);


		//Mettre une icone 
	if (strcmp("vide", mafenetre->chemin_icone))
		//Seulement si le champs icone n'est pas NULL
	{       //(cad on veut ajouter une icone)
		/*
			Creation de GdkPixbuf avec la fct 
				gdk_pixbuf_new_from_file
		
			Image est une chaine de caractere contenant 
				le nom du fichier
		*/
		icone1 = gdk_pixbuf_new_from_file(
				mafenetre->chemin_icone, NULL);
		/*
			pour utiliser gtk_window_set_icon on lui passe GdkPixbuf
		*/
		gtk_window_set_icon(GTK_WINDOW(mafenetre->ma_fenetre),
			icone1);
	}

	//Positionner la fenetre

	if (mafenetre->x_y.X || mafenetre->x_y.Y)
	{
		//deplacer selon les cordonee
	gtk_window_move(GTK_WINDOW(mafenetre->ma_fenetre),
		mafenetre->x_y.X, mafenetre->x_y.Y);
	}
	

	gtk_widget_set_name(mafenetre->ma_fenetre, mafenetre->name);


	if (strcmp("vide", mafenetre->couleur))//Si la couleur existe
	{
		/*_______________Changement couleur background____________*/
		provider = gtk_css_provider_new();
		display = gdk_display_get_default();
		screen = gdk_display_get_default_screen(display);

		gtk_style_context_add_provider_for_screen(screen,
			GTK_STYLE_PROVIDER(provider), 
			GTK_STYLE_PROVIDER_PRIORITY_USER);


		snprintf(buffer, sizeof(buffer), 
			"#%s { background-color:%s;}",mafenetre->name, 
				mafenetre->couleur);
			//Ajout du code CSS
		gtk_css_provider_load_from_data(provider, buffer, -1, NULL);
		
	}
/*____________________________________________________________*/

	return ((Fenetre*)mafenetre);
}

Fenetre* Ajouter_fenetre(Fenetre* mafenetre, GtkWidget* element)
{
	if (mafenetre->ma_fenetre)
	{
		gtk_container_add(GTK_CONTAINER(mafenetre->ma_fenetre), element);
	}
	return (Fenetre*)mafenetre;
}


