#include "gtk/gtk.h"

#define NB_Cara_titre 50
#define NB_Cara_chemin 150

typedef struct
{
	int x;//Postition sur l'axe des abscices
	int y;//Postition sur l'axe des ordonnées
}Coordonees;


/*-----------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------    FENETRE    -----------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------*/
typedef struct
{
	GtkWidget* ma_fenetre;//pointeur sur une fenetre

	GtkWindowType type;//entier indiquant le type du fenetre
	int Largeur;//largeur du fenetre
	int Hauteur;//hauteur du fenetre
	char Titre[NB_Cara_titre];//le titre du fenetre
	char chemin_icone[NB_Cara_chemin];//Icone de la fenetre
	Coordonees x_y;
	int position;//postion dans la fenetre
	char couleur[8];//Couleur de fond en HEX

}Fenetre;//structure d'une fenetre

Fenetre* Allouer_Fenetre(GtkWindowType type, int largeur, int hauteur, char* titre,
	char* chemin_icone, int x, int y, int position, char couleur[8])
{
	Fenetre* mafenetre;

	mafenetre = (Fenetre*)malloc(sizeof(Fenetre));

	if (!mafenetre)
	{
		printf("!!!\nErreur dans l'Allocation de la fenetre!!!\n");
		return (Fenetre*)mafenetre;
	}
	mafenetre->type = type;
	mafenetre->Largeur = largeur;
	mafenetre->Hauteur = hauteur;
	if (!titre) {
		strcpy(mafenetre->Titre, "vide");
	}
	else
		strcpy(mafenetre->Titre, titre);
	if (!chemin_icone)
	{
		strcpy(mafenetre->chemin_icone, "vide");
	}
	else
		strcpy(mafenetre->chemin_icone, chemin_icone);

	mafenetre->x_y.x = x;
	mafenetre->x_y.y = y;
	mafenetre->position = position;
	if (!couleur)
	{
		strcpy(mafenetre->couleur, "vide");
	}
	else
		strcpy(mafenetre->couleur, couleur);






	return ((Fenetre*)mafenetre);
}

//Fonction d'ajouter de css style pour les widgets / sous-widgets
void gtk_add_css(GtkWidget* Widget, const char* CSSCode)
{
	GtkCssProvider* Provider = gtk_css_provider_new();
	gtk_css_provider_load_from_data(Provider, CSSCode, -1, NULL);

	GtkStyleContext* Context = gtk_widget_get_style_context(Widget);
	gtk_style_context_add_provider(Context, GTK_STYLE_PROVIDER(Provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

	g_object_unref(Provider);
}

Fenetre* Creer_Fenetre(Fenetre* mafenetre)
{
	GdkPixbuf* icone1;
	GdkColor lacouleur;
	GdkRGBA lacouleur2;

	char buffer[1024];

	GtkCssProvider* provider;
	GdkDisplay* display;
	GdkScreen* screen;

	if (!mafenetre)
	{
		printf("\nFenetre n'existe pas !!!");
		exit(0);
	}

	//Creation de la fenetre
	mafenetre->ma_fenetre = gtk_window_new(mafenetre->type);

	//ajustement de la taille de la fenetre
	if (mafenetre->Hauteur && mafenetre->Largeur)
		//Seulement si la longeur et la hauteur existe tous les deux
		gtk_window_set_default_size(GTK_WINDOW(mafenetre->ma_fenetre),
			mafenetre->Largeur, mafenetre->Hauteur);
	//Mettre un titre a la fenetre
	if (strcmp("vide", mafenetre->Titre))//Seulement si le titre n'est pas NULL    
		gtk_window_set_title(GTK_WINDOW(mafenetre->ma_fenetre), mafenetre->Titre);


	//Mettre une icone 
	if (strcmp("vide", mafenetre->chemin_icone))//Seulement si le champs icone n'est pas NULL
	{       //(cad on veut ajouter une icone)
		/*_______________Icone de fenetre________________*/
		/*
			Creation de GdkPixbuf avec la fct gdk_pixbuf_new_from_file
		*/
		//Image est une chaine de caractere contenant le nom du fichier
		icone1 = gdk_pixbuf_new_from_file(mafenetre->chemin_icone, NULL);
		/*
			pour utiliser gtk_window_set_icon on lui passe GdkPixbuf
		*/
		gtk_window_set_icon(GTK_WINDOW(mafenetre->ma_fenetre), icone1);
	}

	//Positionner la fenetre

	if (mafenetre->x_y.x && mafenetre->x_y.y)
	{
		//deplacer selon les cordonée
		gtk_window_move(GTK_WINDOW(mafenetre->ma_fenetre),
			mafenetre->x_y.x, mafenetre->x_y.y);


	}

	//___________________TODO: positionement selon les places dans la fenetre
/*else
	if (mafenetre->position)
	{

	}
	else {

	}*/

	if (strcmp("vide", mafenetre->couleur))//Si la couleur existe
	{
		/*_______________Changement couleur background____________*/
		//gdk_color_parse(mafenetre->couleur, &lacouleur);//couleur est une chaine de cara de hex de la couleur
		//gdk_rgba_parse(&lacouleur2, mafenetre->couleur);
		//gtk_widget_modify_bg(mafenetre->ma_fenetre, gtk_state_normal, &lacouleur);
		//gtk_widget_override_background_color(gtk_widget(mafenetre->ma_fenetre),gtk_state_flag_normal,&lacouleur2);

		provider = gtk_css_provider_new();
		display = gdk_display_get_default();
		screen = gdk_display_get_default_screen(display);

		gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

		//    //ceci est une fonction qui va me permettre de creer une chaine de cara avec
		//    //la variable couleur qu'on a deja
		snprintf(buffer, sizeof(buffer), "window { background-color:%s;}", mafenetre->couleur);

		gtk_css_provider_load_from_data(provider, buffer, -1, NULL);

		//gtk_widget_set_name(GTK_WIDGET(mafenetre->ma_fenetre), "karrrrr_el_banie");
		//gtk_add_css(GTK_WIDGET(mafenetre->ma_fenetre), "#ffuuu {background-color:#FF00FF}");

	}

	gtk_container_set_border_width(GTK_CONTAINER(mafenetre->ma_fenetre), 50);


	return ((Fenetre*)mafenetre);
}


