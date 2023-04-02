/*-----------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------    BOUTONS    -----------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------*/
typedef struct
{
    int largeur;//largeur du bouton
    int longueur;//longueur du bouton
}Taille;
typedef struct
{
    GtkWidget *button;//pointeur sur un bouton
    char label[maxcarac];//le nom du bouton
}Boutons;
Boutons *Initialiser_Boutons(char label[maxcarac])
{
    Boutons *NE= (Boutons*)malloc(sizeof (Boutons));
    if(!NE)
    {
        printf("Erreur d'allocation !!!");
        exit(0);
    }
    strcpy(NE->label,label);
    NE->button=NULL;
    return ((Boutons*)NE);
}
