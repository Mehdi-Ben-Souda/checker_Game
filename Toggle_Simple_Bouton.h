#pragma once
typedef struct
{
    Boutons* Mabouton;      // champs du bouton
    char name[maxcarac];    // identifiant
    char tooltip[maxcarac]; // le tooltip
    GtkWidget* img;         // l'image
    coordonne size;         // la taille du bouton
    coordonne pos;          // la position du bouton
    char couleur[8];        // Couleur de fond en HEX
    int relief;
} Bouton; // structure d'un simple bouton et d'un toggle bouton
/*
 * Fonction qui permet d'initialiser la structure Bouton
 * entrées : -> le label du bouton
             -> le tooltip
             ->l'image
             ->la taille (Y ,X)
             ->la position (X,Y)
             ->
 * sorties : ->Bouton initialisé
*/
Bouton* Initialiser_boutton(char label[maxcarac],
                            char name[maxcarac],
                            char tooltip[maxcarac],
                            char image[maxcarac],
                            int Y, int X,
                            int rlf, int x, int y, char* couleur, int size_icon)
{
    Bouton* maboutton; // déclaration de variable
    // allocation de la mémoire
    maboutton = (Bouton*)malloc(sizeof(Bouton));
    if (!maboutton) // vérification d'allocation
    {
        printf("Erreur d'allocation !!!");
        exit(0);
    }
    // initialisation des champs de la structure
    maboutton->Mabouton = Initialiser_Boutons(label);
    maboutton->pos.X = x;
    maboutton->pos.Y = y;
    maboutton->size.X = X;
    maboutton->size.Y = Y;
    maboutton->relief = rlf;
    strcpy(maboutton->tooltip, tooltip);
    if (strcmp(image, "vide") != 0) // s'il y a une immage on l'ajout
    {
        GdkPixbuf* pixt;
        // création de l'image
        pixt = gdk_pixbuf_new_from_file_at_size(image, size_icon,
                                                size_icon,
                                                NULL);
        maboutton->img = gtk_image_new_from_pixbuf(pixt);
    }
    else // sinon on met l'image à NULL
        maboutton->img = NULL;
    // Si la couleur n'existe pas , on met "vide" dans
    // le paramatre
    if (!couleur)
    {
        strcpy(maboutton->couleur, "vide");
    }
    else
        // Si non on le met on la couleur dans la structure
        strcpy(maboutton->couleur, couleur);

    if (name)
        strcpy(maboutton->name, name);
    else
        strcpy(maboutton->name, "vide");
    return ((Bouton*)maboutton);
}
/*
 * Fonction qui permet de créer un simple bouton
 * entrées : -> pointeur sur Bouton
 * sorties : ->Bouton crée
 */
Bouton* Creer_SimpleBoutton(Bouton* maboutton)
{
    // s'il existe un label on crée le bouton avec ce label
    if (strcmp(maboutton->Mabouton->label, "vide") != 0)
    {
        maboutton->Mabouton->button = gtk_button_new_with_mnemonic(maboutton->Mabouton->label);
        gtk_button_set_use_underline(GTK_BUTTON(maboutton->Mabouton->button),
                                     TRUE);
    }
    else // sinon on le crée sans label
        maboutton->Mabouton->button = gtk_button_new();
    // mettre la taille du boutton
    gtk_widget_set_size_request(maboutton->Mabouton->button,
                                maboutton->size.Y,
                                maboutton->size.X);
    // si le bouton a un relief on le met
    if (maboutton->relief)
        gtk_button_set_relief(GTK_BUTTON(maboutton->Mabouton->button),
                              GTK_RELIEF_NORMAL);
    else // sinon on le met pas
        gtk_button_set_relief(GTK_BUTTON(maboutton->Mabouton->button),
                              GTK_RELIEF_NONE);
    // si on veut le bouton avoir un tooltip
    if (strcmp(maboutton->tooltip, "vide") != 0)
        gtk_widget_set_tooltip_text(GTK_WIDGET(maboutton->Mabouton->button),
                                    maboutton->tooltip);
    // si on veut une image dans le bouton
    if (maboutton->img)
    {
        gtk_button_set_image(GTK_BUTTON(maboutton->Mabouton->button),
                             maboutton->img);
        gtk_button_set_always_show_image(GTK_BUTTON(maboutton->Mabouton->button),
                                         TRUE);
    }
    if (strcmp("vide", maboutton->couleur) != 0) // Si la couleur existe
    {

        add_bgcolor(maboutton->Mabouton->button, maboutton->couleur, 0.5);
    }
    gtk_widget_set_name(maboutton->Mabouton->button, maboutton->name);
    return ((Bouton*)maboutton);
}
/*
 * Fonction qui permet de créerun toggle bouton
 * entrées : -> pointeur sur Bouton
 * sorties : ->Bouton crée
 */
Bouton* Creer_ToggleBoutton(Bouton* maboutton)
{
    // s'il existe un label on crée le bouton avec ce label
    if (strcmp(maboutton->Mabouton->label, "vide") != 0)
        maboutton->Mabouton->button = gtk_toggle_button_new_with_mnemonic(maboutton->Mabouton->label);
    else // sinon on le crée sans label
        maboutton->Mabouton->button = gtk_toggle_button_new();
    gtk_widget_set_size_request(maboutton->Mabouton->button,
                                maboutton->size.Y,
                                maboutton->size.X);
    if (maboutton->relief) // si le bouton a un relief on le met
        gtk_button_set_relief(GTK_BUTTON(maboutton->Mabouton->button),
                              GTK_RELIEF_NORMAL);
    else // sinon on le met pas
        gtk_button_set_relief(GTK_BUTTON(maboutton->Mabouton->button),
                              GTK_RELIEF_NONE);
    if (strcmp(maboutton->tooltip, "vide") != 0) // si on veut le bouton avoir un tooltip
        gtk_widget_set_tooltip_text(GTK_WIDGET(maboutton->Mabouton->button),
                                    maboutton->tooltip);
    if (maboutton->img) // si on veut une image dans le bouton
    {
        gtk_button_set_image(GTK_BUTTON(maboutton->Mabouton->button),
                             maboutton->img);
        gtk_button_set_always_show_image(GTK_BUTTON(maboutton->Mabouton->button),
                                         TRUE);
    }
    gtk_widget_set_name(maboutton->Mabouton->button, maboutton->name);
    return ((Bouton*)maboutton);
}