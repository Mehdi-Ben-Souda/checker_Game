
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
	//tester si la balise est une fenetre
	return((int)-1);
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
	int nat;
	GtkWidget* fixed,*parent;
	Boutton *Btn;

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
			fixed = create_fixed((char*)xmlGetProp(cur, "name"));
			printf("\nfixed created\n");
			//ajouter  le fixed a la balise parent
			gtk_container_add(GTK_CONTAINER(Gtk_parent), fixed);
			printf("\nfixed added to the window\n");
			//creation de tous les fils de ce fixed
			creer_fils(doc, cur, fixed);
			break;
		case 3:// si la balise est un bouton
			// initialisation d'un bouton
			Btn = Initialiser_boutton((char*)xmlGetProp(cur, "name"),
										(char*)xmlGetProp(cur, "label"),
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
			nat = nature_balise(cur->parent);
			//tester la nature de la balise parent
			if (nat == 2)// si le parent est fixed
			{
				gtk_fixed_put(GTK_FIXED(Gtk_parent), GTK_WIDGET(Btn->button), Btn->pos.X, Btn->pos.Y);
				printf("\nbutton was added to the container Fixed\n");
			}
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
				NULL, NULL, (char*)xmlGetProp(cur, "name"));
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

