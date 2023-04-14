#pragma once
//----------------------------------------------------------------------------------------------------------------------
//------------------------------------        structures de données       ----------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
typedef struct ce
{
    GtkWidget *menu_item; //pointeur sur un élément
    char label[maxcarac]; //le titre de l'élément
    guint accel_key;//le code ASCII de la lettre du raccourci
    char icon[maxcarac];//le nom de l'icône
    char name[maxcarac];
    struct ce *svt;//pointeur sur le suivant
    struct ce *sous_menu;//sous menu s'il existe
}CelluleItem;//structure d'un élément du menu
typedef struct ne
{
    GtkWidget *sous_menu; //pointeur sur un sous-menu
    char label[maxcarac];//le titre de l'élément
    CelluleItem *liste_item;//liste des éléments du sous-menu
    struct ne *svt;//pointeur sur le suivant
}CelluleMenu;//structure d'un sous-menu du menu principal
typedef  struct
{
    GtkWidget *main_menu;//pointeur sur le menu principal
    CelluleMenu *liste_menu;//liste des sous-menus
    int orientation;
    coordonne pos;
}Menu;//structure d'un menu
//----------------------------------------------------------------------------------------------------------------------
//------------------------------------       Fonction supplémentaires      ---------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
/*
 * Fonction qui permet l'initialisation d'un élément du menu
 * entrées : -> le titre de l'élément
             -> le nom de l'icône de l'élément
             -> la lettre correspondante au raccourci
             -> la fonction de rappelle lorsque l'élément est activé
 * sorties : un pointeur sur élément du menu après initialisation
 */
#pragma warning(disable: 4996)
CelluleItem *Init_CelluleItem(char label[maxcarac],char icon[maxcarac],
                              char name[maxcarac], char accel_key)
{
    CelluleItem *NE;//déclaration d'un nouvel élément
    //l'allocation de la mémoire
    NE=(CelluleItem*) malloc(sizeof (CelluleItem));
    if(!NE)//vérification d'allocation
    {
        printf("\nerrur d'allocation !!!!");
        exit(0);
    }
    //Initialisation des champs de la structure
    strcpy(NE->label,label);
    strcpy(NE->name,name);
    if(accel_key=='$')
        NE->accel_key=100;
    NE->accel_key=(int)accel_key;
    strcpy(NE->icon,icon);
    NE->svt=NULL;//pas de suivant
    NE->menu_item=NULL;
    NE->sous_menu=NULL;//pas de sous-menu
    return ((CelluleItem*)NE);
}
/*
 * Fonction qui permet creer un élément du menu
 * entrées : -> pointeur sur l'élément
             -> le groupe des raccourcis

 * sorties : un pointeur sur élément du menu après création
 */
CelluleItem *Creer_CelluleItem(CelluleItem *item,GtkAccelGroup *accel_group)
{
    if(!item)//vérification d'initialisation de la cellule
        return ((CelluleItem*)NULL);
    //s'il n'y a pas d'icône, on le crée avec seulement le titre
    if(strcmp(item->icon,"vide")==0)
        item->menu_item=gtk_menu_item_new_with_label(item->label);
    else//sinon, on le crée avec l'icône aussi
    {
        item->menu_item=gtk_image_menu_item_new_from_stock( item->icon,NULL);
        gtk_image_menu_item_set_always_show_image(GTK_IMAGE_MENU_ITEM(item->menu_item),TRUE);
        gtk_menu_item_set_label(GTK_MENU_ITEM(item->menu_item),item->label);
    }
    //l'ajout du raccourci
    if(item->accel_key != 100)
        gtk_widget_add_accelerator (item->menu_item, "activate",accel_group,item->accel_key,GDK_CONTROL_MASK,GTK_ACCEL_VISIBLE);
    return ((CelluleItem*)item);
}
/*
 * Fonction qui permet l'initialisation d'un sous-menu
 * entrées : -> un pointeur sur la liste des éléments construisant le sous-menu
             -> le titre de sous-menu
             -> l'icône de sous-menu'
 * sorties : un pointeur sur un sous-menu après initialisation
 */
CelluleMenu *Init_CelluleMenu(CelluleItem *Liste_item,char label[maxcarac])
{
    CelluleMenu *NE;//déclaration d'un nouvel élément

    NE=(CelluleMenu*) malloc(sizeof (CelluleMenu));//allocation de la mémoire
    if(!NE)//vérification de l'allocation
    {
        printf("\nerrur d'allocation !!!!");
        exit(0);
    }
    //initialisation du nouvel élément
    strcpy(NE->label,label);
    NE->liste_item=Liste_item;
    NE->svt=NULL;//pas de suivant
    NE->sous_menu=NULL;
    return ((CelluleMenu*)NE);
}
/*
 * Fonction qui permet la création d'un sous-menu
 * entrés : -> pointeur sur un sous-menu
 * sorties : -> pointeur sur élément du menu après création
 */
CelluleMenu *Creer_CelluleMenu(CelluleMenu *cel)
{
    CelluleItem *ptc;//pointeur courant pour parcourir la liste des éléments
    GtkWidget *submenu;//pointeur pour les regrouper
    if(!cel)//vérification d'initialisation
        return ((CelluleMenu*)NULL);
    //création du sous menu
    cel->sous_menu=gtk_menu_item_new_with_label(cel->label);
    if(cel->liste_item)
    {
        ptc = cel->liste_item;
        submenu = gtk_menu_new();
        while (ptc)//tant qu'il y a des éléments dans la liste, on les ajoute
        {
            gtk_menu_shell_append(GTK_MENU_SHELL(submenu), ptc->menu_item);
            ptc = ptc->svt;//passer à l'élément suivant
        }
        gtk_menu_item_set_submenu(GTK_MENU_ITEM(cel->sous_menu), submenu);
    }
    return ((CelluleMenu*)cel);
}
//----------------------------------------------------------------------------------------------------------------------
//------------------------------------        Fonction prancipales        ----------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
/*
 * Fonction qui permet d'insérer un élément dans une liste des éléments
 * entrées : -> pointeur de type CelluleItem
 *           -> le titre de l'élément
             -> le nom de l'icône de l'élément
             -> la lettre correspondante au raccourci
             -> le groupe des raccourcis
             -> la fonction de rappelle lorsque l'élément est activé
 * sorties : un pointeur sur la liste des éléments
 */
CelluleItem *Inserer_CelluleItem(CelluleItem *Liste_item,char label[maxcarac],
                                char icon[maxcarac],char name[maxcarac],
                                char accel_key, GtkAccelGroup* accel_group)
{
    CelluleItem *ptc;//pointeur courant pour parcourir la liste
    //initialiser le nouvel élément
    CelluleItem *NE= Init_CelluleItem(label,icon,name,accel_key);
    NE= Creer_CelluleItem(NE,accel_group);//creer le nouvel élément
    if(!Liste_item)//si la liste n'existe pas
        return ((CelluleItem*)NE);//retourner le nouvel élément
    ptc=Liste_item;
    while (ptc->svt)//parcourir la liste jusqu'au dernier élément
        ptc=ptc->svt;//passer à l'élément suivant
    ptc->svt=NE;//lier le nouvel élément à la fin de la liste
    return ((CelluleItem*)Liste_item);
}
/*
 * Fonction qui permet d'insérer un sous menu dans une liste des sous-menus
 * entrées : ->pointeur sur la liste des sous-menus
             ->pointeur sur la liste des éléments
             -> le titre du sous-menu
             -> le nom de l'icône du sous-menu
 * sorties : un pointeur sur la liste des sous-menus
 */
CelluleMenu *Inserer_CeluleMenu(CelluleMenu *Liste_menu,
                                CelluleItem *Liste_item,
                                char label[maxcarac])
{
    CelluleMenu *ptc;//pointeur courant pour parcourir la liste
    //initialiser le nouvel sous-menu
    CelluleMenu *NE= Init_CelluleMenu(Liste_item,label);
    NE= Creer_CelluleMenu(NE);//creer le nouvel sous-menu
    if(!Liste_menu)//si la liste n'existe pas
        return ((CelluleMenu*)NE);
    ptc=Liste_menu;
    while(ptc->svt)//parcourir la liste jusqu'au dernier élément
        ptc=ptc->svt;//passer à l'élément suivant
    ptc->svt=NE;//lier le nouvel élément à la fin de la liste
    return ((CelluleMenu*)Liste_menu);
}
/*
 * Fonction qui permet la création du menu principal
 * entrées : -> pointeur sur la liste des sous-menus
 * sorties : un pointeur sur le menu principal
 */
Menu *Creer_Menu(CelluleMenu *Liste_Menu,int x,int y,
                int orientation)
{
    CelluleMenu *ptc;//pointeur courant pour parcourir la liste
    Menu *NE;//déclaration d'un nouvel menu
    NE=(Menu*)malloc(sizeof (Menu));//allocation de la mémoire
    if(!NE)//vérification de l'allocation
    {
        printf("\nerrur d'allocation !!!!");
        exit(0);
    }
    NE->pos.X=x;
    NE->pos.Y=y;
    NE->liste_menu=Liste_Menu;//initialisation de nouvel menu
    NE->main_menu=gtk_menu_bar_new();//creation du menu
    gtk_menu_bar_set_pack_direction ( NE->main_menu,orientation);
    ptc=Liste_Menu;
    while (ptc)//tant qu'il y a des éléments dans la liste des sous-menus, on les ajoute à notre menu principal
    {
        gtk_menu_shell_append(GTK_MENU_SHELL(NE->main_menu), ptc->sous_menu);
        ptc=ptc->svt;//passer à l'élément suivant
    }
    return ((Menu*)NE);
}
/*
 * Fonction qui permet d'ajouter un sous-menu à un élément quelconque
 * entrées : -> pointeur sur l'élément racine qui va contenir le sous menu
             -> pointeur sur la liste des éléments du sous-menu
 * sorties : un pointeur sur élément après l'ajout du sous-menu
 */
CelluleItem *ajouter_sous_menu(CelluleItem *item,CelluleItem *liste_item)
{
    CelluleItem *ptc;//pointeur courant pour parcourir la liste des éléments
    GtkWidget *smenu;//déclaration d'un pointeur qui va centenir le sous menu
    if(!item)//vérification d'existance de l'élément racine
        return ((CelluleItem *)NULL);
    item->sous_menu=liste_item;//remplir le champ du sous-menu
    smenu=gtk_menu_new();//création du sous-menu

    ptc=item->sous_menu;
    while(ptc)//tant qu'il y a des éléments dans la liste, on les ajoute à notre sous menu
    {
        gtk_menu_shell_append(GTK_MENU_SHELL(smenu), ptc->menu_item);
        ptc=ptc->svt;//passer à l'élément suivant
    }
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(item->menu_item),smenu);
    return ((CelluleItem*)item);
}



#pragma warning(disable: 4996)