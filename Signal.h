#pragma once


void chercher_widget(xmlDocPtr doc, char* nom, GtkWidget* wdgt)
{

	/*

	GtkWidget* child_widget = NULL;
	GList* children = gtk_container_get_children(GTK_CONTAINER(container_widget));
	GList* iter;
	for (iter = children; iter != NULL; iter = iter->next) {
		GtkWidget* widget = GTK_WIDGET(iter->data);
		const char* name = gtk_widget_get_name(widget);
		if (name != NULL && strcmp(name, child_name) == 0) {
			child_widget = widget;
			break;
		}
		else
		{
			child_widget = chercher_widget(doc, name, widget);
			if (child_widget != NULL) break;
		}

	}

	g_list_free(children);

	if (child_widget != NULL) {
		printf("\nwidget found\n");
	}
	else {
		wdgt = gtk_widget_get_toplevel(wdgt);
		return((GtkWidget*)chercher_widget(doc,nom,wdgt));
	}
	return((GtkWidget*)child_widget);*/
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