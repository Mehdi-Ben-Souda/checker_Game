#pragma once
#include "common.h"

// Enumeration sur les types de fenetres
// Possible

/*-----------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------    FENETRE    -----------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------*/
typedef struct
{
	GtkWidget* ma_fenetre; // pointeur sur une fenetre

	int type;                          // entier indiquant le type du fenetre
	int Largeur;                       // largeur du fenetre
	int Hauteur;                       // hauteur du fenetre
	char Titre[NB_Cara_titre];         // le titre du fenetre
	char chemin_icone[NB_Cara_chemin]; // Icone de la fenetre
	coordonne x_y;                     // Les cordonees de la position
	char couleur[10];                  // Couleur de fond en HEX
	char name[20];                     // le nom de la fenetre par la quelle on va la
	// cibler par le code CSS
	int visible;                       // un entier qui indique si la fanetre sera visible ou non
} Fenetre;                             // structure d'une fenetre
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
Fenetre* Allouer_Fenetre(int type, int largeur,
	int hauteur, char* titre, char* chemin_icone, int x,
	int y, char couleur[8], char name[20], int visible)
{
	Fenetre* mafenetre;

	mafenetre = (Fenetre*)malloc(sizeof(Fenetre));

	// Tester si l'allocation c'est bien derouler
	if (!mafenetre)
	{
		printf("!!!\nErreur dans l'Allocation de la fenetre!!!\n");
		return (Fenetre*)mafenetre;
	}

	mafenetre->type = type;
	mafenetre->Largeur = largeur;
	mafenetre->visible = visible;
	mafenetre->Hauteur = hauteur;
	// Si le titre n'existe pas , on met "vide" dans
	// le paramatre
	if (!titre)
	{
		strcpy(mafenetre->Titre, "vide");
	}
	else
		// Si non on le met on le met dans la structure
		strcpy(mafenetre->Titre, titre);

	// Si le l'icone n'existe pas , on met "vide" dans
	// le paramatre
	if (!chemin_icone)
	{
		strcpy(mafenetre->chemin_icone, "vide");
	}
	else
		// Si non on le met on le chemin dans la structure
		strcpy(mafenetre->chemin_icone, chemin_icone);

	mafenetre->x_y.X = x;
	mafenetre->x_y.Y = y;

	// Si la couleur n'existe pas , on met "vide" dans
	// le paramatre
	if (!couleur)
	{
		strcpy(mafenetre->couleur, "vide");
	}
	else
		// Si non on le met on la couleur dans la structure
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
	GtkWidget* titlebar;
	titlebar = gtk_header_bar_new();

	int static nb_fenetr = 0;

	char buffer[1024];

	GtkCssProvider* provider;
	GdkDisplay* display;
	GdkScreen* screen;

	// Test si la structure existe
	if (!mafenetre)
	{
		printf("\nFenetre n'existe pas !!!");
		exit(0);
	}

	// Creation de la fenetre
	mafenetre->ma_fenetre = gtk_window_new(mafenetre->type);

	// ajustement de la taille de la fenetre
	if (mafenetre->Hauteur && mafenetre->Largeur)
		// Seulement si la longeur et la hauteur existe tous les deux
		gtk_window_set_default_size(GTK_WINDOW(mafenetre->ma_fenetre),
			mafenetre->Largeur, mafenetre->Hauteur);

	// Mettre un titre a la fenetre
	if (strcmp("vide", mafenetre->Titre))
		// Seulement si le titre n'est pas NULL
	{
		gtk_window_set_icon_from_file(GTK_WINDOW(mafenetre->ma_fenetre), mafenetre->chemin_icone, NULL);
		gtk_header_bar_set_title(GTK_HEADER_BAR(titlebar), mafenetre->Titre);
		gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(titlebar), TRUE);
		gtk_window_set_titlebar(GTK_WINDOW(mafenetre->ma_fenetre), titlebar);
	}
	// Mettre une icone
	if (strcmp("vide", mafenetre->chemin_icone))
		// Seulement si le champs icone n'est pas NULL
	{ //(cad on veut ajouter une icone)
		/*
			Creation de GdkPixbuf avec la fct
				gdk_pixbuf_new_from_file

			Image est une chaine de caractere contenant
				le nom du fichier
		*/
		image* fenetre_icon = creer_image(mafenetre->chemin_icone, 40, 40, 0, 0);
		gtk_header_bar_pack_start(GTK_HEADER_BAR(titlebar), fenetre_icon->img);
		/*
			pour utiliser gtk_window_set_icon on lui passe GdkPixbuf

		gtk_window_set_icon(GTK_WINDOW(mafenetre->ma_fenetre),
			icone1);*/
	}

	// Positionner la fenetre

	if (mafenetre->x_y.X || mafenetre->x_y.Y)
	{
		// deplacer selon les cordonee
		gtk_window_move(GTK_WINDOW(mafenetre->ma_fenetre),
			mafenetre->x_y.X, mafenetre->x_y.Y);
	}
	else
	{
		gtk_window_set_position(GTK_WINDOW(mafenetre->ma_fenetre), GTK_WIN_POS_CENTER);
	}

	gtk_widget_set_name(mafenetre->ma_fenetre, mafenetre->name);

	if (strcmp("vide", mafenetre->couleur)) // Si la couleur existe
	{
		/*_______________Changement couleur background____________*/
		/*provider = gtk_css_provider_new();
		display = gdk_display_get_default();
		screen = gdk_display_get_default_screen(display);

		gtk_style_context_add_provider_for_screen(screen,
			GTK_STYLE_PROVIDER(provider),
			GTK_STYLE_PROVIDER_PRIORITY_USER);

		printf("alllo______________________________");
		snprintf(buffer, sizeof(buffer),
			"#%s { background-color:%s;}",mafenetre->name,
				mafenetre->couleur);
			//Ajout du code CSS
		gtk_css_provider_load_from_data(provider, buffer, -1, NULL);*/
		add_bgcolor(mafenetre->ma_fenetre, mafenetre->couleur, 1);
	}

	return ((Fenetre*)mafenetre);
}
/*____________________________________________________________*/

/*
	Nom Fonction : Ajouter_fenetre

	Entree :Pointeur sur un element de type Fenetre
			Pointeur sur un element fils

	Sortie :Pointeur sur un element de type Fenetre

	Description :la folction associe un widget a la fenetre qui
				Sont tous les deux passe en parametres
*/
Fenetre* Ajouter_fenetre(Fenetre* mafenetre, GtkWidget* element)
{
	if (mafenetre->ma_fenetre)
	{
		// Assoiciation du widget a la fenetre
		gtk_container_add(GTK_CONTAINER(mafenetre->ma_fenetre),
			element);
	}
	return (Fenetre*)mafenetre;
}

/*____________________________________________________________*/

void afficher_fenetre(GtkWidget* Fen)
{
	if (Fen)
	{
		printf("\nune fenetre sera afficher en 1 2 3 ..\n");
		gtk_widget_show_all(Fen);
	}
	else
	{
		printf("\nparametre errone\n");
	}
}

void fenetre_destroy(GtkWidget* fen)
{
	gtk_widget_destroy(fen);
}
void signal_fenetre_destroy(GtkWidget* button, gpointer fen)
{
	GtkWidget* window = GTK_WIDGET(fen);
	gtk_widget_destroy(window);
}
