/*-----------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------   RADIO  BOUTTON    ---------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------*/
typedef struct bt
{
    Boutons *Mabouton;
    struct bt *svt;
}CelluleBouton;
typedef struct
{
    CelluleBouton *MesBoutons;
    Box *groupe;
    coordonne pos;
}RadioCheckBouttons;
CelluleBouton *Creer_Cellule_CHBouton(char label[maxcarac])
{
    CelluleBouton *NE;
    NE=(CelluleBouton*) malloc(sizeof (CelluleBouton));
    if(!NE)
    {
        printf("Erreur d'allocation !!!");
        exit(0);
    }
    NE->Mabouton= Initialiser_Boutons(label);
    if(strcmp(label,"vide")!=0)
        NE->Mabouton->button=gtk_check_button_new_with_mnemonic(label);
    else
        NE->Mabouton->button=gtk_check_button_new();
    NE->svt=NULL;
    return ((CelluleBouton*)NE);
}
CelluleBouton *Creer_Cellule_RBouton(char label[maxcarac],GtkWidget *groupe)
{
    CelluleBouton *NE;
    NE=(CelluleBouton*) malloc(sizeof (CelluleBouton));
    if(!NE)
    {
        printf("Erreur d'allocation !!!");
        exit(0);
    }
    NE->Mabouton= Initialiser_Boutons(label);
    if(groupe)
        NE->Mabouton->button=gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(groupe),NE->Mabouton->label);
    else
        NE->Mabouton->button=gtk_radio_button_new_with_label(NULL,NE->Mabouton->label);
    NE->svt=NULL;
    return ((CelluleBouton*)NE);
}
CelluleBouton *Inserer_Bouton(CelluleBouton *Maliste,char type,char label[maxcarac])
{
    CelluleBouton *NE;
    CelluleBouton *ptcourant;
    switch (type) {
        case 'c':
            NE= Creer_Cellule_CHBouton(label);
            if(!Maliste)
                return NE;
            break;
        case 'r':
            if(!Maliste)
            {
                NE=Creer_Cellule_RBouton(label,NULL);
                return((CelluleBouton*)NE);
            }
            NE= Creer_Cellule_RBouton(label,Maliste->Mabouton->button);
            break;
        default:
            printf("\nundefined type !! ");
            exit(-1);
    }
    ptcourant=Maliste;
    while (ptcourant->svt)           // tant qu'on n'est pas arrivé à la dernière cellule
        ptcourant = ptcourant->svt;  // parcourir la liste
    ptcourant->svt = NE;  // insérer le nouvel élément
    return ((CelluleBouton*)Maliste);
}
RadioCheckBouttons *Crerr_Radio_Check_Boutons(CelluleBouton *Maliste,int x,int y,int orientation,int spacing)
{
    RadioCheckBouttons *NE;
    CelluleBouton *ptc;
    NE=(RadioCheckBouttons*) malloc(sizeof (RadioCheckBouttons));
    if(!NE)
    {
        printf("Erreur d'allocation !!!");
        exit(0);
    }

    NE->pos.X=x;
    NE->pos.Y=y;
    NE->groupe= Allouer_Box(orientation,spacing);
    Creer_Box(NE->groupe,NULL);
    ptc=Maliste;
    while (ptc)
    {
        Ajouter_Box(NE->groupe,ptc->Mabouton->button,0,0.0,0,0);
        ptc=ptc->svt;
    }
    return ((RadioCheckBouttons*)NE);
}