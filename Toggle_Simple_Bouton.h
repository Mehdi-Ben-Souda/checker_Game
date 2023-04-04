#pragma once
#include "Boutons.h"
typedef struct
{
    Boutons *Mabouton;
    char name[NB_Cara_titre];
    char tooltip[NB_Cara_titre];
    GtkWidget *img;
    Taille size;
    coordonne pos;
    int relief;
}Bouton;//structure d'un simple bouton et d'un toggle bouton
Bouton * Initialiser_boutton(char label[NB_Cara_titre],
                             char tooltip[NB_Cara_titre],
                             char image[NB_Cara_chemin],
                             int largeur,int longueur,
                             int rlf,int x, int y)
{
    Bouton *maboutton=NULL;
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



typedef struct
{
    GtkWidget* combo_box;
    int entry;
    int idElem;//indice dernier element dans le combo box disponible
    coordonne pos;
}comboBox;

/*____________________________________________________________________________

 * Fonction qui permet de creer tous les fils d'une balise
 * entrées : -> un entier indique si le combo box anec une entree ou non
 *			 -> deux entier pour la position
 * sorties : combobox
 */
comboBox* creer_combo_Box(int entry,int X,int Y)
{
    comboBox* comboB=NULL;
    //l'allocation de la memeoire
    comboB = (comboBox*)malloc(sizeof(comboB));
    if (!comboB)
    {
        printf("!!!\nErreur dans l'Allocation de la fenetre!!!\n");
        return (Fenetre*)comboB;
    }
    comboB->entry = entry;
    comboB->pos.X = X;
    comboB->pos.Y = Y;
    comboB->idElem = 0;
    //tester si combo box sera sans entree
    if (!entry){
        //creation de combo box sans entree
        comboB->combo_box = gtk_combo_box_text_new();
        printf("\n ComboBox creer\n");
    }
    else{
        //creation de combo box avec entree
        comboB->combo_box = gtk_combo_box_text_new_with_entry();
        printf("\n ComboBox creer\n");
       }
    return ((comboBox*)comboB);
}
/*____________________________________________________________________________

 * Fonction qui permet de creer tous les fils d'une balise
 * entrées : -> un combo box
 *			 -> un entier indique la postion ou on va inserer
 *           ->la valeur a inserer
 *           ->un id pour la valeur a inserer
 * sorties : combobox
 */
comboBox* combo_box_inserer(comboBox* maComboBox, int position, char* valeur, char* id) {
    if (position == -1)
        gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(maComboBox->combo_box), id, valeur);
    else
        gtk_combo_box_text_insert(GTK_COMBO_BOX_TEXT(maComboBox->combo_box), position, id, valeur);
    maComboBox->idElem++;
    return ((comboBox*)maComboBox);
}

/*____________________________________________________________________________

 * Fonction qui permet de creer tous les fils d'une balise
 * entrées : -> un combo box
 *			 -> un entier indique la postion de l'element a supprimer
 * sorties : combobox
 */
comboBox* combo_box_spprimer(comboBox* maComboBox, int position) {
    if (position == -1)
    {
        gtk_combo_box_text_remove_all(maComboBox->combo_box);
        maComboBox->idElem = 0;
    }
    else
    {
        gtk_combo_box_text_remove(maComboBox->combo_box, position);
        maComboBox->idElem--;
    }

    return ((Fenetre*)maComboBox);
}