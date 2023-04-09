#pragma once
#include <gtk/gtk.h>

#define NB_Cara_titre 50
#define NB_Cara_chemin 150


typedef struct crd
{
    int X;
    int Y;
}coordonne;

/**********************************fonction du couleur***********************************/
#pragma warning(disable: 4996)
void add_bgcolor(GtkWidget* widget, char couleur[NB_Cara_titre], gdouble opacite)

{

	if (couleur == NULL) return;

	GdkRGBA color;
	gdk_rgba_parse(&color, couleur);
	color.alpha = opacite;
	gtk_widget_override_background_color(widget, GTK_STATE_FLAG_NORMAL, &color);
}
#pragma warning(disable: 4996)
/*
 * Fonction qui permet de identifier la nature de balise
 * entr�es : un element de type xmlNodePtr ,c'est la balise a identifier
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
	//tester si la balise est un InfoToolBar
	if ((!xmlStrcmp(balise->name, (const xmlChar*)"InfoToolBar")))return((int)10);
	//tester si la balise est un Radio_Check_Buttons
	if ((!xmlStrcmp(balise->name, (const xmlChar*)"Radio_Check_Buttons")))return((int)11);
	//tester si la balise est un Check_Button
	if ((!xmlStrcmp(balise->name, (const xmlChar*)"Check_Button")))return((int)12);
	//tester si la balise est un Radio_Button
	if ((!xmlStrcmp(balise->name, (const xmlChar*)"Radio_Button")))return((int)13);
	//tester si la balise est un ComboBox
	if ((!xmlStrcmp(balise->name, (const xmlChar*)"ComboBox")))return((int)14);
	//tester si la balise est un Option
	if ((!xmlStrcmp(balise->name, (const xmlChar*)"Option")))return((int)15);
	//tester si la balise est un Switch
	if ((!xmlStrcmp(balise->name, (const xmlChar*)"Switch")))return((int)16);
	//tester si la balise est un Search_bar
	if ((!xmlStrcmp(balise->name, (const xmlChar*)"Search_bar")))return((int)17);
	//tester si la balise est un Entry
	if ((!xmlStrcmp(balise->name, (const xmlChar*)"Entry")))return((int)18);
	//tester si la balise est un Toggle_Boutton
	if ((!xmlStrcmp(balise->name, (const xmlChar*)"Toggle_Boutton")))return((int)19);
	//tester si la balise est un signal
	if ((!xmlStrcmp(balise->name, (const xmlChar*)"signal")))return((int)20);
	//tester si la balise est un Label
	if ((!xmlStrcmp(balise->name, (const xmlChar*)"Label")))return((int)21);
	return((int)-1);
}
