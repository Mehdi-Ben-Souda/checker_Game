/*-----------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------    BOUTONS    -----------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------*/
#pragma once
typedef struct
{
    int largeur;//largeur du bouton
    int longueur;//longueur du bouton
}Taille;
typedef struct
{
    GtkWidget *button;//pointeur sur un bouton
    char label[NB_Cara_titre];//le nom du bouton
}Boutons;//structure commun entre tous les boutons
/*
 * Fonction qui permet d'initialiser la structure Boutons
 * entrées : -> le label du bouton
 * sorties : ->Bouton initialisé
*/
Boutons *Initialiser_Boutons(char label[NB_Cara_titre])
{
    //allocation de la mémoire
    Boutons *NE= (Boutons*)malloc(sizeof (Boutons));
    if(!NE)//vérification d'allocation
    {
        printf("Erreur d'allocation !!!");
        exit(0);
    }
    //initialistation des champs du structure
    strcpy(NE->label,label);
    NE->button=NULL;
    return ((Boutons*)NE);
}
