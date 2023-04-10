#pragma once

/*
 * Fonction qui permet d'ajouter un element a un conteneur
	ou juste de l'ajouter a son parent
 * entr�es: -un element de type xmlNodePtr ,c'est la balise parent
			-deux elements de type GtkWidget , le premier widget parent
			le deuxiem est le fils
			- deux valeurs entiers pour indiquer la position
 * sorties : void
 */
void ajoueter_a_conteuneur(xmlNodePtr cur_parent, GtkWidget* parent, GtkWidget* fils, int X, int Y)
{
	int nat;
	//tester la nature de la balise parent
	nat = nature_balise(cur_parent);
	if (nat == 2)// si le parent est fixed
	{
		//ajouet le element au Fixed
		gtk_fixed_put(GTK_FIXED(parent), fils, X, Y);
		printf("\n an element was added to the container Fixed\n");
	}
	else {
		if (nat == 9)// si le parent est Box
		{
			//ajouet le element au Fixed
			gtk_box_pack_end(GTK_BOX(parent), fils, 0, 0, 0);
		}
		else {// si le parent est quelque chose d'autre
			printf("\n an element was added to his parent %s\n", cur_parent->name);
			gtk_container_add(GTK_CONTAINER(parent), fils);
		}
	}
}
/*
 * Fonction qui permet de creer tous les fils d'une celluleMenu
 * entr�es:  -> Le document ou il y a le code xml
 *			 -> la balise pere en format xmlNodePtr
 *			 -> la balise pere en format GtkWidget
 *			 -> un element de type GtkAccelGroup
 * sorties : une liste de tous le element de type CelluleItem trouver
 */
CelluleItem* creer_CelluleMenu_fils(xmlDocPtr doc, xmlNodePtr cur, GtkAccelGroup* accel_group)
{
	CelluleItem* CelluleItemListe = NULL;
	int nat;

	//pointer sur le premier fils de la balise cur
	cur = cur->xmlChildrenNode;

	// boucler jusqu'il y a pas encore une autre balise (frere)
	while (cur != NULL)
	{
		//tester la nature de la balise 
		nat = nature_balise(cur);
		if (nat == 6) {
			//l'appel de la fonction Inserer_CelluleItem
			CelluleItemListe = Inserer_CelluleItem(CelluleItemListe,
				(char*)xmlGetProp(cur, "label"),
				(char*)xmlGetProp(cur, "icon"),
				(char*)xmlGetProp(cur, "name"),
				(char*)xmlGetProp(cur, "accel_key"),
				accel_group);
			printf("\n CelluleItem inserer\n");
		}
		//pointer sur la balise suivante (frere)
		cur = cur->next;
	}

	return((CelluleItem*)CelluleItemListe);
}
/*
 * Fonction qui permet de creer tous les fils d'un Menu
 * entr�es:  -> Le document ou il y a le code xml
 *			 -> la balise pere en format xmlNodePtr
 *			 -> la balise pere en format GtkWidget
 *			 -> un element de type GtkAccelGroup
 * sorties : une liste de tous le element de type CelluleMenu trouver
 */
CelluleMenu* creer_Menu_fils(xmlDocPtr doc, xmlNodePtr cur, GtkAccelGroup* accel_group)
{
	CelluleMenu* CelluleMenuListe = NULL;
	CelluleItem* CelluleItemListe = NULL;
	int nat;

	//pointer sur le premier fils de la balise cur
	cur = cur->xmlChildrenNode;

	// boucler jusqu'il y a pas encore une autre balise (frere)
	while (cur != NULL)
	{
		//tester la nature de la balise 
		nat = nature_balise(cur);
		if (nat == 5) {
			/*l'appel de la fonction creer_CelluleMenu_fils pour creer les fils de
				la balise CelluleMenu trouver*/
			CelluleItemListe = creer_CelluleMenu_fils(doc, cur, accel_group);
			// inserer a la liste
			CelluleMenuListe = Inserer_CeluleMenu(CelluleMenuListe, CelluleItemListe,
				(char*)xmlGetProp(cur, "label"));
			printf("\n cellule menu inserer\n");
		}
		//pointer sur la balise suivante (frere)
		cur = cur->next;
	}

	return((CelluleMenu*)CelluleMenuListe);

}

/*____________________________________________________________________________

 * Fonction qui permet de creer tous les fils d'une balise
 * entr�es : -> Le document ou il y a le code xml
 *			 -> la balise pere en format xmlNodePtr
 *			 -> la balise pere en format GtkWidget
 * sorties : void
 */
void
creer_fils(xmlDocPtr doc, xmlNodePtr cur, GtkWidget* Gtk_parent) {
	//les declaration de tous les elements
	int nat, n = 0;
	xmlNodePtr cur_parent = NULL;
	Fixed* fixed = NULL;
	Bouton* Btn = NULL;
	CelluleMenu* celluleMenu = NULL;
	Menu* menu = NULL;
	CelluleMenu* CelluleMenuListe = NULL;
	GtkAccelGroup* accel_group = NULL;
	ToolBar* toolbar = NULL;
	ToolItem* celluleToolItem = NULL;
	Box* boite = NULL;
	InfoToolBar* infotoolbar = NULL;
	CelluleBouton* listeButton = NULL;
	RadioCheckBouttons* RC_Bouttons = NULL;
	//comboBox* combo = NULL;
	Switch* swtch = NULL;
	Search* srch = NULL;
	Entree* entry = NULL;
	comboBox* combo = NULL;
	Label* label = NULL;

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
			creer_fils(doc, cur, fixed->mon_fixed);
			break;
		case 3:// si la balise est un bouton
			// initialisation d'un bouton
			Btn = Initialiser_boutton((char*)xmlGetProp(cur, "label"),
				(char*)xmlGetProp(cur, "tooltip"),
				(char*)xmlGetProp(cur, "image_icon"),
				atoi((char*)xmlGetProp(cur, "largeur")),
				atoi((char*)xmlGetProp(cur, "longueur")),
				atoi((char*)xmlGetProp(cur, "relief")),
				atoi((char*)xmlGetProp(cur, "X")),
				atoi((char*)xmlGetProp(cur, "Y")), (char*)xmlGetProp(cur, "couleur"));
			//creation d'un bouton
			Btn = Creer_SimpleBoutton(Btn);
			printf("\na button was created\n");
			ajoueter_a_conteuneur(cur->parent, Gtk_parent, Btn->Mabouton->button, Btn->pos.X, Btn->pos.Y);
			Signal(doc, cur, Btn->Mabouton->button);
			break;
		case 4:// si la balise est un menu
			printf("\n menu trouver\n");
			//la creation d'un accel_group pour les racoursi
			accel_group = gtk_accel_group_new();
			//la creation de tous les fils de ce menu (sous menu)
			CelluleMenuListe = creer_Menu_fils(doc, cur, accel_group);
			//la creation de menu avec l'insertion de tous les sous menu
			menu = Creer_Menu(CelluleMenuListe, atoi((char*)xmlGetProp(cur, "X")),
				atoi((char*)xmlGetProp(cur, "Y")),
				atoi((char*)xmlGetProp(cur, "orientation")));

			printf("\nMenu creer\n");
			gtk_window_add_accel_group(GTK_WINDOW( Gtk_parent), accel_group);
			//ajouter le menu a un son pere (FIXED ,BOX ,SIMPLE ELEMENT)
			ajoueter_a_conteuneur(cur->parent, Gtk_parent, menu->main_menu,
				menu->pos.X, menu->pos.Y);

			break;
		case 7:// si la balise est un toolbar
			printf("\ntoolbar trouver\n");
			//l'initialisation d'un toolbar
			toolbar = Init_toolbar(atoi((char*)xmlGetProp(cur, "icon_size")),
				atoi((char*)xmlGetProp(cur, "style")),
				atoi((char*)xmlGetProp(cur, "orientation")),
				atoi((char*)xmlGetProp(cur, "X")),
				atoi((char*)xmlGetProp(cur, "Y")));
			//la creation d'un toolbar
			toolbar = Creer_toolbar(toolbar);
			//la creation de tous ses fils
			creer_fils(doc, cur, toolbar->toolbar);
			ajoueter_a_conteuneur(cur->parent, Gtk_parent, toolbar->toolbar,
				toolbar->x_y.X, toolbar->x_y.Y);
			printf("\ntoolbar creer\n");
			break;
		case 8:// si la balise est un CelluleToolItem
			do
			{
				printf("\nCelluleToolItem trouver\n");
				//l'initialisation d'un CelluleTooolItem
				celluleToolItem = Init_CelluleTooolItem((char*)xmlGetProp(cur, "label"),
					(char*)xmlGetProp(cur, "icon"));
				//la creation d'un CelluleToolItem
				celluleToolItem = Creer_CelluleToolItem(celluleToolItem);
				//l'inserer a son parent (toolbar)
				gtk_toolbar_insert(GTK_TOOLBAR(Gtk_parent), celluleToolItem->item, n++);
				printf("\nCelluleToolItem inserer\n");
				//pointer sur la balise suivante
				cur = cur->next;
				//boucler tanqu'il y a une balise CelluleToolItem
			} while (!xmlStrcmp(cur->name, (const xmlChar*)"CelluleToolItem"));
			//pointer sur l'element precedant
			cur = cur->prev;
			break;
		case 9:// si la balise est un Box
			printf("\nBox trouver\n");
			//l'initialisation d'un Box
			boite = Allouer_Box(atoi((char*)xmlGetProp(cur, "orientation")),
				atoi((char*)xmlGetProp(cur, "espacement")));
			//la creation d'un box
			Creer_Box(boite, Gtk_parent);
			printf("\nBox est creer\n");
			break;
		case 10:// si la balise est un infotoolbar
			printf("\n infotoolbar trouver\n");
			//l'initialisation d'un InfoToolBar
			infotoolbar = Init_InfoToolBar((char*)xmlGetProp(cur, "message"),
				(char*)xmlGetProp(cur, "boutton_Label"),
				atoi((char*)xmlGetProp(cur, "type_message"))
                ,(char*)xmlGetProp(cur, "name"));
			//la creation d'un InfoToolBar
			infotoolbar = Creer_InfoToolBar(infotoolbar);
			gtk_fixed_put(GTK_FIXED(Gtk_parent), GTK_WIDGET(infotoolbar->info_toolbar), 10, 10);
			printf("\n infotoolbar est creer\n");
			break;
		case 11:// si la balise est un Radio_Check_Buttons
			printf("\n Radio_Check_Buttons trouver\n");
			cur_parent = cur;
			//pointer sur le premier fils de la balise cur
			cur = cur->xmlChildrenNode;
			//boucler jusqu'il ne reste aucune balise a traiter
			while (cur)
			{
				//tester la nature de la balise
				if (nature_balise(cur) == 12)// si la balise est check bouton
				{
					//creer et inserer le bouton trouver a la liste
					listeButton = Inserer_Bouton(listeButton, 'c', (char*)xmlGetProp(cur, "label"));
					printf("\n Check_Button trouver et creer\n");
				}
				if (nature_balise(cur) == 13)// si la balise est check bouton
				{
					//creer et inserer le bouton trouver a la liste
					listeButton = Inserer_Bouton(listeButton, 'r', (char*)xmlGetProp(cur, "label"));
					printf("\n Radio_Button trouver et creer\n");
				}
				//pointer sur l'element suivant (frere)
				cur = cur->next;
			}
			//l'appel de la fonction Crerr_Radio_Check_Boutons
			RC_Bouttons = Crerr_Radio_Check_Boutons(listeButton,
				atoi((char*)xmlGetProp(cur_parent, "X")),
				atoi((char*)xmlGetProp(cur_parent, "Y")),
				atoi((char*)xmlGetProp(cur_parent, "orientation")),
				atoi((char*)xmlGetProp(cur_parent, "spacing")));
			printf("\n Radio_Check_Buttons creer\n");
			//ajouter les boutons creer a son parent
			ajoueter_a_conteuneur(cur_parent->parent, Gtk_parent, RC_Bouttons->groupe->mon_box,
				RC_Bouttons->pos.X, RC_Bouttons->pos.Y);
			//retourner cur a la balise parent pour la suite de traitement
			cur = cur_parent;
			break;
		case 14:// si la balise est un ComboBox 
			printf("\n ComboBox trouver\n");
			cur_parent = cur;
			// la creation de combobox
			combo = creer_combo_Box(atoi((char*)xmlGetProp(cur_parent, "entry")),
				atoi((char*)xmlGetProp(cur_parent, "X")),
				atoi((char*)xmlGetProp(cur_parent, "Y")),
				(char*)xmlGetProp(cur_parent, "name"));
			//pointer sur le premier fils de la balise cur
			cur = cur->xmlChildrenNode;
			//boucler tanqu'il y a une balise a traiter
			while (cur)
			{
				//tester la nature de la balise s'il est un Option
				if (nature_balise(cur) == 15)
				{
					//inserer l'option trouver dans le combo box
					combo = combo_box_inserer(combo, 1, (char*)xmlNodeGetContent(cur),
						(char*)xmlGetProp(cur, "id"));
					printf("\n Option trouver et creer\n");
				}
				//pointer sur la balise suivante (frere)
				cur = cur->next;
			}
			//ajouter le combo box creer a son parent
			ajoueter_a_conteuneur(cur_parent->parent, Gtk_parent,
				combo->combo_box, combo->pos.X, combo->pos.Y);
			//retourner cur a la balise parent pour la suite de traitement
			cur = cur_parent;
			break;
		case 16:// si la balise est un Switch 
			//la creation d'un switch
			swtch = Creer_Switch(atoi((char*)xmlGetProp(cur, "etat")),
				atoi((char*)xmlGetProp(cur, "X")),
				atoi((char*)xmlGetProp(cur, "Y")));
			ajoueter_a_conteuneur(cur->parent, Gtk_parent, swtch->my_switch, swtch->pos.X, swtch->pos.Y);
			break;
		case 17:// si la balise est un Search_bar
			//la creation d'un search bar
			srch = Creer_Search((char*)xmlGetProp(cur, "name"),
				atoi((char*)xmlGetProp(cur, "X")),
				atoi((char*)xmlGetProp(cur, "Y")));
			ajoueter_a_conteuneur(cur->parent, Gtk_parent, srch->search, srch->pos.X, srch->pos.Y);
			break;
		case 18:// si la balise est une entree
			//l'inatialisation d'une entree
            printf("\n entry trouver");
			entry = Entry_init((gchar*)xmlGetProp(cur, "text"),
                               (char*)xmlGetProp(cur, "cache"),
				(char*)xmlGetProp(cur, "icon"),
                (char*)xmlGetProp(cur, "name"),
				atoi((char*)xmlGetProp(cur, "X")),
				atoi((char*)xmlGetProp(cur, "Y")));
			//la creation
			entry = Creer_Entree(entry);
			//l'ajouter a son parent
			ajoueter_a_conteuneur(cur->parent, Gtk_parent, entry->entry, entry->pos.X, entry->pos.Y);
            printf("\nentry ajouter !!!!");
			break;
		case 19:// si la balise est un bouton toogle
			// initialisation d'un bouton toogle
			Btn = Initialiser_boutton((char*)xmlGetProp(cur, "label"),
				(char*)xmlGetProp(cur, "tooltip"),
				(char*)xmlGetProp(cur, "image_icon"),
				atoi((char*)xmlGetProp(cur, "largeur")),
				atoi((char*)xmlGetProp(cur, "longueur")),
				atoi((char*)xmlGetProp(cur, "relief")),
				atoi((char*)xmlGetProp(cur, "X")),
				atoi((char*)xmlGetProp(cur, "Y")), 
				(char*)xmlGetProp(cur, "couleur"));
			//creation d'un bouton toggle
			Btn = Creer_ToggleBoutton(Btn);
			printf("\na ToggleBoutton was created\n");
			ajoueter_a_conteuneur(cur->parent, Gtk_parent, Btn->Mabouton->button, Btn->pos.X, Btn->pos.Y);
			break;
		case 21:
			printf("\n label trouver \n");
			label = Init_label((char*)xmlGetProp(cur, "text"), (char*)xmlGetProp(cur, "name"),
				atoi((char*)xmlGetProp(cur, "X")), atoi((char*)xmlGetProp(cur, "Y")));
			ajoueter_a_conteuneur(cur->parent, Gtk_parent, label->leLabel, label->X_Y.X, label->X_Y.Y);
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
 * entr�es : -> le nom de document a traiter
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
			printf("\nFenetre trouver %s\n", (char*)cur->name);
			//l'appel de la fonction Allouer_Fenetre
			Fen = Allouer_Fenetre(0,
				atoi((char*)xmlGetProp(cur, "largeur")),
				atoi((char*)xmlGetProp(cur, "hauteur")),
				(char*)xmlGetProp(cur, "Titre"),
				"C:\\Users\\HP FOLIO 9470m\\Desktop\\gtk atelier\\ts\\ts\\home.png",
				atoi((char*)xmlGetProp(cur, "X")),
				atoi((char*)xmlGetProp(cur, "Y")),
				(char*)xmlGetProp(cur, "couleur"), (char*)xmlGetProp(cur, "name"),
				atoi((char*)xmlGetProp(cur, "visible")));
			//la creation d'une fenetre
			Fen = Creer_Fenetre(Fen);

			printf("\nfenetre creer\n");
			//creation de tous les fils de la fenetre creer
			creer_fils(doc, cur, Fen->ma_fenetre);
			if (Fen->visible)
				afficher_fenetre(GTK_WINDOW( Fen->ma_fenetre));
			else
				printf("\nfentre creer est non visible(visible = 0)");
		}
		//pointer sur la balise suivante
		cur = cur->next;
	}
	//librer l'espace reserver au document
	xmlFreeDoc(doc);
	return;
}

//__________________________________________________________________________________________
