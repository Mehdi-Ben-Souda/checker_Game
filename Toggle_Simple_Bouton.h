typedef struct
{
    Boutons *Mabouton;//champs du bouton
    char name[maxcarac];//identifiant
    char tooltip[maxcarac];//le tooltip
    GtkWidget *img;//l'image
    Taille size;//la taille du bouton
    coordonne pos;//la position du bouton
    int relief;
}Bouton;//structure d'un simple bouton et d'un toggle bouton
/*
 * Fonction qui permet d'initialiser la structure Bouton
 * entrées : -> le label du bouton
             -> le tooltip
             ->l'image
             ->la taille (largeur ,longueur)
             ->la position (X,Y)
             ->
 * sorties : ->Bouton initialisé
*/
Bouton * Initialiser_boutton(char label[maxcarac],
                             char tooltip[maxcarac],
                             char image[maxcarac],
                             int largeur,int longueur,
                             int rlf,int x, int y)
{
    Bouton *maboutton;//déclaration de variable
    //allocation de la mémoire
    maboutton = (Bouton *)malloc(sizeof(Bouton));
    if(!maboutton)//vérification d'allocation
    {
        printf("Erreur d'allocation !!!");
        exit(0);
    }
    //initialisation des champs de la structure
    maboutton->Mabouton= Initialiser_Boutons(label);
    maboutton->pos.X=x;
    maboutton->pos.Y=y;
    maboutton->size.longueur = longueur;
    maboutton->size.largeur = largeur;
    maboutton->relief = rlf;
    strcpy(maboutton->tooltip,tooltip);
    if (strcmp(image,"vide")!=0)//s'il y a une immage on l'ajout
    {
        GdkPixbuf* pixt;
        //création de l'image
        pixt= gdk_pixbuf_new_from_file_at_size(image,maboutton->size.largeur,
                                               maboutton->size.longueur,
                                               NULL);
        maboutton->img = gtk_image_new_from_pixbuf(pixt);
    }
    else //sinon on met l'image à NULL
        maboutton->img = NULL;
    return ((Bouton *)maboutton);
}
/*
 * Fonction qui permet de créer un simple bouton
 * entrées : -> pointeur sur Bouton
 * sorties : ->Bouton crée
*/
Bouton* Creer_SimpleBoutton(Bouton* maboutton)
{
    //s'il existe un label on crée le bouton avec ce label
    if (strcmp(maboutton->Mabouton->label,"vide")!=0)
    {
        maboutton->Mabouton->button = gtk_button_new_with_mnemonic(maboutton->Mabouton->label);
        gtk_button_set_use_underline(GTK_BUTTON(maboutton->Mabouton->button),
                                     TRUE);
    }
    else //sinon on le crée sans label
        maboutton->Mabouton->button = gtk_button_new();
    //mettre la taille du boutton
    gtk_widget_set_size_request(maboutton->Mabouton->button,
                                maboutton->size.largeur,
                                maboutton->size.longueur);
    //si le bouton a un relief on le met
    if (maboutton->relief)
        gtk_button_set_relief(GTK_BUTTON(maboutton->Mabouton->button),
                              GTK_RELIEF_NORMAL);
    else //sinon on le met pas
        gtk_button_set_relief(GTK_BUTTON(maboutton->Mabouton->button),
                              GTK_RELIEF_NONE);
    //si on veut le bouton avoir un tooltip
    if (strcmp(maboutton->tooltip,"vide")!=0)
        gtk_widget_set_tooltip_text(GTK_WIDGET(maboutton->Mabouton->button),
                                    maboutton->tooltip);
    //si on veut une image dans le bouton
    if (maboutton->img)
    {
        gtk_button_set_image(GTK_BUTTON(maboutton->Mabouton->button),
                             maboutton->img);
        gtk_button_set_always_show_image(GTK_BUTTON(maboutton->Mabouton->button),
                                         TRUE);
    }
    return ((Bouton *)maboutton);
}
/*
 * Fonction qui permet de créerun toggle bouton
 * entrées : -> pointeur sur Bouton
 * sorties : ->Bouton crée
*/
Bouton * Creer_ToggleBoutton(Bouton* maboutton)
{
    //s'il existe un label on crée le bouton avec ce label
    if (strcmp(maboutton->Mabouton->label,"vide")!=0)
        maboutton->Mabouton->button = gtk_toggle_button_new_with_mnemonic(maboutton->Mabouton->label);
    else //sinon on le crée sans label
        maboutton->Mabouton->button = gtk_toggle_button_new();
    gtk_widget_set_size_request(maboutton->Mabouton->button,
                                maboutton->size.largeur,
                                maboutton->size.longueur);
    if (maboutton->relief)//si le bouton a un relief on le met
        gtk_button_set_relief(GTK_BUTTON(maboutton->Mabouton->button),
                              GTK_RELIEF_NORMAL);
    else//sinon on le met pas
        gtk_button_set_relief(GTK_BUTTON(maboutton->Mabouton->button),
                              GTK_RELIEF_NONE);
    if (strcmp(maboutton->tooltip,"vide")!=0)//si on veut le bouton avoir un tooltip
        gtk_widget_set_tooltip_text(GTK_WIDGET(maboutton->Mabouton->button),
                                    maboutton->tooltip);
    if (maboutton->img)//si on veut une image dans le bouton
    {
        gtk_button_set_image(GTK_BUTTON(maboutton->Mabouton->button),
                             maboutton->img);
        gtk_button_set_always_show_image(GTK_BUTTON(maboutton->Mabouton->button),
                                         TRUE);
    }
    return ((Bouton *)maboutton);
}
