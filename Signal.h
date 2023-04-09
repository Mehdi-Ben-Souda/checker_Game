#pragma once

GtkWidget* chercher_widget_par_conteneur(char* nom, GtkWidget* widget)
{

	GtkWidget* child_widget = NULL;
	GList* children = NULL;
	GList* iter2;
	char* name = NULL;
	child_widget = NULL;
	children = gtk_container_get_children(GTK_CONTAINER(widget));

	for (iter2 = children; iter2 != NULL; iter2 = iter2->next) {
		widget = GTK_WIDGET(iter2->data);
		name = gtk_widget_get_name(widget);
		printf("\n the name %s \n", name);
		if (name != NULL && !strcmp(name, nom)) {
			child_widget = widget;
			break;
		}
		else
		{
			child_widget = chercher_widget_par_conteneur(nom, widget);
		}
	}
	if (child_widget)
		printf("\n le widegt %s est trouve\n", name);
	else
		printf("\n le widegt n'est trouve\n");
	g_list_free(children);
	return((GtkWidget*)child_widget);
}

void chercher_widget( char* nom)
{
	GList* windows, * iter;
	GtkWindow* window = NULL;
	GtkWidget* child_widget = NULL;

	char* name = NULL;
	// Récupérer la liste des fenêtres principales
	windows = gtk_window_list_toplevels();
	for (iter = windows; iter != NULL; iter = g_list_next(iter)) {
		window = GTK_WINDOW(iter->data);
		child_widget = chercher_widget_par_conteneur(nom, window);
	}
	if (child_widget)
		printf("\n le widegt %s est trouve\n", nom);
	else
		printf("\n le widegt n'est trouve\n");
	g_list_free(windows);	
	return((GtkWidget*)child_widget);
}

GtkWindow* chercher_fenetre_parFils(GtkWidget *fils)
{
	GtkWidget* parent = fils;
	while (parent && !GTK_IS_WINDOW(parent)) {
		parent = gtk_widget_get_parent(parent);
	}
	return((GtkWindow*)parent);
}

GtkWindow* chercher_fenetre_parNom(char name[NB_Cara_titre])
{
	GList* windows, * iter;
	GtkWindow* window=NULL;

	// Récupérer la liste des fenêtres principales
	windows = gtk_window_list_toplevels();
	for (iter = windows; iter != NULL; iter = g_list_next(iter)) {
		window = GTK_WINDOW(iter->data);
		if (!strcmp(gtk_widget_get_name(window), name))return((GtkWindow*)window);
		window = NULL;
	}
	//if (!window)printf("\n fenetre inexistant\n");
	g_list_free(windows);
	return((GtkWindow*)NULL);
}
void Signal_afficher_fenetre(GtkWindow *wdgt1, GtkWindow* wdgt2)
{
	GtkWindow* The2_wdgt = (GtkWindow*)wdgt2;
	afficher_fenetre(The2_wdgt);
}
void Signal_afficher_fenetre_et_destroy(GtkWindow* wdgt1, GtkWindow* wdgt2)
{
	GtkWindow* The2_wdgt = (GtkWindow*)wdgt2;
	afficher_fenetre(The2_wdgt);
	gtk_widget_destroy(chercher_fenetre_parFils(wdgt1));
}

void Signal(xmlDocPtr doc, xmlNodePtr cur, GtkWidget* wdgt)
{
	cur = cur->xmlChildrenNode;
	GtkWindow* win;
	int nat, callback;
	while (cur)
	{

		nat = nature_balise(cur);
		if (nat == 20)
		{
			printf("\n la balise a de signal\n ");
			callback = atoi((char*)xmlGetProp(cur, "callback"));
			printf("\n %d", callback);
			switch (callback)
			{
			case 1:
				win = chercher_fenetre_parNom((char*)xmlGetProp(cur, "data"));
				g_signal_connect(wdgt, "clicked", G_CALLBACK(Signal_afficher_fenetre), win);
				printf("\n signal realiser \n");
				break;
			case 2:
				win = chercher_fenetre_parNom((char*)xmlGetProp(cur, "data"));
				g_signal_connect(wdgt, "clicked", G_CALLBACK(Signal_afficher_fenetre_et_destroy), win);
				printf("\n signal realiser \n");
				break;
			default:break;
			}

		}
		cur = cur->next;
	}

	//printf(atoi((char*)xmlGetProp(cur,)))
}