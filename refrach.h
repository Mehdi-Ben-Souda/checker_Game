
Bouton* damier[8][8];
pion lespions[NB_PIONS];
match lematch;
int tour = 1, mode = 2, id_pion_selectioner = -1, jeu_complexe_idJ = -1;

void afficher_damier()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            printf("%d \t", lematch.damier[i][j]);
        }
        printf("\n");
    }
}
void CSS(GtkWidget* wdgt)
{
    GtkCssProvider* cssProvider = gtk_css_provider_new();

    gtk_css_provider_load_from_path(cssProvider, "C:\\Users\\HP FOLIO 9470m\\OneDrive\\Bureau\\chabab_GTK\\chabab_GTK\\style.css", NULL);

    // Apply the CSS provider to the button widget
    GtkStyleContext* styleContext = gtk_widget_get_style_context(wdgt);
    gtk_style_context_add_provider(styleContext,
                                   GTK_STYLE_PROVIDER(cssProvider),
                                   GTK_STYLE_PROVIDER_PRIORITY_USER);
}

/*
typedef struct infoA
{
    pion lespions[NB_PIONS];

    match lematch;
}All_info;

All_info* cree_All_info()
{
    All_info* elem = (All_info*)malloc(sizeof(All_info));
    if (!elem)
    {
        printf("\nErreur d'allocation !!");
        exit(0);
    }
    Initialiser_Damier(&elem->lematch.damier);
    Initialiser_Tab_Pion(elem->lespions);
    return((elem*)elem);
}*/

void show_mouve(GtkWidget* widget, int id)
{

    noeud* nd = NULL;
    char* name = NULL;

    // nd = nd->svt;
    // printf("%d \t %d \t", nd->lejeu->x, nd->lejeu->x);
    // while (nd)
    //{
    // char* name = gtk_widget_get_name(damier[3][4]);
    // gtk_widget_set_name(damier[3][4], "mvt_possible");
    // CSS(damier[3][4]);
    // }

    printf(" \n idselectioner %d", id);

    switch (mode)
    {
    case 1:
        break;
    case 2:

        switch (tour)
        {
        case -1:
            if (id < 12)
            {
                if (jeu_complexe_idJ >= 0)
                {
                    nd = tousLesMouvementsJetton(id, lematch.damier, lespions, 0);
                    if (jeu_complexe_idJ == id)
                    {

                        for (int i = 0; i < 8; i++)
                        {
                            for (int j = 0; j < 8; j++)
                            {
                                char* name = gtk_widget_get_name(damier[i][j]->Mabouton->button);
                                if (!strcmp(name, "mvt_possible") || !strcmp(name, "autre_mvt_possible"))
                                {
                                    gtk_widget_set_name(damier[i][j]->Mabouton->button, "my-button_black");
                                    CSS(damier[i][j]->Mabouton->button);
                                }
                                if (!strcmp(name, "pion_selected"))
                                {
                                    gtk_widget_set_name(damier[i][j]->Mabouton->button, "joueur2");
                                    CSS(damier[i][j]->Mabouton->button);
                                }
                            }
                        }
                        while (nd)
                        {

                            if (nd->lejeu)
                            {

                                if (nd->lejeu->IDa >= 0)
                                {
                                    afficher_damier();
                                    printf("\n id adv %d", nd->lejeu->IDa);
                                    gtk_widget_set_name(damier[nd->lejeu->y][nd->lejeu->x]->Mabouton->button, "mvt_possible");
                                    CSS(damier[nd->lejeu->y][nd->lejeu->x]->Mabouton->button);
                                    g_signal_connect(damier[nd->lejeu->y][nd->lejeu->x]->Mabouton->button, "clicked", G_CALLBACK(make_mouve), nd->lejeu);
                                    set_name_autre_mvt_possible(nd->lejeu->gch);
                                    set_name_autre_mvt_possible(nd->lejeu->drt);
                                }
                            }
                            nd = nd->svt;
                        }
                        id_pion_selectioner = id;
                        gtk_widget_set_name(widget, "pion_selected");
                        CSS(widget);
                    }
                }
                else
                {
                    nd = tousLesMouvementsJetton(id, lematch.damier, lespions, 0);

                    for (int i = 0; i < 8; i++)
                    {
                        for (int j = 0; j < 8; j++)
                        {
                            char* name = gtk_widget_get_name(damier[i][j]->Mabouton->button);
                            if (!strcmp(name, "mvt_possible") || !strcmp(name, "autre_mvt_possible"))
                            {
                                gtk_widget_set_name(damier[i][j]->Mabouton->button, "my-button_black");
                                CSS(damier[i][j]->Mabouton->button);
                            }
                            if (!strcmp(name, "pion_selected"))
                            {
                                gtk_widget_set_name(damier[i][j]->Mabouton->button, "joueur2");
                                CSS(damier[i][j]->Mabouton->button);
                            }
                        }
                    }
                    while (nd)
                    {

                        if (nd->lejeu)
                        {
                            gtk_widget_set_name(damier[nd->lejeu->y][nd->lejeu->x]->Mabouton->button, "mvt_possible");
                            CSS(damier[nd->lejeu->y][nd->lejeu->x]->Mabouton->button);
                            g_signal_connect(damier[nd->lejeu->y][nd->lejeu->x]->Mabouton->button, "clicked", G_CALLBACK(make_mouve), nd->lejeu);
                            set_name_autre_mvt_possible(nd->lejeu->gch);
                            set_name_autre_mvt_possible(nd->lejeu->drt);
                        }
                        nd = nd->svt;
                    }
                    id_pion_selectioner = id;
                    gtk_widget_set_name(widget, "pion_selected");
                    CSS(widget);
                }
            }
            else
            {
                // name = gtk_widget_get_name()
            }
            break;
        case 1:
            if (id > 11)
            {
                if (jeu_complexe_idJ >= 0)
                {
                    nd = tousLesMouvementsJetton(id, lematch.damier, lespions, 0);
                    if (jeu_complexe_idJ == id)
                    {

                        for (int i = 0; i < 8; i++)
                        {
                            for (int j = 0; j < 8; j++)
                            {
                                char* name = gtk_widget_get_name(damier[i][j]->Mabouton->button);
                                if (!strcmp(name, "mvt_possible") || !strcmp(name, "autre_mvt_possible"))
                                {
                                    gtk_widget_set_name(damier[i][j]->Mabouton->button, "my-button_black");
                                    CSS(damier[i][j]->Mabouton->button);
                                }
                                if (!strcmp(name, "pion_selected"))
                                {
                                    gtk_widget_set_name(damier[i][j]->Mabouton->button, "joueur1");
                                    CSS(damier[i][j]->Mabouton->button);
                                }
                            }
                        }
                        while (nd)
                        {

                            if (nd->lejeu)
                            {

                                if (nd->lejeu->IDa >= 0)
                                {
                                    afficher_damier();
                                    printf("\n id adv %d", nd->lejeu->IDa);
                                    gtk_widget_set_name(damier[nd->lejeu->y][nd->lejeu->x]->Mabouton->button, "mvt_possible");
                                    CSS(damier[nd->lejeu->y][nd->lejeu->x]->Mabouton->button);
                                    g_signal_connect(damier[nd->lejeu->y][nd->lejeu->x]->Mabouton->button, "clicked", G_CALLBACK(make_mouve), nd->lejeu);
                                    set_name_autre_mvt_possible(nd->lejeu->gch);
                                    set_name_autre_mvt_possible(nd->lejeu->drt);
                                }
                            }
                            nd = nd->svt;
                        }
                        id_pion_selectioner = id;
                        gtk_widget_set_name(widget, "pion_selected");
                        CSS(widget);
                    }
                }
                else
                {
                    nd = tousLesMouvementsJetton(id, lematch.damier, lespions, 0);

                    for (int i = 0; i < 8; i++)
                    {
                        for (int j = 0; j < 8; j++)
                        {
                            char* name = gtk_widget_get_name(damier[i][j]->Mabouton->button);
                            if (!strcmp(name, "mvt_possible") || !strcmp(name, "autre_mvt_possible"))
                            {
                                gtk_widget_set_name(damier[i][j]->Mabouton->button, "my-button_black");
                                CSS(damier[i][j]->Mabouton->button);
                            }
                            if (!strcmp(name, "pion_selected"))
                            {
                                gtk_widget_set_name(damier[i][j]->Mabouton->button, "joueur1");
                                CSS(damier[i][j]->Mabouton->button);
                            }
                        }
                    }
                    while (nd)
                    {

                        if (nd->lejeu)
                        {
                            gtk_widget_set_name(damier[nd->lejeu->y][nd->lejeu->x]->Mabouton->button, "mvt_possible");
                            CSS(damier[nd->lejeu->y][nd->lejeu->x]->Mabouton->button);
                            g_signal_connect(damier[nd->lejeu->y][nd->lejeu->x]->Mabouton->button, "clicked", G_CALLBACK(make_mouve), nd->lejeu);
                            set_name_autre_mvt_possible(nd->lejeu->gch);
                            set_name_autre_mvt_possible(nd->lejeu->drt);
                        }
                        nd = nd->svt;
                    }
                    id_pion_selectioner = id;
                    gtk_widget_set_name(widget, "pion_selected");
                    CSS(widget);
                }
            }
            else
            {
                // name = gtk_widget_get_name()
            }
            break;
        default:
            return;
            break;
        }
        break;
    default:
        break;
    }
}