#include <gtk/gtk.h>


/*-----------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------    position    -----------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------*/

typedef struct crd
{
    int X;
    int Y;
}coordonne;



/*-----------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------    BOUTTON    -----------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------*/
typedef struct
{
    GtkWidget* button;//pointeur sur un boutton
    char* label;//le nom du boutton
    char* tooltip;
    GtkWidget* img;
    int largeur;//largeur du button
    int longueur;//longueur du boutton
    int relief;
    coordonne pos;
}Boutton;//structure d'un boutton
Boutton* Initialiser_boutton(char* label, char* tooltip, char* image, int largeur, int longueur, int rlf, int x, int y)
{
    Boutton* maboutton = NULL;
    maboutton = (Boutton*)malloc(sizeof(Boutton));
    maboutton->longueur = longueur;
    maboutton->largeur = largeur;
    maboutton->relief = rlf;
    maboutton->pos.X = x;
    maboutton->pos.Y = y;

    maboutton->label = label;
    maboutton->tooltip = tooltip;
    if (image)
    {
        GdkPixbuf* pixt = gdk_pixbuf_new_from_file_at_size(image, maboutton->largeur, maboutton->longueur, NULL);
        maboutton->img = gtk_image_new_from_pixbuf(pixt);
    }
    else
    {
        maboutton->img = NULL;
    }

    return ((Boutton*)maboutton);
}
Boutton* creer_boutton(Boutton* maboutton)
{
    if (maboutton->label)
    {
        maboutton->button = gtk_button_new_with_mnemonic(maboutton->label);
        gtk_button_set_use_underline(GTK_BUTTON(maboutton->button), TRUE);
    }
    else
    {
        maboutton->button = gtk_button_new();
    }

    gtk_widget_set_size_request(maboutton->button,
        maboutton->largeur, maboutton->longueur);

    if (maboutton->relief)
        gtk_button_set_relief(GTK_BUTTON(maboutton->button), GTK_RELIEF_NORMAL);
    else
        gtk_button_set_relief(GTK_BUTTON(maboutton->button), GTK_RELIEF_NONE);

    if (maboutton->tooltip)
        gtk_widget_set_tooltip_text(GTK_BUTTON(maboutton->button), maboutton->tooltip);

    if (maboutton->img)
    {
        gtk_button_set_image(GTK_BUTTON(maboutton->button), maboutton->img);
        gtk_button_set_always_show_image(GTK_BUTTON(maboutton->button), TRUE);
    }

    return ((Boutton*)maboutton);
}

/*-----------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------  TOGGELE  BOUTTON    -----------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------*/
typedef struct
{
    GtkWidget* toggel_btn;//pointeur sur un boutton
    char* label;//le nom du boutton
    char* tooltip;
    GtkWidget* img;
    int largeur;//largeur du button
    int longueur;//longueur du boutton
    int relief;
    coordonne pos;
}toggele_Boutton;//structure d'un boutton


toggele_Boutton* Initialiser_toggle_boutton(char* label, char* tooltip, char* image, int largeur, int longueur, int rlf, int x, int y)
{
    toggele_Boutton* maboutton = NULL;
    maboutton = (toggele_Boutton*)malloc(sizeof(toggele_Boutton));
    maboutton->longueur = longueur;
    maboutton->largeur = largeur;
    maboutton->relief = rlf;
    maboutton->pos.X = x;
    maboutton->pos.Y = y;

    maboutton->label = label;
    maboutton->tooltip = tooltip;
    if (image)
    {
        GdkPixbuf* pixt = gdk_pixbuf_new_from_file_at_size(image, maboutton->largeur, maboutton->longueur, NULL);
        maboutton->img = gtk_image_new_from_pixbuf(pixt);
    }
    else
    {
        maboutton->img = NULL;
    }

    return ((toggele_Boutton*)maboutton);
}
toggele_Boutton* creer_toggle_boutton(toggele_Boutton* maboutton)
{
    if (maboutton->label)
        maboutton->toggel_btn = gtk_toggle_button_new_with_mnemonic(maboutton->label);
    else
    {
        maboutton->toggel_btn = gtk_toggle_button_new();
    }

    gtk_widget_set_size_request(maboutton->toggel_btn,
        maboutton->largeur, maboutton->longueur);

    if (maboutton->relief)
        gtk_button_set_relief(GTK_TOGGLE_BUTTON(maboutton->toggel_btn), GTK_RELIEF_NORMAL);
    else
        gtk_button_set_relief(GTK_TOGGLE_BUTTON(maboutton->toggel_btn), GTK_RELIEF_NONE);

    if (maboutton->tooltip)
        gtk_widget_set_tooltip_text(GTK_TOGGLE_BUTTON(maboutton->toggel_btn), maboutton->tooltip);



    if (maboutton->img)
    {
        gtk_button_set_image(GTK_TOGGLE_BUTTON(maboutton->toggel_btn), maboutton->img);
        gtk_button_set_always_show_image(GTK_TOGGLE_BUTTON(maboutton->toggel_btn), TRUE);
    }
    return ((toggele_Boutton*)maboutton);
}
