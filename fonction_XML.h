#include <libxml2/libxml/parser.h>
#include "Fenetre.h"
#include "struct_med.h"
#include "Menu.h"
#include "ToolBar.h"
#include "conteuneurs.h"
#include "InfoToolBar.h"

/*
 * Fonction qui permet de identifier la nature de balise
 * entrées : un element de type xmlNodePtr ,c'est la balise a identifier
 * sorties : un entier selon la nature ce la balise entrer en parametre
 */
int nature_balise(xmlNodePtr balise)
{
	//tester si la balise est une fenetre
	if ((!xmlStrcmp(balise->name, (const xmlChar*)"Fenetre")))return((int)1);
	//tester si la balise est un fixed
	if ((!xmlStrcmp(balise->name, (const xmlChar*)"Fixed")))return((int)2);
	//tester si la balise est un bouton
	if ((!xmlStrcmp(balise->name, (const xmlChar*)"Button")))return((int)3);
	//tester si la balise est un Menu
	if ((!xmlStrcmp(balise->name, (const xmlChar*)"Menu")))return((int)4);
	//tester si la balise est un CelluleMenu
	if ((!xmlStrcmp(balise->name, (const xmlChar*)"CelluleMenu")))return((int)5);
	//tester si la balise est un CelluleItem
	if ((!xmlStrcmp(balise->name, (const xmlChar*)"CelluleItem")))return((int)6); 
	//tester si la balise est un Toolbar
	if ((!xmlStrcmp(balise->name, (const xmlChar*)"Toolbar")))return((int)7);
	//tester si la balise est un CelluleToolItem
	if ((!xmlStrcmp(balise->name, (const xmlChar*)"CelluleToolItem")))return((int)8);
	//tester si la balise est un Box
	if ((!xmlStrcmp(balise->name, (const xmlChar*)"Box")))return((int)9);
	return((int)-1);
}


void ajoueter_a_conteuneur(xmlNodePtr cur_parent, GtkWidget* parent, GtkWidget *fils,int X, int Y)
{
	int nat;
	nat = nature_balise(cur_parent);
	//tester la nature de la balise parent
	if (nat == 2)// si le parent est fixed
	{
		Ajouter_Fixed(fils, X, Y, parent);
		printf("\nbutton was added to the container Fixed\n");
	}
	else {
		if (nat == 9)
		{

		}
	}

}
CelluleItem* creer_CelluleMenu_fils(xmlDocPtr doc, xmlNodePtr cur, GtkAccelGroup* accel_group)
{
	CelluleItem* CelluleItemListe = NULL;
	int nat;
	printf("\n %s \n ", cur->name);
	//pointer sur le premier fils de la balise cur
	cur = cur->xmlChildrenNode;
	printf("\n %s \n ", cur->name);
	// boucler jusqu'il y a pas encore une autre balise (frere)
	while (cur != NULL)
	{
		nat = nature_balise(cur);
		if (nat == 6) {
			CelluleItemListe = Inserer_CelluleItem(CelluleItemListe,
				(char*)xmlGetProp(cur, "label"),
				(char*)xmlGetProp(cur, "icon"),
				(char*)xmlGetProp(cur, "name"),
				(char*)xmlGetProp(cur, "accel_key"),
				accel_group,NULL);
			printf("\n CelluleItem inserer\n");
		}
		cur = cur->next;
	}

	return((CelluleItem*)CelluleItemListe);

}

CelluleMenu* creer_Menu_fils(xmlDocPtr doc, xmlNodePtr cur, GtkAccelGroup* accel_group)
{
	CelluleMenu* CelluleMenuListe = NULL;
	CelluleItem* CelluleItemListe = NULL;
	int nat;
	printf("\n %s \n ", cur->name);
	//pointer sur le premier fils de la balise cur
	cur = cur->xmlChildrenNode;
	printf("\n %s \n ", cur->name);
	// boucler jusqu'il y a pas encore une autre balise (frere)
	while (cur != NULL) 
	{
		nat = nature_balise(cur);
		if(nat == 5){
		printf("\n  %s \n ", cur->name);
		CelluleItemListe = creer_CelluleMenu_fils(doc, cur, accel_group);
		CelluleMenuListe = Inserer_CeluleMenu(CelluleMenuListe, CelluleItemListe,
											(char*)xmlGetProp(cur, "label"),
											(char*)xmlGetProp(cur, "name"));
		printf("\n cellule menu inserer\n");
		}
		cur = cur->next;
	}

	return((CelluleMenu*)CelluleMenuListe);

}

/*____________________________________________________________________________

 * Fonction qui permet de creer tous les fils d'une balise
 * entrées : -> Le document ou il y a le code xml
 *			 -> la balise pere en format xmlNodePtr
 *			 -> la balise pere en format GtkWidget
 * sorties : void
 */
void
creer_fils(xmlDocPtr doc, xmlNodePtr cur, GtkWidget* Gtk_parent) {
	int nat,n=0;
	Fixed* fixed;
	Boutton *Btn;
	CelluleMenu * celluleMenu =NULL;
	Menu* menu;
	CelluleMenu* CelluleMenuListe = NULL;
	GtkAccelGroup* accel_group;
	ToolBar* toolbar;
	CelluleToolItem* celluleToolItem;
	Box* boite;
	//pointer sur le premier fils de la balise cur
	cur = cur->xmlChildrenNode;
	// boucler jusqu'il y a pas encore une autre balise (frere)
	while (cur != NULL) {
		//identifier la nature de la balise
		nat = nature_balise(cur);
		switch (nat)
		{
		case 2:// si la balise est fixed
			// la creation d'un fixed
			fixed = Allouer_fixed((char*)xmlGetProp(cur, "name"));
			printf("\nfixed created\n");
			//ajouter  le fixed a la balise parent
			gtk_container_add(GTK_CONTAINER(Gtk_parent), fixed->mon_fixed);
			printf("\nfixed added to the window\n");
			//creation de tous les fils de ce fixed
			creer_fils(doc, cur,fixed->mon_fixed);
			break;
		case 3:// si la balise est un bouton
			// initialisation d'un bouton
			Btn = Initialiser_boutton(	(char*)xmlGetProp(cur, "label"),
										(char*)xmlGetProp(cur, "tooltip"),
										(char*)xmlGetProp(cur, "image_icon"),
										atoi((char*)xmlGetProp(cur, "largeur")),
										atoi((char*)xmlGetProp(cur, "longueur")), 
										atoi((char*)xmlGetProp(cur, "relief")),
										atoi((char*)xmlGetProp(cur, "X")),
										atoi((char*)xmlGetProp(cur, "Y")));
			//creation d'un bouton
			Btn = creer_boutton(Btn);
			printf("\na button was created\n");

			ajoueter_a_conteuneur(cur->parent, Gtk_parent, Btn->button,Btn->pos.X, Btn->pos.Y);

			break;
		case 4:

			printf("\n menu trouver\n");
			accel_group = gtk_accel_group_new();
			CelluleMenuListe=creer_Menu_fils(doc, cur, accel_group);
			menu = Creer_Menu(CelluleMenuListe);
			printf("\nMenu creer\n");
			gtk_window_add_accel_group(Gtk_parent, accel_group);
			GtkWidget* fixed;
			fixed = gtk_fixed_new();
			gtk_fixed_put(GTK_FIXED( fixed), menu->main_menu,0,0);
			gtk_container_add(Gtk_parent, fixed);

			break;
		case 7: 
			printf("\ntoolbar trouver\n");
			toolbar=Init_toolbar(NULL, atoi((char*)xmlGetProp(cur, "icon_size")),
										atoi((char*)xmlGetProp(cur, "style")),
										atoi((char*)xmlGetProp(cur, "orientation")));
			toolbar = Creer_toolbar(toolbar);
			creer_fils(doc, cur, toolbar->toolbar);
			gtk_fixed_put(GTK_FIXED(Gtk_parent), GTK_WIDGET(toolbar->toolbar), 150, 150);
			printf("\ntoolbar creer\n");
			break;
		case 8 :
			do
			{
				printf("\nCelluleToolItem trouver\n");
				celluleToolItem = Init_CelluleTooolItem((char*)xmlGetProp(cur, "label"),
					(char*)xmlGetProp(cur, "icon"),
					atoi((char*)xmlGetProp(cur, "callback")));
				celluleToolItem = Creer_CelluleToolItem(celluleToolItem);//creer le nouvel élément
				gtk_toolbar_insert(GTK_TOOLBAR(Gtk_parent), celluleToolItem->item, n++);
				printf("\nCelluleToolItem inserer\n");
				//pointer sur la balise suivante
				cur = cur->next;
			} while(!xmlStrcmp(cur->name, (const xmlChar*)"CelluleToolItem"));
			cur=cur->prev;
			break;
		case 9:
			printf("\nBox trouver\n");
			boite = Allouer_Box(atoi((char*)xmlGetProp(cur, "orientation")), atoi((char*)xmlGetProp(cur, "espacement")));
			Creer_Box(boite, Gtk_parent);
			printf("\nBox est creer\n");
			break;
		default:break;
		}
		//pointer sur la balise suivante
		cur = cur->next;
	}
	return;
}

//________________________________________________________________________________________________

/*
 * Fonction qui permet de creer tous les fils d'une balise
 * entrées : -> Le document ou il y a le code xml
 *			 -> la balise pere en format xmlNodePtr
 *			 -> la balise pere en format GtkWidget
 * sorties : void
 */

void
Lire_doc(char* docname) {

	Fenetre* Fen;
	xmlDocPtr doc;
	xmlNodePtr cur;
	int nat;

	//l'ouverure et la lecture de fichier xml
	doc = xmlParseFile(docname);

	//tester si l'ouverture est bien faite
	if (doc == NULL) {
		fprintf(stderr, "ERREUR d'ouverture de fichier \n");
		return;
	}
	//pointer sur la balise global --> <interface>
	cur = xmlDocGetRootElement(doc);

	//tester si il y a une balise ou non
	if (cur == NULL) {
		fprintf(stderr, "\nle document est vide\n");
		xmlFreeDoc(doc);
		return;
	}
	//tester si la balise pointer est la balise interface
	if (xmlStrcmp(cur->name, (const xmlChar*)"interface")) {
		fprintf(stderr, "\ndocument of the wrong type, root node != interface");
		xmlFreeDoc(doc);
		return;
	}

	//pointer sur le fils de la balise cur
	cur = cur->xmlChildrenNode;
	//boucler jusqu'il y a aucune balise a traiter (frere)
	while (cur != NULL) {
		//teser la nature de la balise
		nat = nature_balise(cur);
		// tester si la balise est une fenetre
		if (nat == 1)
		{
			printf("\nFenetre trouver \n", (char*)cur->name);
			//l'appel de la fonction Allouer_Fenetre
			Fen = Allouer_Fenetre(0,
				atoi((char*)xmlGetProp(cur, "largeur")),
				atoi((char*)xmlGetProp(cur, "hauteur")),
				(char*)xmlGetProp(cur, "Titre"),
				"C:\\Users\\HP FOLIO 9470m\\Desktop\\gtk atelier\\ts\\ts\\home.png",
				atoi((char*)xmlGetProp(cur, "X")),
				atoi((char*)xmlGetProp(cur, "Y")),
				NULL, (char*)xmlGetProp(cur, "couleur"), (char*)xmlGetProp(cur, "name"));
			//la creation d'une fenetre
			Fen = Creer_Fenetre(Fen);

			printf("\nfenetre creer\n");
			//creation de tous les fils de la fenetre creer
			creer_fils(doc, cur, Fen->ma_fenetre);
			gtk_widget_show_all(Fen->ma_fenetre);

		}

		cur = cur->next;
	}
	xmlFreeDoc(doc);
	return;
}

//__________________________________________________________________________________________

