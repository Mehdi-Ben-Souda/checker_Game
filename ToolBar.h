//----------------------------------------------------------------------------------------------------------------------
//------------------------------------        structures de données       ----------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
typedef struct to
{
    GtkToolItem *item;//pointeur sur l'élément
    char label[maxcarac];//le titre de l'élément
    char icon[maxcarac];//le nom de l'icône
    GCallback callback;//l'action faite par l'élément
    struct to *svt;//pointeur sur le suivant
}CelluleToolItem;//structure d'un élément du toolbar
typedef struct
{
    GtkWidget *toolbar;//pointeur sur le toolbar
    guint icon_size;//entier indiquant la taille de l'icône
    guint style;//entier indiquant le style des éléments du toolbar
    guint orientation;//entier indiquant l'orientation des éléments du toolbar
    CelluleToolItem *liste_item;//liste des éléments du toolbar
}ToolBar;//structure du toolbar
//----------------------------------------------------------------------------------------------------------------------
//------------------------------------       Fonction supplémentaires      ---------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
/*
 * Fonction qui permet l'initialisation d'un élément du toolbar
 * entrées : -> le titre de l'élément
             -> le nom de l'icône de l'élément
             -> la fonction de rappelle lorsque l'élément est activé
 * sorties : un pointeur sur élément du toolbar après initialisation
 */
CelluleToolItem *Init_CelluleTooolItem( char label[maxcarac], char icon[maxcarac],GCallback callback)
{
    CelluleToolItem *NE;//déclaration d'un nouvel élément
    NE=(CelluleToolItem*)malloc(sizeof (CelluleToolItem));//l'allocation de la mémoire
    if(!NE)//vérification d'allocation
    {
        printf("\nerrur d'allocation !!!!");
        exit(0);
    }
    strcpy(NE->label,label);
    NE->svt=NULL;//pas de suivant
    //Initialisation des champs de la structure
    strcpy(NE->icon,icon);
    NE->callback=callback;
    return ((CelluleToolItem*)NE);
}
/*
 * Fonction qui permet creer un élément du toolbar
 * entrées : -> pointeur sur l'élément
 * sorties : un pointeur sur élément du toolbar après création
 */
CelluleToolItem *Creer_CelluleToolItem(CelluleToolItem *item)
{
    GtkWidget *icon;//variable pour creer l'icône
    if(!item)//vérification d'initialisation de la cellule
        return ((CelluleToolItem*)NULL);
    icon= gtk_image_new_from_file(item->icon);//création de l'icône
    item->item=gtk_tool_button_new(icon,item->label);//création d'élément du toolbar
    g_signal_connect(item->item,"clicked",item->callback,NULL);//lier l'action à l'élément du toolbar
    return ((CelluleToolItem*)item);//retourner l'élément
}
/*
 * Fonction qui permet l'initialisation du toolbar
 * entrées : -> un pointeur sur la liste des éléments construisant le toolbar
             -> la taille de l'icône
             -> le style des éléments du toolbar
             -> l'orientation des éléments du toolbar
 * sorties : un pointeur sur un sous-menu après initialisation
 */
ToolBar *Init_toolbar(CelluleToolItem *liste,guint icon_size,guint style,guint orientation)
{
    ToolBar *NE;//déclaration d'un nouvel élément
    NE=(ToolBar*) malloc(sizeof (ToolBar));//allocation de la mémoire
    if(!NE)
    {
        printf("\nerrur d'allocation !!!!");
        exit(0);
    }//vérification de l'allocation
    //initialisation du nouvel élément
    NE->liste_item=liste;
    NE->icon_size=icon_size;
    NE->style=style;
    NE->orientation=orientation;
    return ((ToolBar*)NE);
}
//----------------------------------------------------------------------------------------------------------------------
//------------------------------------        Fonction prancipales        ----------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
/*
 * Fonction qui permet d'insérer un élément dans une liste des éléments
 * entrées : -> pointeur de type CelluleToolItem
 *           -> le titre de l'élément
             -> le nom de l'icône de l'élément
             -> la fonction de rappelle lorsque l'élément est activé
 * sorties : un pointeur sur la liste des éléments
 */
CelluleToolItem *Inserer_CelluleToolItem(CelluleToolItem *liste,const gchar *label, const gchar *icon,GCallback callback)
{
    CelluleToolItem *NE,*ptc;//pointeur courant pour parcourir la liste
    NE= Init_CelluleTooolItem(label,icon,callback);//initialiser le nouvel élément
    NE= Creer_CelluleToolItem(NE);//creer le nouvel élément
    if(!liste)//si la liste n'existe pas
        return ((CelluleToolItem*)NE);//retourner le nouvel élément
    ptc=liste;
    while(ptc->svt)//parcourir la liste jusqu'au dernier élément
        ptc=ptc->svt;//passer à l'élément suivant
    ptc->svt=NE;//lier le nouvel élément à la fin de la liste
    return ((CelluleToolItem*)liste);
}
/*
 * Fonction qui permet la création du toolbar
 * entrées : -> pointeur sur le toolbar
 * sorties : -> un pointeur sur le toolbar après création
 */
ToolBar *Creer_toolbar(ToolBar *toolbar)
{
    int i=0;//compteur
    CelluleToolItem *ptc;//pointeur courant pour parcourir la liste des éléments
    if(!toolbar)//vérification d'initialisation du toolbar
        return ((ToolBar*)NULL);
    //création du toolbar
    toolbar->toolbar=gtk_toolbar_new();
    gtk_toolbar_set_show_arrow(GTK_TOOLBAR(toolbar->toolbar),FALSE);
    //mettre la taille des éléments
    gtk_toolbar_set_icon_size(GTK_TOOLBAR(toolbar->toolbar),toolbar->icon_size);
    //mettre le style des éléments
    gtk_toolbar_set_style(GTK_TOOLBAR(toolbar->toolbar),toolbar->style);
    //mettre l'orientation des éléments
    gtk_orientable_set_orientation(GTK_ORIENTABLE(toolbar->toolbar),toolbar->orientation);
    ptc=toolbar->liste_item;
    while (ptc)//tant qu'il y a des éléments dans la liste des éléments, on les ajoute à notre toolbar
    {
        gtk_toolbar_insert(GTK_TOOLBAR(toolbar->toolbar),ptc->item,i++);
        ptc=ptc->svt;//passer à l'élément suivant
    }
    return ((ToolBar*)toolbar);
}
