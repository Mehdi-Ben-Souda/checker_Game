#include "common.h"
typedef struct
{
    GtkWidget* combo_box;
    int entry;
    int idElem;//indice dernier element dans le combo box disponible
    coordonne pos;
}comboBox;

/*____________________________________________________________________________

 * Fonction qui permet de creer tous les fils d'une balise
 * entr�es : -> un entier indique si le combo box anec une entree ou non
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
        return (comboBox*)comboB;
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
 * entr�es : -> un combo box
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
 * entr�es : -> un combo box
 *			 -> un entier indique la postion de l'element a supprimer
 * sorties : combobox
 */
comboBox* combo_box_spprimer(comboBox* maComboBox, int position) {
    if (position == -1)
    {
        gtk_combo_box_text_remove_all(GTK_COMBO_BOX_TEXT( maComboBox->combo_box));
        maComboBox->idElem = 0;
    }
    else
    {
        gtk_combo_box_text_remove(maComboBox->combo_box, position);
        maComboBox->idElem--;
    }