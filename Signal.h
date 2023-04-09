#pragma once

typedef struct {
    GtkWindow *window;
    GtkWidget *username_entry;
    GtkWidget *password_entry;
}loginstructure;

loginstructure *Init_Login_structure(GtkWindow *window,GtkWidget *username_entry,GtkWidget *password_entry)
{
    loginstructure *NE=(loginstructure*) malloc(sizeof (loginstructure));
    if(!NE)
    {
        printf("\nerreur d'allocation");
        exit(-1);
    }
    // NE->infoBar=infoBar;
    NE->window=window;
    NE->password_entry=password_entry;
    NE->username_entry=username_entry;
    return ((loginstructure*)NE);
}


GtkWidget* chercher_widget_par_conteneur(char* nom, GtkWidget* widget)
{

	GtkWidget* child_widget = NULL;
	GList* children = NULL;
	GList* iter2;
	char name[NB_Cara_titre];
	child_widget = NULL;
	if (GTK_IS_ENTRY(widget) || GTK_IS_LABEL(widget)|| GTK_IS_IMAGE(widget))return((GtkWidget*)child_widget);

	children = gtk_container_get_children(GTK_CONTAINER(widget));

	for (iter2 = children; iter2 != NULL; iter2 = iter2->next) {
		widget = GTK_WIDGET(iter2->data);
		strcpy(name, gtk_widget_get_name(widget));
		printf("\n the name %s \n", name);
		if (!strcmp(name, nom)) {
			child_widget = widget;
			break;
		}
		else
		{
			child_widget = chercher_widget_par_conteneur(nom, GTK_WIDGET(widget));
		}
	}
	if (child_widget)
		printf("\n le widegt %s est trouve\n", name);
	else
		printf("\n le widegt n'est trouve\n");
	g_list_free(children);
	return((GtkWidget*)child_widget);
}

GtkWidget *chercher_widget( char* nom)
{
	GList* windows, * iter;
	GtkWindow* window = NULL;
	GtkWidget* child_widget = NULL;
	char* name = NULL;
	// R�cup�rer la liste des fen�tres principales
	windows = gtk_window_list_toplevels();
	for (iter = windows; iter != NULL; iter = g_list_next(iter)) {
		window = GTK_WINDOW(iter->data);
		child_widget = chercher_widget_par_conteneur(nom, GTK_WIDGET( window));
	}
	if (child_widget)
		printf("\n le widegt est trouve\n");
	else
		printf("\n le widegt n'est trouve\n");
    g_list_free(windows);
    return ((GtkWidget*)child_widget);
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

	// R�cup�rer la liste des fen�tres principales
	windows = gtk_window_list_toplevels();
	for (iter = windows; iter != NULL; iter = g_list_next(iter)) {
		window = GTK_WINDOW(iter->data);
		if (!strcmp(gtk_widget_get_name(GTK_WIDGET(window)), name))
		{
			printf("\n fenetre trouver %s \n", name);
			return((GtkWindow*)window);
		}
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
	gtk_widget_destroy(GTK_WIDGET(chercher_fenetre_parFils(GTK_WIDGET(wdgt1))));
}
void login_clicked(G_GNUC_UNUSED GtkButton* bouton,loginstructure*STR)
{
    printf("\nlogin clicked");
    int found=0;
    const gchar *username,*pwd;
    InfoToolBar *warning;
    int nbjoueur;
    warning= Init_InfoToolBar("user name or password incorrect !!","ok",1,"vide");
    warning= Creer_InfoToolBar(warning);
    cellulejoueur*Base=remplir_Base_Joueur(&nbjoueur);
    cellulejoueur*ptc=Base;
    username=(gchar *)malloc(maxcarac*sizeof (gchar));
    username= gtk_entry_get_text(GTK_ENTRY(STR->username_entry));
    pwd=(gchar *)malloc(maxcarac*sizeof (gchar));
    pwd= gtk_entry_get_text(GTK_ENTRY(STR->password_entry));
    while (ptc)
    {
        if(!strcmp(ptc->info->username,username))
        {
            found=1;
            break;
        }
        ptc=ptc->svt;
    }
    if(found)
    {
        if(!strcmp(ptc->info->password,pwd))
            afficher_fenetre(STR->window);
        else
        printf("\nfalse user info !!");
    }
    else
        printf("\n not found !!");
}
void Signal(xmlDocPtr doc, xmlNodePtr cur, GtkWidget* wdgt)
{
	cur = cur->xmlChildrenNode;

    loginstructure *L;
    GtkWidget *usernameentry,*pwdentry;
	GtkWindow* win,*window_parent;
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
				win = chercher_fenetre_parNom((char*)xmlGetProp(cur, "data1"));
                usernameentry= chercher_widget((char*)xmlGetProp(cur, "data2"));
                pwdentry= chercher_widget((char*)xmlGetProp(cur, "data3"));
                L= Init_Login_structure(win,usernameentry,pwdentry);
				g_signal_connect(wdgt, "clicked", G_CALLBACK(login_clicked), L);
				printf("\n signal realiser \n");
				break;
			default:break;
			}

		}
		cur = cur->next;
	}

	//printf(atoi((char*)xmlGetProp(cur,)))
}