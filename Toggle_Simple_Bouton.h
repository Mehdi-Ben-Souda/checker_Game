typedef struct
{
    Boutons *Mabouton;
    char name[maxcarac];
    char tooltip[maxcarac];
    GtkWidget *img;
    Taille size;
    coordonne pos;
    int relief;
}Bouton;//structure d'un simple bouton et d'un toggle bouton
Bouton * Initialiser_boutton(char label[maxcarac],
                             char tooltip[maxcarac],
                             char image[maxcarac],
                             int largeur,int longueur,
                             int rlf,int x, int y)
{
    Bouton *maboutton;
    maboutton = (Bouton *)malloc(sizeof(Bouton));
    maboutton->Mabouton= Initialiser_Boutons(label);
    maboutton->pos.X=x;
    maboutton->pos.Y=y;
    maboutton->size.longueur = longueur;
    maboutton->size.largeur = largeur;
    maboutton->relief = rlf;
    strcpy(maboutton->tooltip,tooltip);
    if (strcmp(image,"vide")!=0)
    {
        GdkPixbuf* pixt;
        pixt= gdk_pixbuf_new_from_file_at_size(image,
                                                           maboutton->size.largeur,
                                                           maboutton->size.longueur,
                                                           NULL);
        maboutton->img = gtk_image_new_from_pixbuf(pixt);
    }
    else
        maboutton->img = NULL;
    return ((Bouton *)maboutton);
}
Bouton* Creer_SimpleBoutton(Bouton* maboutton)
{
    if (strcmp(maboutton->Mabouton->label,"vide")!=0)
    {
        maboutton->Mabouton->button = gtk_button_new_with_mnemonic(maboutton->Mabouton->label);
        gtk_button_set_use_underline(GTK_BUTTON(maboutton->Mabouton->button),
                                     TRUE);
    }
    else
        maboutton->Mabouton->button = gtk_button_new();

    gtk_widget_set_size_request(maboutton->Mabouton->button,
                                maboutton->size.largeur,
                                maboutton->size.longueur);
    if (maboutton->relief)
        gtk_button_set_relief(GTK_BUTTON(maboutton->Mabouton->button),
                              GTK_RELIEF_NORMAL);
    else
        gtk_button_set_relief(GTK_BUTTON(maboutton->Mabouton->button),
                              GTK_RELIEF_NONE);

    if (strcmp(maboutton->tooltip,"vide")!=0)
        gtk_widget_set_tooltip_text(GTK_WIDGET(maboutton->Mabouton->button),
                                    maboutton->tooltip);
    if (maboutton->img)
    {
        gtk_button_set_image(GTK_BUTTON(maboutton->Mabouton->button),
                             maboutton->img);
        gtk_button_set_always_show_image(GTK_BUTTON(maboutton->Mabouton->button),
                                         TRUE);
    }
    return ((Bouton *)maboutton);
}
Bouton * Creer_ToggleBoutton(Bouton* maboutton)
{
    if (strcmp(maboutton->Mabouton->label,"vide")!=0)
        maboutton->Mabouton->button = gtk_toggle_button_new_with_mnemonic(maboutton->Mabouton->label);
    else
        maboutton->Mabouton->button = gtk_toggle_button_new();
    gtk_widget_set_size_request(maboutton->Mabouton->button,
                                maboutton->size.largeur,
                                maboutton->size.longueur);

    if (maboutton->relief)
        gtk_button_set_relief(GTK_BUTTON(maboutton->Mabouton->button),
                              GTK_RELIEF_NORMAL);
    else
        gtk_button_set_relief(GTK_BUTTON(maboutton->Mabouton->button),
                              GTK_RELIEF_NONE);

    if (strcmp(maboutton->tooltip,"vide")!=0)
        gtk_widget_set_tooltip_text(GTK_WIDGET(maboutton->Mabouton->button),
                                    maboutton->tooltip);
    if (maboutton->img)
    {
        gtk_button_set_image(GTK_BUTTON(maboutton->Mabouton->button),
                             maboutton->img);
        gtk_button_set_always_show_image(GTK_BUTTON(maboutton->Mabouton->button),
                                         TRUE);
    }
    return ((Bouton *)maboutton);
}