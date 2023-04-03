#pragma once
//----------------------------------------------------------------------------------------------------------------------
//------------------------------------        structures de données       ----------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
typedef struct to
{
    GtkToolItem *item;//pointeur sur l'élément
    char label[NB_Cara_titre];//le titre de l'élément
    char icon[NB_Cara_chemin];//le nom de l'icône
}ToolItem;//structure d'un élément du toolbar
typedef struct
{
    GtkWidget *toolbar;//pointeur sur le toolbar
    guint icon_size;//entier indiquant la taille de l'icône
    guint style;//entier indiquant le style des éléments du toolbar
    guint orientation;//entier indiquant l'orientation des éléments du toolbar
    coordonne x_y;//position du toolbar
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
ToolItem *Init_CelluleTooolItem( char label[NB_Cara_titre], char icon[NB_Cara_chemin])
{
    ToolItem *NE;//déclaration d'un nouvel élément
    NE=(ToolItem*)malloc(sizeof (ToolItem));//l'allocation de la mémoire
    if(!NE)//vérification d'allocation
    {
        printf("\nerreur d'allocation !!!!");
        exit(0);
    }
    strcpy(NE->label,label);
    //Initialisation des champs de la structure
    NE->item=NULL;
    strcpy(NE->icon,icon);
    return ((ToolItem*)NE);
}
/*
 * Fonction qui permet creer un élément du toolbar
 * entrées : -> pointeur sur l'élément
 * sorties : un pointeur sur élément du toolbar après création
 */
ToolItem *Creer_CelluleToolItem(ToolItem *item)
{
    GtkWidget *icon;//variable pour creer l'icône
    if(!item)//vérification d'initialisation de la cellule
        return ((ToolItem*)NULL);
    icon= gtk_image_new_from_file(item->icon);//création de l'icône
    item->item=gtk_tool_button_new(icon,item->label);//création d'élément du toolbar
    return ((ToolItem*)item);//retourner l'élément
}
/*
 * Fonction qui permet l'initialisation du toolbar
 * entrées : -> un pointeur sur la liste des éléments construisant le toolbar
             -> la taille de l'icône
             -> le style des éléments du toolbar
             -> l'orientation des éléments du toolbar
             -> la position du toolbar selon les absices
             -> la position du toplbar selon les ordonees
 * sorties : un pointeur sur un sous-menu après initialisation
 */
ToolBar *Init_toolbar(guint icon_size,guint style,guint orientation,
                      int x , int y)
{
    ToolBar *NE;//déclaration d'un nouvel élément
    NE=(ToolBar*) malloc(sizeof (ToolBar));//allocation de la mémoire
    if(!NE)
    {
        printf("\nerrur d'allocation !!!!");
        exit(0);
    }//vérification de l'allocation
    //initialisation du nouvel élément
    NE->icon_size=icon_size;
    NE->style=style;
    NE->orientation=orientation;
    NE->x_y.X = x;
    NE->x_y.Y = y;
    return ((ToolBar*)NE);
}
//----------------------------------------------------------------------------------------------------------------------
//------------------------------------        Fonction prancipales        ----------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
/*
 * Fonction qui permet la création du toolbar
 * entrées : -> pointeur sur le toolbar
 * sorties : -> un pointeur sur le toolbar après création
 */
ToolBar *Creer_toolbar(ToolBar *toolbar)
{
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
    return ((ToolBar*)toolbar);
}
/*
 * Fonction qui permet d'insérer un toolitem dans une toolbar
 * entrées : -> pointeur sur le toolbar
             ->pointeur sur le tool item
             ->compteur de l'ordre du tool item
 * sorties : -> le tool item inséré dans le toolbar
 */
void Inserer_Tool_Item(GtkWidget *toolbar,ToolItem *item, int *compt)
{
    //test d'existance des widgets
    if(!toolbar || !item)
        exit(-2) ;
    //insertion du tool item dan le toolbar
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar),item->item, *compt++);
}
