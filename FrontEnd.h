#pragma once
#include "FrontEndDefintion.h"

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

/*
    Nom Fonction : CSS

    Entree : _ un element de type GtkWidget

    Sortie : _Rien

    Description : L'utilite de cette fct c'est qu'elle applique
            un CSS sur le widget passer en parametre
*/

void CSS(GtkWidget* wdgt)
{
    GtkCssProvider* cssProvider = gtk_css_provider_new();

    gtk_css_provider_load_from_path(cssProvider, "style.css", NULL);

    // Apply the CSS provider to the button widget
    GtkStyleContext* styleContext = gtk_widget_get_style_context(wdgt);
    gtk_style_context_add_provider(styleContext,
                                   GTK_STYLE_PROVIDER(cssProvider),
                                   GTK_STYLE_PROVIDER_PRIORITY_USER);
}

/*
    Nom Fonction : show_mouve

    Entree : _ un element de type GtkWidget
             _ l'id d'un pion
             _

    Sortie : _Rien

    Description : L'utilite de cette fct c'est qu'elle montre les chemin possible
                    d'un pion
*/
void show_mouve(GtkWidget* widget, int id)
{

    noeud* nd = NULL;
    char* name = (char)malloc(sizeof(char*));
    mouvement* ptr = NULL;

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
                    nd = Mouvements_Possibles(id, lematch.damier, lespions);

                    if (jeu_complexe_idJ == id)
                    {

                        for (int i = 0; i < 8; i++)
                        {
                            for (int j = 0; j < 8; j++)
                            {

                                name = gtk_widget_get_name(damier[i][j]->Mabouton->button);
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
                            ptr = nd->lejeu;
                            while (ptr)
                            {

                                if (ptr->IDa >= 0)
                                {
                                    printf("\n");
                                    Afficher_Damier(lematch.damier);
                                    printf("\n");
                                    Afficher_Arbre_horizotalement(ptr, 3);
                                    printf("\n");
                                    printf("\n id adv %d", ptr->IDa);
                                    gtk_widget_set_name(damier[ptr->y][ptr->x]->Mabouton->button, "mvt_possible");
                                    CSS(damier[ptr->y][ptr->x]->Mabouton->button);
                                    g_signal_connect(damier[ptr->y][ptr->x]->Mabouton->button, "clicked", G_CALLBACK(make_mouve), ptr);
                                    set_name_autre_mvt_possible(ptr->fils1);
                                    set_name_autre_mvt_possible(ptr->fils2);
                                }

                                ptr = ptr->fils3;
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
                    nd = Mouvements_Possibles(id, lematch.damier, lespions);

                    for (int i = 0; i < 8; i++)
                    {
                        for (int j = 0; j < 8; j++)
                        {
                            name = gtk_widget_get_name(damier[i][j]->Mabouton->button);
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
                        ptr = nd->lejeu;
                        while (ptr)
                        {
                            printf("\n");
                            Afficher_Damier(lematch.damier);
                            printf("\n");
                            Afficher_Arbre_horizotalement(ptr, 3);
                            printf("\n");
                            gtk_widget_set_name(damier[ptr->y][ptr->x]->Mabouton->button, "mvt_possible");
                            CSS(damier[ptr->y][ptr->x]->Mabouton->button);
                            g_signal_connect(damier[ptr->y][ptr->x]->Mabouton->button, "clicked", G_CALLBACK(make_mouve), ptr);
                            set_name_autre_mvt_possible(ptr->fils1);
                            set_name_autre_mvt_possible(ptr->fils2);
                            ptr = ptr->fils3;
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
                    nd = Mouvements_Possibles(id, lematch.damier, lespions);
                    if (jeu_complexe_idJ == id)
                    {

                        for (int i = 0; i < 8; i++)
                        {
                            for (int j = 0; j < 8; j++)
                            {
                                name = gtk_widget_get_name(damier[i][j]->Mabouton->button);
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
                            ptr = nd->lejeu;
                            while (ptr)
                            {

                                if (ptr->IDa >= 0)
                                {
                                    printf("\n");
                                    Afficher_Damier(lematch.damier);
                                    printf("\n");
                                    Afficher_Arbre_horizotalement(ptr, 3);
                                    printf("\n");
                                    printf("\n id adv %d", ptr->IDa);
                                    gtk_widget_set_name(damier[ptr->y][ptr->x]->Mabouton->button, "mvt_possible");
                                    CSS(damier[ptr->y][ptr->x]->Mabouton->button);
                                    g_signal_connect(damier[ptr->y][ptr->x]->Mabouton->button, "clicked", G_CALLBACK(make_mouve), ptr);
                                    set_name_autre_mvt_possible(ptr->fils1);
                                    set_name_autre_mvt_possible(ptr->fils2);
                                }

                                ptr = ptr->fils3;
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
                    nd = Mouvements_Possibles(id, lematch.damier, lespions);

                    for (int i = 0; i < 8; i++)
                    {
                        for (int j = 0; j < 8; j++)
                        {
                            name = gtk_widget_get_name(damier[i][j]->Mabouton->button);
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
                        ptr = nd->lejeu;
                        while (ptr)
                        {
                            printf("\n");
                            Afficher_Damier(lematch.damier);
                            printf("\n");
                            Afficher_Arbre_horizotalement(ptr, 3);
                            printf("\n");
                            gtk_widget_set_name(damier[ptr->y][ptr->x]->Mabouton->button, "mvt_possible");
                            CSS(damier[ptr->y][ptr->x]->Mabouton->button);
                            g_signal_connect(damier[ptr->y][ptr->x]->Mabouton->button, "clicked", G_CALLBACK(make_mouve), ptr);
                            set_name_autre_mvt_possible(ptr->fils1);
                            set_name_autre_mvt_possible(ptr->fils2);
                            ptr = ptr->fils3;
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

/*
    Nom Fonction : make_mouve

    Entree : _ un element de type GtkWidget
             _ le mouvement appliquer
             _

    Sortie : _Rien

    Description : L'utilite de cette fct c'est qu'elle applique
            un mouvement d'un pion
*/

void make_mouve(GtkWidget* widget, mouvement* mvt)
{
    printf(" \n %d  --  %d", id_pion_selectioner, mvt->IDj);
    char* name = (char)malloc(sizeof(char*));
    name = gtk_widget_get_name(widget);
    GdkPixbuf* pixt = NULL;
    GtkWidget* img = NULL;

    if (!strcmp(name, "mvt_possible") && (id_pion_selectioner == mvt->IDj))
    {

        if (mvt->IDj > 11)
        {
            if (lespions[mvt->IDj].etat == 2)
            {
                pixt = gdk_pixbuf_new_from_file_at_size("black_pionDame.png", 50, 50, NULL);
            }
            else
            {
                pixt = gdk_pixbuf_new_from_file_at_size("white_pion.png", 50, 50, NULL);
            }
        }

        else
        {
            if (lespions[mvt->IDj].etat == 2)
            {
                pixt = gdk_pixbuf_new_from_file_at_size("white_pionDame.png", 50, 50, NULL);
            }
            else
            {
                pixt = gdk_pixbuf_new_from_file_at_size("black_pion.png", 50, 50, NULL);
            }
        }

        img = gtk_image_new_from_pixbuf(pixt);
        gtk_button_set_image(GTK_BUTTON(widget), img);
        gtk_button_set_image(GTK_BUTTON(damier[lespions[mvt->IDj].y][lespions[mvt->IDj].x]->Mabouton->button), NULL);
        gtk_button_set_always_show_image(widget, TRUE);
        g_signal_handlers_block_matched(widget,
                                        G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)make_mouve, NULL);

        if (mvt->IDa >= 0)
        {
            printf("\npos adv %d   &&   %d id %d\n", lespions[mvt->IDa].y, lespions[mvt->IDa].x, mvt->IDa);
            gtk_button_set_image(GTK_BUTTON(damier[lespions[mvt->IDa].y][lespions[mvt->IDa].x]->Mabouton->button), NULL);
            gtk_widget_set_name(damier[lespions[mvt->IDa].y][lespions[mvt->IDa].x]->Mabouton->button, "my-button_black");
            CSS(damier[lespions[mvt->IDa].y][lespions[mvt->IDa].x]->Mabouton->button);
            g_signal_handlers_block_matched(damier[lespions[mvt->IDa].y][lespions[mvt->IDa].x]->Mabouton->button,
                                            G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)show_mouve, NULL);
        }

        printf("\npos jr %d   &&   %d \n", lespions[mvt->IDj].y, lespions[mvt->IDj].x);
        gtk_widget_set_name(damier[lespions[mvt->IDj].y][lespions[mvt->IDj].x]->Mabouton->button, "my-button_black");
        CSS(damier[lespions[mvt->IDj].y][lespions[mvt->IDj].x]->Mabouton->button);
        g_signal_handlers_block_matched(damier[lespions[mvt->IDj].y][lespions[mvt->IDj].x]->Mabouton->button,
                                        G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)show_mouve, NULL);

        if (mvt->IDj > 11)
            gtk_widget_set_name(widget, "joueur1");
        else
            gtk_widget_set_name(widget, "joueur2");
        CSS(widget);

        deplacerJeton(mvt, lematch.damier, lespions);

        if (lespions[mvt->IDj].etat == 2)
        {
            if (mvt->IDj > 11)
                pixt = gdk_pixbuf_new_from_file_at_size("white_pionDame.png", 50, 50, NULL);
            else
                pixt = gdk_pixbuf_new_from_file_at_size("black_pionDame.png", 50, 50, NULL);
            img = gtk_image_new_from_pixbuf(pixt);
            gtk_button_set_image(GTK_BUTTON(widget), img);
        }

        afficher_damier();
        if (mvt->fils1 || mvt->fils2 || mvt->fils3)
        {
            printf("\n??? encore a jouer \n");
            if (mvt->fils1)
                printf("\n )))))) fils1 ((((((\n");
            if (mvt->fils2)
                printf("\n)))))) fils2 ((((((\n");
            if (mvt->fils3)
                printf("\n)))))) fils3 (((((( \n");
            jeu_complexe_idJ = mvt->IDj;
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
                }
            }

            show_mouve(widget, mvt->IDj);
        }
        else
        {
            if (jeu_complexe_idJ >= 0)
            {
                jeu_complexe_idJ = -1;
            }
        }

        if (jeu_complexe_idJ < 0)
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
                }
            }
            g_signal_connect(widget, "clicked", G_CALLBACK(show_mouve), mvt->IDj);
            id_pion_selectioner = -1;
            jeu_complexe_idJ = -1;
            tour = tour * (-1);
            printf(">>>> FIN DE TOUR <<<<<");
        }
    }
    else
    {
        printf("\n error : Y %d X %d", mvt->y, mvt->x);
    }
}

/*
    Nom Fonction : set_name_autre_mvt_possible

    Entree : _ une structure mouvement

    Sortie : _Rien

    Description : cette fonction sert a donner le nom de 'autre_mvt_possible'
    pour tous les widget dont leur position est dans la structure mouvement,
    cette fonnction elle va nous aider a faire un css pour ces widgets
*/

void set_name_autre_mvt_possible(mouvement* mvt)
{
    if (mvt)
    {
        gtk_widget_set_name(damier[mvt->y][mvt->x]->Mabouton->button, "autre_mvt_possible");
        CSS(damier[mvt->y][mvt->x]->Mabouton->button);
        if (mvt->fils1)
            set_name_autre_mvt_possible(mvt->fils1);
        if (mvt->fils2)
            set_name_autre_mvt_possible(mvt->fils2);
    }
}

void on_button_clicked1(GtkWidget* widget, Fenetre* new)
{
    afficher_fenetre(new->ma_fenetre);
}
void on_bouton_clicked(GtkWidget* widget, Dialog* MonDialogue)
{
    Afficher_dialogue(MonDialogue);
}
void dialogue_action(GtkWidget* widget, Dialog* MonDialogue)
{
    g_signal_connect(widget, "clicked", G_CALLBACK(on_bouton_clicked), MonDialogue);
}

/*
    Nom Fonction : page_damier

    Entree : _ Rien
    Sortie : _ Rien

    Description : cette fonction sert a construire une page de damier

*/

void page_damier()
{
    Fenetre* wind;

    wind = Allouer_Fenetre(0, 1600, 900, "Jeu Damier", NULL, 200, 0, "#FF5733", "window", 1);
    wind = Creer_Fenetre(wind);
    CSS(wind->ma_fenetre);
    Fixed* fixed = Allouer_fixed("fixed");
    frame *frame1, *profil, *addimg;
    Box *B1, *B2, *B3, *B4, *B5, *b1, *b2, *b3, *b4;
    Label* mylabel;

    //-------------------------------------  Fixed       -------------------------------------------------

    //-------------------------------------    Simple boutton     --------------------------------------------------
    Bouton* rejouer = Initialiser_boutton("Rejouer", NULL, "Voulez vous répéter?", "", 350, 40, 1, 1300, 350, "vide", 0);
    rejouer = Creer_SimpleBoutton(rejouer);
    Ajouter_Fixed(rejouer->Mabouton->button, rejouer->pos.X, rejouer->pos.Y, fixed);

    Bouton* regle_jeu = Initialiser_boutton("Regles de jeu", NULL, "découvrir les règles de jeu ", "", 350, 40, 1, 1300, 450, "vide", 0);
    regle_jeu = Creer_SimpleBoutton(regle_jeu);
    Ajouter_Fixed(regle_jeu->Mabouton->button, regle_jeu->pos.X, regle_jeu->pos.Y, fixed);

    Bouton* help = Initialiser_boutton("Help", NULL, "", "", 350, 40, 1, 1300, 550, "vide", 0);
    help = Creer_SimpleBoutton(help);
    Ajouter_Fixed(help->Mabouton->button, help->pos.X, help->pos.Y, fixed);
    //-------------------------------------    Le dialogue     --------------------------------------------------
    Dialog* mondialog = Init_Dialog("zrferg", "Do you want to leave this match ? ", "E:\\chabab_GTK\\icons\\accepter.png");

    /*---------------------ajouter boutons simples dans une frame-----------------*/

    frame1 = Init_frame("", "name", 20, 1280, 670, 50, 70);
    Creation_frame(frame1);
    Ajouter_Fixed(frame1->monframe, frame1->pos.X, frame1->pos.Y, fixed);

    Bouton* re = Initialiser_boutton("", NULL, "", "C:\\Users\\HP FOLIO 9470m\\OneDrive\\Bureau\\trash\\chabab_GTK\\chabab_GTK\\icons\\qutter_exporter.png", 80, 20, 1, 1500, 400, "vide", 30);
    re = Creer_SimpleBoutton(re);
    Creer_Dialog(mondialog);
    dialogue_action(re->Mabouton->button, mondialog);
    // Afficher_dialogue(mondialog);

    Bouton* btn1 = Initialiser_boutton("", NULL, "", "C:\\Users\\lenovoi\\CLionProjects\\chabab_GTK\\icons\\reload.png", 80, 20, 1, 1500, 400, "vide", 80);
    btn1 = Creer_SimpleBoutton(btn1);

    Bouton* btn2 = Initialiser_boutton("", NULL, "", "C:\\Users\\lenovoi\\CLionProjects\\chabab_GTK\\icons\\pause.png", 80, 20, 1, 1500, 400, "vide", 80);
    btn2 = Creer_SimpleBoutton(btn2);

    Bouton* btn3 = Initialiser_boutton("", NULL, "", "C:\\Users\\lenovoi\\CLionProjects\\chabab_GTK\\icons\\play.png", 80, 20, 1, 1500, 400, "vide", 80);
    btn3 = Creer_SimpleBoutton(btn3);

    B1 = Allouer_Box(1, 5);
    Creer_Box(B1, frame1->monframe);
    B2 = Allouer_Box(0, 5);
    Creer_Box(B2, B1->mon_box);
    B3 = Allouer_Box(0, 5);
    Creer_Box(B3, B1->mon_box);
    B4 = Allouer_Box(0, 5);
    Creer_Box(B4, B1->mon_box);
    B5 = Allouer_Box(0, 5);
    Creer_Box(B5, B1->mon_box);

    Ajouter_Box(B2, re->Mabouton->button, 0, TRUE, TRUE, 5);
    Ajouter_Box(B2, btn1->Mabouton->button, 0, TRUE, TRUE, 5);
    Ajouter_Box(B2, btn2->Mabouton->button, 0, TRUE, TRUE, 5);
    Ajouter_Box(B2, btn3->Mabouton->button, 0, TRUE, TRUE, 5);

    b1 = Allouer_Box(1, 5);
    b2 = Allouer_Box(0, 5);
    Creer_Box(b2, b1->mon_box);
    if (mode == 1)
        mylabel = Init_label("Machine Vs Joueur", "framePr", 1330, 200);
    else
        mylabel = Init_label("Joueur Vs Joueur", "framePr", 1330, 200);

    Ajouter_Fixed(mylabel->leLabel, mylabel->X_Y.X, mylabel->X_Y.Y, GTK_FIXED(fixed));
    CSS(mylabel->leLabel);

    /*-----------------------------------image----------------------------------------------*/
    /*
    GtkWidget* image1 = gtk_image_new_from_file("C:\\Users\\lenovoi\\CLionProjects\\chabab_GTK\\icons\\chessboard.png");
    Ajouter_Fixed(image1, 1430, 130, fixed);
    GtkWidget* image2 = gtk_image_new_from_file("C:\\Users\\lenovoi\\CLionProjects\\chabab_GTK\\icons\\chessboard.png");
    Ajouter_Fixed(image2, 1650, 130, fixed);*/
    /*-------------------------------------nouvelle fenetre---------------------------*/
    GtkWidget* label;

    label = gtk_label_new("choisis ton mode de jeu !");

    Fenetre* nouvfen;
    // Fixed* fixed = Allouer_fixed("fixed");
    Label* label1;
    nouvfen = Allouer_Fenetre(0, 500, 500, "choix", "C:\\Users\\lenovoi\\CLionProjects\\chabab_GTK\\icons\\home.png", 200, 0, NULL, "titre1", 1);
    nouvfen = Creer_Fenetre(nouvfen);
    Fixed* fixed1 = Allouer_fixed("fixed");
    label1 = Init_label("coisis ton mode", "label", 500, 100);
    Ajouter_Fixed(label1->leLabel, label1->X_Y.X, label1->X_Y.Y, fixed1);
    Ajouter_fenetre(nouvfen, fixed1->mon_fixed);
    // Bouton* bouton = Initialiser_boutton("choix", NULL, "", "C:\\Users\\lenovoi\\CLionProjects\\chabab_GTK\\icons\\qutter_exporter.png", 80, 20, 1, 1500, 50, "vide", 15);
    // bouton = Creer_SimpleBoutton(bouton);
    // Ajouter_Fixed(bouton->Mabouton->button, bouton->pos.X, bouton->pos.Y, fixed);
    // g_signal_connect(bouton->Mabouton->button, "clicked", G_CALLBACK(Signal_afficher_fenetre), nouvfen->ma_fenetre);
    //----------------------------------------------------------------------------------------------------------------------
    //-------------------------------------     Création de la fenêtre    --------------------------------------------------

    //+++++++++++++++ login page++++++++++++++++++++++
    /* Fenetre* login_wind;

    login_wind = Allouer_Fenetre(0, 1600, 900, "Jeu Damier", NULL, 200, 0, "#FF5733", "login_window", 0);
    login_wind = Creer_Fenetre(login_wind);
*/
    // ++++++++++++++++++++++damier++++++++++++++++++++++

    int ligne = 400, colonne = 140, sizeBTN = 80, size_icon = 50;
    char icon_pion[NB_Cara_titre], name[NB_Cara_titre];

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            damier[i][j] = NULL;
        }
    }

    for (int i = 0; i < 8; i++)
    {
        ligne = 400;
        strcpy(icon_pion, "vide");

        for (int j = 0; j < 8; j++)
        {

            if ((i % 2) == 0)
            {
                if ((j % 2) == 0)
                    strcpy(name, "my-button_gold");
                else
                    strcpy(name, "my-button_black");
            }
            else
            {
                if ((j % 2) == 0)
                    strcpy(name, "my-button_black");
                else
                    strcpy(name, "my-button_gold");
            }

            strcpy(icon_pion, "vide");

            if (i <= 2)
            {
                if ((i % 2) == 0)
                {
                    if ((j % 2) != 0)
                    {
                        strcpy(icon_pion, "black_pion.png");
                    }
                }
                else
                {
                    if ((j % 2) == 0)
                    {
                        strcpy(icon_pion, "black_pion.png");
                    }
                }
            }
            if (i >= 5)
            {
                if (i % 2 == 0)
                {
                    if (j % 2 != 0)
                    {
                        strcpy(icon_pion, "white_pion.png");
                    }
                }
                else
                {
                    if (j % 2 == 0)
                    {
                        strcpy(icon_pion, "white_pion.png");
                    }
                }
            }
            damier[i][j] = Initialiser_boutton("", name, "", icon_pion, sizeBTN, sizeBTN, 0, ligne, colonne, NULL, size_icon);
            damier[i][j] = Creer_SimpleBoutton(damier[i][j]);

            // add_bgcolor(GTK_WIDGET(damier[i][j]->Mabouton->button), "#bb8141", 1);
            //++++++ CSS++++++
            CSS(damier[i][j]->Mabouton->button);
            Ajouter_Fixed(damier[i][j]->Mabouton->button, damier[i][j]->pos.X, damier[i][j]->pos.Y, GTK_FIXED(fixed));
            ligne = ligne + sizeBTN;
        }
        colonne = colonne + sizeBTN;
    }

    //++++++++++++++++++++++++++++++score++++++++++++++++++

    Label *scoreMachine, *scoreJoueur;
    scoreJoueur = Init_label("Score : 0000 ", "score_Joueur", 400, 50);
    scoreMachine = Init_label("Score : 0000 ", "score_Machine", 400, 800);
    Ajouter_Fixed(scoreJoueur->leLabel, scoreJoueur->X_Y.X, scoreJoueur->X_Y.Y, GTK_FIXED(fixed));
    Ajouter_Fixed(scoreMachine->leLabel, scoreMachine->X_Y.X, scoreMachine->X_Y.Y, GTK_FIXED(fixed));
    CSS(scoreJoueur->leLabel);
    CSS(scoreMachine->leLabel);

    Ajouter_fenetre(wind, fixed->mon_fixed);
    // Affichage de la fenêtre
    afficher_fenetre(wind->ma_fenetre);
}

/*
    Nom Fonction : jeu_commence

    Entree : _ Rien

    Sortie : _Rien

    Description : cette fonction sert a declancher un jeu de damier
*/

void jeu_commence()
{

    Initialiser_Damier(&lematch.damier);
    Initialiser_Tab_Pion(lespions);

    page_damier();
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (lematch.damier[i][j] >= 0)
            {
                g_signal_connect(damier[i][j]->Mabouton->button, "clicked", G_CALLBACK(show_mouve), lematch.damier[i][j]);
                CSS(damier[i][j]->Mabouton->button);
                if (lematch.damier[i][j] > 11)
                    gtk_widget_set_name(damier[i][j]->Mabouton->button, "joueur1");
                else
                    gtk_widget_set_name(damier[i][j]->Mabouton->button, "joueur2");
            }
        }
    }
}

void what_btn(GtkWidget* widget, GtkWidget* widget2)
{
    gboolean active = gtk_toggle_button_get_active(widget);

    char* label = gtk_widget_get_name(GTK_BUTTON(widget));
    if (active)
    {
        if (!strcmp(label, "btn_mode1"))
            mode = 1;
        else
            mode = 2;
        gtk_toggle_button_set_active(widget2, FALSE);
    }

    // fenetre_destroy(fen->ma_fenetre);
    // jeu_commence();
}

/*
    Nom Fonction : Mode_page

    Entree : _ Rien
    Sortie : _Rien

    Description : la fonction qui sert a  fair la construction d'une page mode
    (la page ou l'utilisateur choisit quelle mode de jeu)
*/

void Mode_page()
{
    Fenetre* fenetre_mode;
    fenetre_mode = Allouer_Fenetre(0, 1300, 900, "Jeu damier", NULL, 300, 0, NULL, "fenetre_mode", 0);
    fenetre_mode = Creer_Fenetre(fenetre_mode);
    CSS(fenetre_mode->ma_fenetre);

    Fixed* fixed = Allouer_fixed("fixed");
    frame* frame1;
    Box* B1;

    // Afficher_dialogue(mondialog);
    frame1 = Init_frame("MODE", "frameMode", 20, 180, 270, 450, 470);
    Creation_frame(frame1);
    CSS(frame1->monframe);

    Bouton* btn1 = Initialiser_boutton("Joueur   VS   Machine", "btn_mode1", "", "", 380, 106, 1, 1500, 400, "vide", 80);
    btn1 = Creer_ToggleBoutton(btn1);
    CSS(btn1->Mabouton->button);

    Bouton* btn2 = Initialiser_boutton("Joueur   VS   Joueur", "btn_mode2", "", "", 380, 106, 1, 1500, 400, "vide", 80);
    btn2 = Creer_ToggleBoutton(btn2);
    CSS(btn2->Mabouton->button);

    g_signal_connect(btn2->Mabouton->button, "clicked", G_CALLBACK(what_btn), btn1->Mabouton->button);
    g_signal_connect(btn1->Mabouton->button, "clicked", G_CALLBACK(what_btn), btn2->Mabouton->button);

    Bouton* btn3 = Initialiser_boutton("Quitter", "btn_mode_quitter", "", "", 380, 106, 1, 1500, 400, "vide", 80);
    btn3 = Creer_SimpleBoutton(btn3);
    CSS(btn3->Mabouton->button);
    g_signal_connect(btn3->Mabouton->button, "clicked", G_CALLBACK(signal_fenetre_destroy), fenetre_mode->ma_fenetre);

    B1 = Allouer_Box(1, 20);
    Creer_Box(B1, NULL);
    gtk_widget_set_name(B1->mon_box, "BoxMode");
    CSS(B1->mon_box);

    Label* title_mode;
    title_mode = Init_label("MODE ", "title_mode", 400, 50);
    CSS(title_mode->leLabel);
    Ajouter_Box(B1, title_mode->leLabel, 0, FALSE, FALSE, 0);
    Ajouter_Box(B1, btn1->Mabouton->button, 0, FALSE, FALSE, 0);
    Ajouter_Box(B1, btn2->Mabouton->button, 0, FALSE, FALSE, 0);
    Ajouter_Box(B1, btn3->Mabouton->button, 0, FALSE, FALSE, 0);

    Ajouter_Fixed(B1->mon_box, 400, 200, fixed);
    Ajouter_fenetre(fenetre_mode, fixed->mon_fixed);
    afficher_fenetre(fenetre_mode->ma_fenetre);
}
