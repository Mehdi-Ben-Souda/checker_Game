//La structure de données du switch
typedef struct sw
{
    //un widget qui a deux états: activé ou désactivé
    GtkWidget *my_switch;
    GtkWidget *fixed_container;//le conteneur
    int etat;//activé ou désactivé
}Switch;
/*
La fonction Creer_Switch
-Entrees :etat1:un entier indique l'état du boutton.
-Sortie :Objet de type Switch.
-Description: Cette fonction permet de créer un switch boutton 
        on prenons on concidération l'état qu'on veut
*/
Switch*Creer_Switch(int etat1)
{
    //allocation de la mémoire 
    Switch*my_switch1=(Switch*)malloc(sizeof(Switch));
    //si l'allocation a échoué
    if(!my_switch1)
    {
        printf("Erreur d'allocation"); exit(-1);
    }
    //Crée un widget GtkSwitch
    my_switch1->my_switch=gtk_switch_new();
    //initialisation de l'état du switch
    my_switch1->etat=etat1;
    switch(etat1)
    {
        //si on veut choisir l'état activé pour le switch
        case 0:gtk_switch_set_state(GTK_SWITCH(my_switch1->my_switch), FALSE);break;
        //si on veut choisir l'état désactivé pour le switch
        case 1: gtk_switch_set_state(GTK_SWITCH(my_switch1->my_switch), TRUE);break;
        //activé par défaut 
        default: gtk_switch_set_active(GTK_SWITCH(my_switch1->my_switch), TRUE);
    }
    return((Switch*)my_switch1);
}

//La structure de données de l'entrée de recherche
typedef struct
{
    //un widget de la sous classe des GtkEntry
    GtkWidget *search;
    GtkWidget *conteneur;//le conteneur du widget
}Search;
/*
La fonction Creer_Search
-Entrees :conteneur1:de type GtkWidget.
-Sortie : une zone de recherche.
-Description: Cette fonction permet de créer une zone de 
            recherche 
*/
Search*Creer_Search(GtkWidget *conteneur1)
{
    //allocation de la mémoire 
    Search*sea=(Search*)malloc(sizeof(Search));
    //si l'allocation a échoué
    if(!sea)
    {
        printf("Erreur d'allocation"); exit(-1);
    }
    //Initialisation du conteneur
     sea->conteneur =conteneur1;
     //créer un nouveau Gtk widget de recherche
    sea->search=gtk_search_entry_new ();
    return ((Search*)sea);
}
//La structure de données de check boutton
typedef struct cb
{
    char label[15];//le titre du boutton
    GtkWidget *ma_check_button;
    GtkWidget *vbox;//le conteneur
    gchar orientation;//vertical ou horizontal
    gint espace;//l'espace entre les check boutton dans le box
    struct cb *svt;//regrouper les boutton de meme groupe
} check_button;
/*
La fonction Creer_check_bouton
-Entrees :label1:un tableau de caractères,
          orientation1:soit vertical soit horizontal,
          espace1:un entier indique l'éspace entre les widget 
          dans le box
-Sortie :objet de type check_bouton.
-Description: Cette fonction permet de créer des cases à cocher
    en utilisant un conteneur de type GtkBox qui permet
    d'organiser les widgets enfants(les bouttons) en une seule ligne ou colonne
    en fonction de la valeur de champs orientation
*/
check_button*creer_check_bouton(char label1[15],gchar orientation1,gint espace1)
{
    //allocation de la mémoire 
    check_button*ch=(check_button*)malloc(sizeof(check_button));
    //si l'allocation a échoué
    if(!ch)
    {
        printf("Erreur d'allocation"); exit(-1);
    }
    //Initialisation 
    ch->orientation=orientation1;
    ch->svt=NULL;
    ch->espace=espace1;
    //Crée une nouvelle GtkBox avec orientation horizontal
    if(ch->orientation==H||ch->orientation==h)
         ch->vbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,ch->espace );
    else 
     //Crée une nouvelle GtkBox avec orientation vertical
    if(ch->orientation==v||ch->orientation==V)
         ch->vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL,ch->espace);
         else 
         {
         printf("\nL'orientation est invalide !");
         exit(0);
         }
         //si on veut un boutton avec label ou label avec mnemonic
    if(label1)
       ch->ma_check_button=gtk_check_button_new_with_mnemonic(label1);
    else//sinon un boutton sans label
       ch->ma_check_button=gtk_check_button_new();
    return ((check_button*)ch);
}
/*
La fonction Inserer_liste_chboutton
-Entrees :Maliste:pointeur de type check_button,
         label1:un tableau de caractère
-Sortie :objet de type check_bouton.
-Déscription: Cette fonction permet d'insérer les case à cocher 
            dans la liste,et regrouper les cases à cocher .
*/
check_button*Inserer_liste_chboutton(check_button*Maliste,char label1[15])
{
    //déclaration des variables
    check_button*ptc,*ne;
    //appel à la fonction de la création 
    ne= creer_check_bouton(label1);
    //si la liste est vide
    if(!Maliste)
    {
        gtk_container_add (GTK_CONTAINER ( ne->vbox),
         ne->ma_check_button);
        return (ne);
    }
    //un pointeur courant parcourant la liste
    ptc=Maliste;
    while(ptc->svt)
    ptc=ptc->svt;
    //on ajoute le nouveau élément à la fin de la liste
    ptc->svt=ne;
    ne->vbox=Maliste->vbox;
    gtk_container_add (GTK_CONTAINER ( Maliste->vbox), 
    ne->ma_check_button);
    return ((check_button*)Maliste);
}
//La structure de données de l'entrée
typedef struct et
{
    gchar cache;//le caractère de cach dans la zone de texte
    gchar *text;//le text par défaut dans la zone
    GtkWidget *entry;//le widget 
    GtkWidget *conteneur;//le conteneur du widget
    gint visible;//0 invisible,1 visible
    gchar *icon;//l'icon dans la zone
}Entree;
/*
La fonction Entry_init
-Entrees :text1:une chaine de caractere pour le text saisi 
          par défaut dans la zone.
     visible1:entier indique si les caractéres entrées sont 
              visible ou pas.
    cache1:caractère indique le caractère choisi pour 
           cacher le text saisi
    cont:de type GtkWidget le conteneur qui va contenir
         la zone de text
    mon_icon:une chaine de caractère indique le nom
            de l'icon à ajouter dans la zone.
-Sortie :Objet de type Entree.
-Description: Cette fonction permet d'allouer de l'espace pour
la structure de type Entree et d'initialiser
ses champs et de la retourner .
*/
Entree* Entry_init(gchar *text1,int visible1,gchar cache1,
GtkWidget *cont,gchar *mon_icon)
{
    Entree* mon_entre=(Entree*)malloc(sizeof(Entree));
    if(!mon_entre)
    {
        printf("Erreur d'allocation"); exit(-1);
    }
    //initialisation de la manière de saisie
    mon_entre->visible = visible1;
    //Initialisation de caractère de remplacement
    if(cache1)
        mon_entre->cache=cache1;
    else mon_entre->cache='\0';
    //initilisation du conteneur
    mon_entre->conteneur= cont;
    //initilisation de text par défaut 
    if (text1)
    {
        mon_entre->text = (gchar*) malloc (150*sizeof (gchar));
        strcpy (mon_entre->text, text1);
    }
    else mon_entre->text =NULL;
    //initilisation pour l'icon
    if (mon_icon)
    {
        mon_entre->icon = (gchar*) malloc (150*sizeof (gchar));
        strcpy (mon_entre->icon, mon_icon);
    }
    else mon_entre->icon =NULL;
    //on retourne la structure initialisé
    return((Entree*)mon_entre);
}
/*
La fonction Creer_Entree
-Entrees :L'objet Entree initialisé.
-Sortie :Objet de type Entree.
-Description: Cette fonction permet de créer un objet entree 
    en fonction des paramétres récupéres de la fonction 
    Entree_init
*/
Entree*Creer_Entree(Entree*mon_entre)
{
    //Création d'une nouvelle entrée
    mon_entre->entry = gtk_entry_new ();
    //si on veut que le texte saisi soit visible
 if ( mon_entre->visible==1)
  gtk_entry_set_visibility (GTK_ENTRY( mon_entre->entry),TRUE);
        //si on veut un mot de passe
 else
 {
  gtk_entry_set_visibility (GTK_ENTRY( mon_entre->entry),FALSE);
     //avec choix de caractère de cache
 if ( mon_entre->cache)
    gtk_entry_set_invisible_char(GTK_ENTRY( mon_entre->entry),
     mon_entre->cache);
}
 //si on veut un texte saisi par défaut dans la zone de texte
 if(mon_entre->text)
  {
 gtk_entry_set_text (GTK_ENTRY(mon_entre->entry),mon_entre->text);
  }
 //si on veut ajouter un icon
 if(mon_entre->icon)
 {
    gtk_entry_set_icon_from_icon_name(GTK_ENTRY(mon_entre->entry)
    ,GTK_ENTRY_ICON_SECONDARY,mon_entre->icon);
 }
    return ((Entree*)mon_entre);
}
