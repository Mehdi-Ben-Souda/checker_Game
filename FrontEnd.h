#pragma once
#include "FrontEndDefintion.h"
#include "minmax.h"
// Déclaration des variables
Bouton* damier[8][8];
pion lespions[NB_PIONS];
match lematch;
int tour = 1, mode = 1, id_pion_selectioner = -1, jeu_complexe_idJ = -1,
    dernierePosY = -1, dernierePosX = -1;

int nfikh = 0, colorJeton = 1;
Label *scoreJoueur1, *scoreJoueur2;

/*
    Nom Fonction : clr_choisis

    Entree : _ un entier

    Sortie : _un pointeur de type char

    Description : retourne une chaîne de caractères correspondant
    au nom du fichier image pour le jeton d'une case donnée, en fonction
    de la couleur du jeton (colorJeton).
*/
char* clr_choisis(int i)
{
    // tour du joueur 2
    if (colorJeton == 1)
    {
        /*
         Si i est égal à 0, cela signifie que le jeton est un pion noir.
        Si i est égal à 1, cela signifie que le jeton est un pion blanc.
        Si i est égal à 2, cela signifie que le jeton est une dame blanche.
        Si i est égal à 3, cela signifie que le jeton est une dame noire.
         */
        if (i == 0)
            return "black_pion.png";
        // joueur1
        if (i == 1)
            return "white_pion.png";
        if (i == 2)
            return "white_pionDame.png";
        if (i == 3)
            return "black_pionDame.png";
    }
    else // tour du joueur 1
    {
        /*
        Si i est égal à 0, cela signifie que le jeton est un pion blanc.
       Si i est égal à 1, cela signifie que le jeton est un pion noire.
       Si i est égal à 2, cela signifie que le jeton est une dame noire.
       Si i est égal à 3, cela signifie que le jeton est une dame blanc.
        */
        if (i == 0)
            return "white_pion.png";
        if (i == 1)
            return "black_pion.png";
        if (i == 2)
            return "black_pionDame.png";
        if (i == 3)
            return "white_pionDame.png";
    }
    return NULL;
}

/*
    Nom Fonction : MiseAJourScore

    Entree : _ deux entiers
    Sortie : Void

    Description :La fonction MiseAJourScore met à jour le score du joueur
    en fonction de l'identifiant (id) et de la valeur du score à ajouter (s).
*/
void MiseAJourScore(int id, int s)
{
    // Déclaration des variables
    const char* texteScore;
    long scoreActuel;
    char nouveauScore[25];
    if (id > 11) // s'il s'agit du joueur 2
    {
        // récuperer le label
        texteScore = gtk_label_get_text(GTK_LABEL(scoreJoueur2->leLabel));
        // convertir le texte récupérer
        scoreActuel = strtol(texteScore, NULL, 10);
        // ajouter à la valeur actuel du score la nouvelle valeur
        scoreActuel += s;
        sprintf(nouveauScore, " %04ld ", scoreActuel);
        gtk_label_set_text(GTK_LABEL(scoreJoueur2->leLabel), nouveauScore);
    }
    else // s'il s'agit du joueur 1
    {
        // récuperer le label
        texteScore = gtk_label_get_text(GTK_LABEL(scoreJoueur1->leLabel));
        // convertir le texte récupérer
        scoreActuel = strtol(texteScore, NULL, 10);
        // ajouter à la valeur actuel du score la nouvelle valeur
        scoreActuel += s;
        sprintf(nouveauScore, " %04ld ", scoreActuel);
        gtk_label_set_text(GTK_LABEL(scoreJoueur1->leLabel), nouveauScore);
    }
}

/*
    Nom Fonction : on_rejouer_clicked

    Entree : _ deux Widget
    Sortie : Void

    Description :La fonction détruit la fenêtre passée en paramètre (fen)
    et réinitialise différentes variables utilisées dans le jeu.
*/
void on_rejouer_clicked(GtkWidget* widget, GtkWidget* fen)
{
    // Détruire la fenetre
    gtk_widget_destroy(fen);
    // Initialisation des variables
    tour = 1;
    id_pion_selectioner = -1;
    jeu_complexe_idJ = -1;
    dernierePosY = -1;
    dernierePosX = -1;
    nfikh = 0;
    // Appel à la fonction jeu_commence
    jeu_commence(NULL, NULL);
}
/*
void on_regle_jeu_clicked(GtkWidget* widget, gpointer data)
{
    Fenetre* fen = Allouer_Fenetre(0, 1300, 900, "Règles de jeu", NULL, 300, 0, NULL, "fenetre_mode", 0);
    fen = Creer_Fenetre(fen);
    Fixed* fixed = Allouer_fixed("fixed");
    Ajouter_fenetre(fen, fixed->mon_fixed);
    Box* B1;
    GtkWidget* label = gtk_label_new(
        "Règles du jeu : \n-Les pions se déplacent en diagonale \n- Les pions avancent d'une case à la fois...\n- Lorsqu'un pion capture un pion adverse, il peut sauter au-dessus...\n- Les pions ne peuvent pas reculer...\n- Si un pion arrive sur la dernière rangée du côté de l’adversaire, il est promu en dame...\n- Si un pion a l’opportunité de capturer un pion de l’adversaire et ne la capture pas lui-même, il va être capturé\n-Une dame peut se déplacer en diagonale dans toutes les directions, en avant et en arrière, et peut avancer de plusieurs cases à la fois.");
    Bouton* btn3 = Initialiser_boutton("Quitter", "btn_mode_quitter", "", "", 380, 106, 1, 1500, 400, "vide", 80);
    btn3 = Creer_SimpleBoutton(btn3);
    CSS(btn3->Mabouton->button);
    g_signal_connect(btn3->Mabouton->button, "clicked", G_CALLBACK(signal_fenetre_destroy), fen->ma_fenetre);
    B1 = Allouer_Box(1, 5);
    Creer_Box(B1, 0);
    Ajouter_Box(B1, label, 0, FALSE, FALSE, 0);
    Ajouter_Box(B1, btn3->Mabouton->button, 0, FALSE, FALSE, 0);
    Ajouter_Fixed(B1->mon_box, 400, 200, fixed);
    afficher_fenetre(fen->ma_fenetre);
}
*/
/*
    Nom Fonction : tour_de_machine

    Entree : _ Void
    Sortie : Void

    Description :La fonction tour_de_machine représente le tour
    de jeu de l'ordinateur. Elle effectue une série d'opérations
    pour afficher les mouvements possibles de l'ordinateur
    et mettre à jour le damier, les jetons et le score en conséquence.
*/
void tour_de_machine()
{
    // Déclaration des variables
    GdkPixbuf* pixt = NULL;
    GtkWidget* img = NULL;
    char* name = (char*)malloc(sizeof(char));
    if (!name)
    {
        printf("Erreur d'allocation");
        exit(0);
    }
    // Création de l'arbre de Minmax
    noeud* nd = creerArbre_MiniMax(lematch.damier, lespions, 2);
    // Initialisation des variables etatJoueur à -1 et id_nfikh à -1.
    int etatJoueur = -1, id_nfikh = -1;
    mouvement* ptr = NULL;
    ptr = nd->lejeu;
    // Déclaration d'un tableau damierCpy de taille NB_CASES x NB_CASES.
    int damierCpy[NB_CASES][NB_CASES];
    // Déclaration d'un tableau pionCpy de taille NB_PIONS.
    pion pionCpy[NB_PIONS];
    if (ptr) // Si ptr n'est pas NULL, cela signifie que l'arbre contient des mouvements valides
    {
        // Sauvegarde de l'état actuel du damier et des pions dans les tableaux de copie damierCpy et pionCpy.
        copierDamier(damierCpy, lematch.damier);
        copierLesJetons(pionCpy, lespions);
        /*Parcours du damier avec une boucle for imbriquée pour
         réinitialiser les noms et les styles des boutons des cases du damier*/
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                name = gtk_widget_get_name(damier[i][j]->Mabouton->button);
                if (!strcmp(name, "mvt_possible") || !strcmp(name, "autre_mvt_possible") || !strcmp(name, "my-button_black_nfikh"))
                {
                    gtk_widget_set_name(damier[i][j]->Mabouton->button, "my-button_black");
                    CSS(damier[i][j]->Mabouton->button);
                }
            }
        } // Sauvegarde de l'état du joueur actuel dans etatJoueur
        etatJoueur = lespions[ptr->IDj].etat;
        while (ptr)
        {
            gtk_widget_set_name(damier[ptr->y][ptr->x]->Mabouton->button, "mvt_possible");
            CSS(damier[ptr->y][ptr->x]->Mabouton->button);

            gtk_widget_set_name(damier[lespions[ptr->IDj].y][lespions[ptr->IDj].x]->Mabouton->button, "mvt_possible");
            CSS(damier[lespions[ptr->IDj].y][lespions[ptr->IDj].x]->Mabouton->button);

            printf("\n x : %d y : %d Ida : %d", ptr->x, ptr->y, ptr->IDa);
            printf("\n");
            if (lespions[nd->lejeu->IDj].etat == 1)
                pixt = gdk_pixbuf_new_from_file_at_size(clr_choisis(0), 50, 50, NULL);
            else
                pixt = gdk_pixbuf_new_from_file_at_size(clr_choisis(3), 50, 50, NULL);
            img = gtk_image_new_from_pixbuf(pixt);
            gtk_button_set_image(GTK_BUTTON(damier[lespions[ptr->IDj].y][lespions[ptr->IDj].x]->Mabouton->button), NULL);
            g_signal_handlers_block_matched(damier[lespions[ptr->IDj].y][lespions[ptr->IDj].x]->Mabouton->button,
                                            G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)make_mouve, NULL);
            g_signal_handlers_block_matched(damier[lespions[ptr->IDj].y][lespions[ptr->IDj].x]->Mabouton->button,
                                            G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)show_mouve, NULL);
            gtk_button_set_image(damier[ptr->y][ptr->x]->Mabouton->button, img);
            gtk_button_set_always_show_image(damier[ptr->y][ptr->x]->Mabouton->button, TRUE);

            if (ptr->IDa >= 0)
            {
                nfikh++;
                gtk_button_set_image(damier[lespions[ptr->IDa].y][lespions[ptr->IDa].x]->Mabouton->button, NULL);
                g_signal_handlers_block_matched(damier[lespions[ptr->IDa].y][lespions[ptr->IDa].x]->Mabouton->button,
                                                G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)make_mouve, NULL);
                g_signal_handlers_block_matched(damier[lespions[ptr->IDa].y][lespions[ptr->IDa].x]->Mabouton->button,
                                                G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)show_mouve, NULL);
                gtk_widget_set_name(damier[lespions[ptr->IDa].y][lespions[ptr->IDa].x]->Mabouton->button, "mvt_possible");
                CSS(damier[lespions[ptr->IDa].y][lespions[ptr->IDa].x]->Mabouton->button);
                if (lespions[nd->lejeu->IDa].etat == 1)
                    MiseAJourScore(nd->lejeu->IDj, 10);
                else
                    MiseAJourScore(nd->lejeu->IDj, 40);
            }
            deplacerJeton(ptr, lematch.damier, lespions);
            ptr = ptr->fils1;
        }
        if (etatJoueur != lespions[nd->lejeu->IDj].etat && lespions[nd->lejeu->IDj].etat == 2)
        {
            pixt = gdk_pixbuf_new_from_file_at_size(clr_choisis(3), 50, 50, NULL);
            img = gtk_image_new_from_pixbuf(pixt);
            gtk_button_set_image(GTK_BUTTON(damier[lespions[nd->lejeu->IDj].y][lespions[nd->lejeu->IDj].x]->Mabouton->button), img);
            gtk_button_set_always_show_image(damier[lespions[nd->lejeu->IDj].y][lespions[nd->lejeu->IDj].x]->Mabouton->button, TRUE);
            MiseAJourScore(nd->lejeu->IDj, 20);
        }
        if (!nfikh)
        {
            id_nfikh = fct_nfikh(nd->lejeu->IDj, damierCpy, pionCpy);
            if (id_nfikh != -1)
            {
                gtk_button_set_image(GTK_BUTTON(damier[lespions[id_nfikh].y][lespions[id_nfikh].x]->Mabouton->button), NULL);
                gtk_widget_set_name(damier[lespions[id_nfikh].y][lespions[id_nfikh].x]->Mabouton->button, "my-button_black_nfikh");
                CSS(damier[lespions[id_nfikh].y][lespions[id_nfikh].x]->Mabouton->button);
                g_signal_handlers_block_matched(damier[lespions[id_nfikh].y][lespions[id_nfikh].x]->Mabouton->button,
                                                G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)show_mouve, NULL);
                lematch.damier[lespions[id_nfikh].y][lespions[id_nfikh].x] = -1;
                lespions[id_nfikh].etat = 0;
                MiseAJourScore(nd->lejeu->IDj, -10);
            }
        }
        nfikh = 0;
    }

    tour = tour * (-1);
}

int direction_Interdit(int X_myPos, int Y_myPos, int X_dest, int Y_dest)
{
    int h, v, X, Y;
    v = -1, h = 1;
    printf("\n dernierePosX : %d ,, dernierePosY : %d \n", dernierePosX, dernierePosY);
    printf("\n X_myPos : %d ,,  Y_myPos : %d \n  X_dest : %d ,,  Y_dest : %d \v", X_myPos, Y_myPos, X_dest, Y_dest);
    int lastPos = 0, DesPos = 0;
    for (int j = 0; j < 2; j++)
    {
        for (int i = 0; i < 2; i++)
        {
            lastPos = 0;
            DesPos = 0;
            X = X_myPos;
            Y = Y_myPos;
            while ((0 <= X && X <= 7) && (0 <= Y && Y <= 7))
            {
                X = X + h;
                Y = Y + v;
                if ((X == X_dest) && (Y == Y_dest))
                    DesPos = 1;
                if ((X == dernierePosX) && (Y == dernierePosY))
                    lastPos = 1;
                if ((lastPos == 1) && (DesPos == 1))
                {
                    printf(" \ninterdit X : %d  Y : %d\n", X, Y);
                    return ((int)0);
                }
            }
            h = h * (-1);
        }
        v = v * (-1);
    }
    return ((int)1);
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
    char* name = (char*)malloc(sizeof(char));
    mouvement* ptr = NULL;

    printf(" \n idselectioner %d", id);

    switch (mode)
    {
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
                            if (!strcmp(name, "mvt_possible") || !strcmp(name, "autre_mvt_possible") || !strcmp(name, "my-button_black_nfikh"))
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
                                if (direction_Interdit(lespions[id].x, lespions[id].y, ptr->x, ptr->y))
                                {
                                    printf("\n");
                                    afficher_damier(lematch.damier);

                                    printf("\n");
                                    Afficher_Arbre_horizotalement(ptr, 3);
                                    printf("\n");
                                    printf("\n id adv %d", ptr->IDa);
                                    gtk_widget_set_name(damier[ptr->y][ptr->x]->Mabouton->button, "mvt_possible");
                                    CSS(damier[ptr->y][ptr->x]->Mabouton->button);
                                    g_signal_handlers_block_matched(damier[ptr->y][ptr->x]->Mabouton->button,
                                                                    G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)make_mouve, NULL);
                                    g_signal_connect(damier[ptr->y][ptr->x]->Mabouton->button, "clicked", G_CALLBACK(make_mouve), ptr);
                                    set_name_autre_mvt_possible(ptr->fils1);
                                    set_name_autre_mvt_possible(ptr->fils2);
                                }
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
                        if (!strcmp(name, "mvt_possible") || !strcmp(name, "autre_mvt_possible") || !strcmp(name, "my-button_black_nfikh"))
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
<<<<<<< HEAD

=======
                        afficher_damier(lematch.damier);
>>>>>>> 3a7517a3bf1c483c01a0db20e8424506a39f9fbd
                        printf("\n");
                        Afficher_Arbre_horizotalement(ptr, 3);
                        printf("\n");
                        gtk_widget_set_name(damier[ptr->y][ptr->x]->Mabouton->button, "mvt_possible");
                        CSS(damier[ptr->y][ptr->x]->Mabouton->button);
                        g_signal_handlers_block_matched(damier[ptr->y][ptr->x]->Mabouton->button,
                                                        G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)make_mouve, NULL);
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
                                if (!strcmp(name, "mvt_possible") || !strcmp(name, "autre_mvt_possible") || !strcmp(name, "my-button_black_nfikh"))
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
                                    if (direction_Interdit(lespions[id].x, lespions[id].y, ptr->x, ptr->y))
                                    {
                                        printf("\n");
<<<<<<< HEAD

=======
                                        afficher_damier(lematch.damier);
>>>>>>> 3a7517a3bf1c483c01a0db20e8424506a39f9fbd
                                        printf("\n");
                                        Afficher_Arbre_horizotalement(ptr, 3);
                                        printf("\n");
                                        printf("\n id adv %d", ptr->IDa);
                                        gtk_widget_set_name(damier[ptr->y][ptr->x]->Mabouton->button, "mvt_possible");
                                        CSS(damier[ptr->y][ptr->x]->Mabouton->button);
                                        g_signal_handlers_block_matched(damier[ptr->y][ptr->x]->Mabouton->button,
                                                                        G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)make_mouve, NULL);
                                        g_signal_connect(damier[ptr->y][ptr->x]->Mabouton->button, "clicked", G_CALLBACK(make_mouve), ptr);
                                        set_name_autre_mvt_possible(ptr->fils1);
                                        set_name_autre_mvt_possible(ptr->fils2);
                                    }
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
                            if (!strcmp(name, "mvt_possible") || !strcmp(name, "autre_mvt_possible") || !strcmp(name, "my-button_black_nfikh"))
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
<<<<<<< HEAD

=======
                            afficher_damier(lematch.damier);
>>>>>>> 3a7517a3bf1c483c01a0db20e8424506a39f9fbd
                            printf("\n");
                            Afficher_Arbre_horizotalement(ptr, 3);
                            printf("\n");
                            gtk_widget_set_name(damier[ptr->y][ptr->x]->Mabouton->button, "mvt_possible");
                            CSS(damier[ptr->y][ptr->x]->Mabouton->button);
                            g_signal_handlers_block_matched(damier[ptr->y][ptr->x]->Mabouton->button,
                                                            G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)make_mouve, NULL);
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
                                if (!strcmp(name, "mvt_possible") || !strcmp(name, "autre_mvt_possible") || !strcmp(name, "my-button_black_nfikh"))
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
                                    if (direction_Interdit(lespions[id].x, lespions[id].y, ptr->x, ptr->y))
                                    {
                                        printf("\n");
<<<<<<< HEAD

=======
                                        afficher_damier(lematch.damier);
>>>>>>> 3a7517a3bf1c483c01a0db20e8424506a39f9fbd
                                        printf("\n");
                                        Afficher_Arbre_horizotalement(ptr, 3);
                                        printf("\n");
                                        printf("\n id adv %d", ptr->IDa);
                                        gtk_widget_set_name(damier[ptr->y][ptr->x]->Mabouton->button, "mvt_possible");
                                        CSS(damier[ptr->y][ptr->x]->Mabouton->button);
                                        g_signal_handlers_block_matched(damier[ptr->y][ptr->x]->Mabouton->button,
                                                                        G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)make_mouve, NULL);
                                        g_signal_connect(damier[ptr->y][ptr->x]->Mabouton->button, "clicked", G_CALLBACK(make_mouve), ptr);
                                        set_name_autre_mvt_possible(ptr->fils1);
                                        set_name_autre_mvt_possible(ptr->fils2);
                                    }
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
                            if (!strcmp(name, "mvt_possible") || !strcmp(name, "autre_mvt_possible") || !strcmp(name, "my-button_black_nfikh"))
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

                            afficher_damier(lematch.damier);

                            printf("\n");
                            Afficher_Arbre_horizotalement(ptr, 3);
                            printf("\n");
                            gtk_widget_set_name(damier[ptr->y][ptr->x]->Mabouton->button, "mvt_possible");
                            CSS(damier[ptr->y][ptr->x]->Mabouton->button);
                            g_signal_handlers_block_matched(damier[ptr->y][ptr->x]->Mabouton->button,
                                                            G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)make_mouve, NULL);
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
    char* name = (char*)malloc(sizeof(char));
    name = gtk_widget_get_name(widget);
    GdkPixbuf* pixt = NULL;
    GtkWidget* img = NULL;
    int damierCpy[NB_CASES][NB_PIONS];
    pion pionCpy[NB_PIONS];
    int id_nfikh = -1, etatJoueur = -1;

    if (!strcmp(name, "mvt_possible") && (id_pion_selectioner == mvt->IDj))
    {

        etatJoueur = lespions[mvt->IDj].etat;
        if (mvt->IDj > 11)
        {
            if (lespions[mvt->IDj].etat == 2)
            {
                pixt = gdk_pixbuf_new_from_file_at_size(clr_choisis(2), 50, 50, NULL);
            }
            else
            {
                pixt = gdk_pixbuf_new_from_file_at_size(clr_choisis(1), 50, 50, NULL);
            }
        }

        else
        {
            if (lespions[mvt->IDj].etat == 2)
            {
                pixt = gdk_pixbuf_new_from_file_at_size(clr_choisis(3), 50, 50, NULL);
            }
            else
            {
                pixt = gdk_pixbuf_new_from_file_at_size(clr_choisis(0), 50, 50, NULL);
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
            nfikh++;
            printf("\npos adv %d   &&   %d id %d\n", lespions[mvt->IDa].y, lespions[mvt->IDa].x, mvt->IDa);
            gtk_button_set_image(GTK_BUTTON(damier[lespions[mvt->IDa].y][lespions[mvt->IDa].x]->Mabouton->button), NULL);
            gtk_widget_set_name(damier[lespions[mvt->IDa].y][lespions[mvt->IDa].x]->Mabouton->button, "my-button_black");
            CSS(damier[lespions[mvt->IDa].y][lespions[mvt->IDa].x]->Mabouton->button);
            g_signal_handlers_block_matched(damier[lespions[mvt->IDa].y][lespions[mvt->IDa].x]->Mabouton->button,
                                            G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)show_mouve, NULL);
            if (lespions[mvt->IDa].etat == 1)
                MiseAJourScore(mvt->IDj, 10);
            else
                MiseAJourScore(mvt->IDj, 40);
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

        dernierePosY = lespions[mvt->IDj].y;
        dernierePosX = lespions[mvt->IDj].x;

        if (nfikh == 0)
        {
            copierDamier(damierCpy, lematch.damier);
            copierLesJetons(pionCpy, lespions);
        }
        deplacerJeton(mvt, lematch.damier, lespions);

        if (lespions[mvt->IDj].etat == 2)
        {
            if (mvt->IDj > 11)
                pixt = gdk_pixbuf_new_from_file_at_size(clr_choisis(2), 50, 50, NULL);
            else
                pixt = gdk_pixbuf_new_from_file_at_size(clr_choisis(3), 50, 50, NULL);
            img = gtk_image_new_from_pixbuf(pixt);
            gtk_button_set_image(GTK_BUTTON(widget), img);
        }

        if (mvt->fils1 || mvt->fils2)
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
                    char* name = (char*)malloc(sizeof(char));
                    name = gtk_widget_get_name(damier[i][j]->Mabouton->button);
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
                    char* name = (char*)malloc(sizeof(char));
                    name = gtk_widget_get_name(damier[i][j]->Mabouton->button);
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
            dernierePosY = -1;
            dernierePosX = -1;

            if (etatJoueur != lespions[mvt->IDj].etat && lespions[mvt->IDj].etat == 2)
                MiseAJourScore(mvt->IDj, 20);
            printf(">>>> FIN DE TOUR <<<<<");

            printf("_______ NFIKH ________");
            printf("\n la valeur de nfikh est %d", nfikh);
            if (!nfikh)
            {
                id_nfikh = fct_nfikh(mvt->IDj, damierCpy, pionCpy);
                if (id_nfikh != -1)
                {
                    gtk_button_set_image(GTK_BUTTON(damier[lespions[id_nfikh].y][lespions[id_nfikh].x]->Mabouton->button), NULL);
                    gtk_widget_set_name(damier[lespions[id_nfikh].y][lespions[id_nfikh].x]->Mabouton->button, "my-button_black_nfikh");
                    CSS(damier[lespions[id_nfikh].y][lespions[id_nfikh].x]->Mabouton->button);
                    g_signal_handlers_block_matched(damier[lespions[id_nfikh].y][lespions[id_nfikh].x]->Mabouton->button,
                                                    G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)show_mouve, NULL);
                    lematch.damier[lespions[id_nfikh].y][lespions[id_nfikh].x] = -1;
                    lespions[id_nfikh].etat = 0;
                    MiseAJourScore(mvt->IDj, -10);
                }
            }
            nfikh = 0;
            if (mode == 1)
                tour_de_machine();
        }
    }
    else
        printf("\n error : Y %d X %d", mvt->y, mvt->x);
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
    char* name = (char*)malloc(sizeof(char));
    if (mvt)
    {
        name = gtk_widget_get_name(damier[mvt->y][mvt->x]->Mabouton->button);
        if (strcmp(name, "mvt_possible"))
        {
            gtk_widget_set_name(damier[mvt->y][mvt->x]->Mabouton->button, "autre_mvt_possible");
            CSS(damier[mvt->y][mvt->x]->Mabouton->button);
        }
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

    Entree : _ void
    Sortie : _ void

    Description : cette fonction sert a construire une page de damier

*/

void page_damier()
{
    // Déclaration d'un pointeur vers une structure Fenetre nommée wind.
    Fenetre* wind;
    /* Allocation de mémoire pour la structure Fenetre et assignation
     à wind en utilisant la fonction Allouer_Fenetre().Création de la fenêtre
     en appelant la fonction Creer_Fenetre() avec wind comme argument.*/
    wind = Allouer_Fenetre(0, 1600, 900, "Jeu Damier", NULL, 200, 0, "#FF5733", "window", 1);
    wind = Creer_Fenetre(wind);
    // Application d'une feuille de style CSS à la fenêtre
    CSS(wind->ma_fenetre);
    /* Déclaration d'un pointeur vers une structure Fixed et allocation
    de mémoire pour cette structure en utilisant la fonction Allouer_fixed().*/
    Fixed* fixed = Allouer_fixed("fixed");
    // Déclaration de plusieurs pointeurs vers les structures frame,Box,Label et Bouton
    frame *frame1, *profil, *addimg;
    Box *B1, *B2, *B3, *B4, *B5, *b1, *b2, *b3, *b4;
    Label* mylabel;
    Label *score1, *score2;
    // Initialisation d'un Boutton simple
    Bouton* rejouer = Initialiser_boutton("Rejouer", NULL, "Voulez vous r�p�ter?", "", 350, 40, 1, 1300, 350, "vide", 0);
    // creation d'un boutton simple
    rejouer = Creer_SimpleBoutton(rejouer);
    // Connexion du signal "clicked" du bouton "Rejouer" à la fonction on_rejouer_clicked()
    g_signal_connect(rejouer->Mabouton->button, "clicked", G_CALLBACK(on_rejouer_clicked), wind->ma_fenetre);
    // Ajout du bouton "Rejouer" au conteneur fixed en appelant la fonction Ajouter_Fixed()
    Ajouter_Fixed(rejouer->Mabouton->button, rejouer->pos.X, rejouer->pos.Y, fixed);

    // Initialisation d'un Boutton simple
    Bouton* regle_jeu = Initialiser_boutton("Regles de jeu", NULL, "d�couvrir les r�gles de jeu ", "", 350, 40, 1, 1300, 450, "vide", 0);
    // creation d'un boutton simple
    regle_jeu = Creer_SimpleBoutton(regle_jeu);
    // Ajout du bouton "regle_jeu" au conteneur fixed en appelant la fonction Ajouter_Fixed()
    Ajouter_Fixed(regle_jeu->Mabouton->button, regle_jeu->pos.X, regle_jeu->pos.Y, fixed);
    // Connexion du signal "clicked" du bouton "regle_jeu" à la fonction on_regle_jeu_clicked()
    //    g_signal_connect(regle_jeu->Mabouton->button, "clicked", G_CALLBACK(on_regle_jeu_clicked), wind->ma_fenetre);

    // Initialisation et création d'un dialogue avec des boutons et des actions associées.
    Dialog* mondialog = Init_Dialog("dialog", "Do you want to leave this match ? ", "E:\\chabab_GTK\\icons\\accepter.png");
    Bouton* re = Initialiser_boutton("", NULL, "", "C:\\Users\\HP FOLIO 9470m\\OneDrive\\Bureau\\trash\\chabab_GTK\\chabab_GTK\\icons\\qutter_exporter.png", 80, 20, 1, 1500, 400, "vide", 30);
    re = Creer_SimpleBoutton(re);
    Creer_Dialog(mondialog);
    dialogue_action(re->Mabouton->button, mondialog);

    if (mode == 1) // correspond à Machine Vs Joueur
        mylabel = Init_label("Machine Vs Joueur", "framePr", 1330, 200);
    else // correspond à Joueur Vs Joueur
        mylabel = Init_label("Joueur Vs Joueur", "framePr", 1330, 200);
    Ajouter_Fixed(mylabel->leLabel, mylabel->X_Y.X, mylabel->X_Y.Y, GTK_FIXED(fixed));
    CSS(mylabel->leLabel);
    /*Définition des variables ligne, colonne, sizeBTN et size_icon
    pour contrôler la taille et la position des boutons du damier.*/
    int ligne = 400, colonne = 140, sizeBTN = 80, size_icon = 50;
    char icon_pion[NB_Cara_titre], name[NB_Cara_titre];

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            // Initialisation du tableau damier avec NULL.
            damier[i][j] = NULL;
        }
    }
    // créer les boutons du damier en fonction des coordonnées et des couleurs.
    for (int i = 0; i < 8; i++)
    {
        ligne = 400;
        strcpy(icon_pion, "vide");

        for (int j = 0; j < 8; j++)
        {

            if ((i % 2) == 0)
            {
                if ((j % 2) == 0) // si i et j sont pairs
                    strcpy(name, "my-button_gold");
                else
                    strcpy(name, "my-button_black");
            }
            else
            {
                if ((j % 2) == 0) // si j est pair et i impair
                    strcpy(name, "my-button_black");
                else
                    strcpy(name, "my-button_gold");
            }
            // copie la chaîne de caractères "vide" dans la variable icon_pion
            strcpy(icon_pion, "vide");
            /*vérifient les positions (i, j) dans le damier
             et attribuent une couleur à la variable icon_pion
             en utilisant la fonction clr_choisis().*/
            if (i <= 2)
            {
                if ((i % 2) == 0)
                {
                    if ((j % 2) != 0)
                    {
                        strcpy(icon_pion, clr_choisis(0));
                    }
                }
                else
                {
                    if ((j % 2) == 0)
                    {
                        strcpy(icon_pion, clr_choisis(0));
                    }
                }
            }
            if (i >= 5)
            {
                if (i % 2 == 0)
                {
                    if (j % 2 != 0)
                    {
                        strcpy(icon_pion, clr_choisis(1));
                    }
                }
                else
                {
                    if (j % 2 == 0)
                    {
                        strcpy(icon_pion, clr_choisis(1));
                    }
                }
            }
            /*crée un nouveau bouton avec les paramètres spécifiés,
            y compris la couleur icon_pion. Le bouton est ensuite assigné
             à l'élément correspondant dans le tableau damier à l'indice [i][j]*/
            damier[i][j] = Initialiser_boutton("", name, "", icon_pion, sizeBTN, sizeBTN, 0, ligne, colonne, NULL, size_icon);
            damier[i][j] = Creer_SimpleBoutton(damier[i][j]);
            // On applique la fonction CSS
            CSS(damier[i][j]->Mabouton->button);
            // ajoute le bouton au conteneur fixed à la position spécifiée
            Ajouter_Fixed(damier[i][j]->Mabouton->button, damier[i][j]->pos.X, damier[i][j]->pos.Y, GTK_FIXED(fixed));
            // ajuster la position verticale des boutons dans le damier.
            ligne = ligne + sizeBTN;
        }
        // colonne est mise à jour pour la prochaine itération de la boucle extérieure.
        colonne = colonne + sizeBTN;
    }
    // Initialisation de la structure Label
    score1 = Init_label(" Score ", "score", 400, 50);
    score2 = Init_label(" Score ", "score", 400, 800);
    scoreJoueur1 = Init_label(" 0000 ", "score", 550, 50);
    scoreJoueur2 = Init_label(" 0000 ", "score", 550, 800);
    // ajoute le bouton au conteneur fixed à la position spécifiée
    Ajouter_Fixed(scoreJoueur1->leLabel, scoreJoueur1->X_Y.X, scoreJoueur1->X_Y.Y, GTK_FIXED(fixed));
    Ajouter_Fixed(scoreJoueur2->leLabel, scoreJoueur2->X_Y.X, scoreJoueur2->X_Y.Y, GTK_FIXED(fixed));
    Ajouter_Fixed(score1->leLabel, score1->X_Y.X, score1->X_Y.Y, GTK_FIXED(fixed));
    Ajouter_Fixed(score2->leLabel, score2->X_Y.X, score2->X_Y.Y, GTK_FIXED(fixed));
    // On applique une feuille de style CSS au bouton en utilisant la fonction CSS().
    CSS(score1->leLabel);
    CSS(score2->leLabel);
    CSS(scoreJoueur1->leLabel);
    CSS(scoreJoueur2->leLabel);
    // Ajout du fixed à la fenetre
    Ajouter_fenetre(wind, fixed->mon_fixed);
    // Affichage de la fenetre
    afficher_fenetre(wind->ma_fenetre);
}

/*
    Nom Fonction : jeu_commence

    Entree : _ Rien

    Sortie : _Rien

    Description : cette fonction sert a declancher un jeu de damier
*/

void jeu_commence(GtkWidget* widget, GtkWidget* widget2)
{
    //Si widget2 existe il est détruit à l'aide de la fonction gtk_widget_destroy
    if (widget2)
        gtk_widget_destroy(widget2);
// initialiser le damier et les pions du jeu respectivement.
    Initialiser_Damier(&lematch.damier);
    Initialiser_Tab_Pion(lespions);
// appelée pour créer et afficher la page du damier dans l'interface utilisateur
    page_damier();
    for (int i = 0; i < 8; i++)// parcourent le damier.
    {
        for (int j = 0; j < 8; j++)
        {
            /*Si la valeur dans lematch.damier[i][j] est supérieure
            ou égale à zéro, cela signifie qu'il y a un bouton à cette position dans le damier.*/
            if (lematch.damier[i][j] >= 0)
            {
                // connecter le signal "clicked" du bouton à la fonction show_mouve en utilisant G_CALLBACK()
                g_signal_connect(damier[i][j]->Mabouton->button, "clicked", G_CALLBACK(show_mouve), lematch.damier[i][j]);
                //appliquer des styles CSS au bouton.
                CSS(damier[i][j]->Mabouton->button);
                /*Selon la valeur de mode, le nom du widget
                 (bouton) est défini en tant que "joueur1"
                 ou "joueur2" en utilisant gtk_widget_set_name()
                 en fonction de la valeur dans lematch.damier[i][j].*/
                if (mode == 2)
                {
                    if (lematch.damier[i][j] > 11)
                        gtk_widget_set_name(damier[i][j]->Mabouton->button, "joueur1");
                    else
                        gtk_widget_set_name(damier[i][j]->Mabouton->button, "joueur2");
                }
                else
                {
                    if (lematch.damier[i][j] > 11)
                        gtk_widget_set_name(damier[i][j]->Mabouton->button, "joueur1");
                }
            }
        }
    }
    //Si le mode est égal à 1 et colorJeton est égal à -1,
    //cela signifie qu'il s'agit du tour de la machine
    if (mode == 1 && colorJeton == -1)
        tour_de_machine();
}

/*
    Nom Fonction : what_btn_mode

    Entree : _ Deux Widget

    Sortie :_void

    Description : cette fonction est utilisée pour changer le mode
    de jeu entre le mode 1 et le mode 2 en fonction du bouton cliqué
*/
void what_btn_mode(GtkWidget* widget, GtkWidget* widget2)
{
    // utilisée pour obtenir le nom du widget sous forme
    // de chaîne de caractères et le stocker dans la variable label.
    char* label = gtk_widget_get_name(GTK_BUTTON(widget));
    // vérifie si le nom du widget widget est égal à "btn_mode1_Off" ou "btn_mode1_On".
    if (!strcmp(label, "btn_mode1_Off") || !strcmp(label, "btn_mode1_On"))
    {
        //le mode actuel est le mode 2, et le bouton a été cliqué pour passer au mode 1.
        gtk_widget_set_name(widget, "btn_mode1_On");
        gtk_widget_set_name(widget2, "btn_mode2_Off");
        CSS(widget);
        CSS(widget2);
        mode = 1;
    }
    else
    //le mode actuel est le mode 1,et le bouton a été cliqué pour passer au mode 2.
    {
        gtk_widget_set_name(widget, "btn_mode2_On");
        gtk_widget_set_name(widget2, "btn_mode1_Off");
        CSS(widget);
        CSS(widget2);
        mode = 2;
    }
}
/*
    Nom Fonction : what_btn_Color

    Entree : _ Deux Widget

    Sortie : void

    Description : cette fonction sert a declancher un jeu de damier
*/
void what_btn_Color(GtkWidget* widget, GtkWidget* widget2)
{
    //obtenir le nom du widget widget sous forme de chaîne
    // de caractères et le stocker dans la variable label
    char* label = gtk_widget_get_name(GTK_BUTTON(widget));
    /* vérifie si le nom du widget widget est égal
    à "black_color_Off" ou "black_color_On" */
    if (!strcmp(label, "black_color_Off") || !strcmp(label, "black_color_On"))
    {
        //widget est défini comme "black_color_On".
        gtk_widget_set_name(widget, "black_color_On");
        //widget2 est défini comme "white_color_Off".
        gtk_widget_set_name(widget2, "white_color_Off");
        CSS(widget);
        CSS(widget2);
        //définie à -1 pour représenter la couleur blanche du jeton.
        colorJeton = -1;
        //définie à -1 pour représenter le tour du joueur blanc.
        tour = -1;
    }
    //la couleur du jeton actuelle est le blanc, et le bouton a été cliqué pour changer la couleur en noir
    else
    {
        gtk_widget_set_name(widget, "white_color_On");
        gtk_widget_set_name(widget2, "black_color_Off");
        CSS(widget);
        CSS(widget2);
        colorJeton = 1;//définie à 1 pour représenter la couleur noire du jeton.
        tour = 1;//définie à 1 pour représenter le tour du joueur noir.
    }
}

/*
    Nom Fonction : Mode_page

    Entree : _ void
    Sortie : void

    Description : la fonction qui sert a  fair la construction d'une page mode
    (la page ou l'utilisateur choisit quelle mode de jeu)
*/

void Mode_page()
{
    //Déclaration des variables
    Fenetre* fenetre_mode;
    // déclarée et initialisée en tant que pointeur vers une structure Fenetre
    fenetre_mode = Allouer_Fenetre(0, 1300, 900, "Jeu damier", NULL, 300, 0, NULL, "fenetre_mode", 0);
    fenetre_mode = Creer_Fenetre(fenetre_mode);
    CSS(fenetre_mode->ma_fenetre);
//Un objet Fixed est créé pour gérer le positionnement des éléments dans la fenêtre
    Fixed* fixed = Allouer_fixed("fixed");
    //Les variables frame1, B1, B2 et B3 sont déclarées pour stocker des structures de type frame et Box
    frame* frame1;
    Box *B1, *B2, *B3;
    //initialisé avec le titre "MODE" et les coordonnées de position et de taille spécifiées.
    frame1 = Init_frame("MODE", "frameMode", 20, 180, 270, 450, 470);
    //Le cadre est créé à l'aide de la fonction Creation_frame()
    Creation_frame(frame1);
    CSS(frame1->monframe);
       // initialisé avec le label "Joueur VS Machine" et d'autres paramètres.
       //Le bouton est créé à l'aide de la fonction Creer_SimpleBoutton().
    Bouton* btn1 = Initialiser_boutton("Joueur   VS   Machine", "btn_mode1_On", "", "", 380, 106, 1, 1500, 400, "vide", 80);
    btn1 = Creer_SimpleBoutton(btn1);
       //Les styles CSS du bouton sont appliqués à l'aide de la fonction CSS().
    CSS(btn1->Mabouton->button);

      // initialisé avec le label "Joueur VS Joueur" et d'autres paramètres.
      //Le bouton est créé à l'aide de la fonction Creer_SimpleBoutton().
    Bouton* btn2 = Initialiser_boutton("Joueur   VS   Joueur", "btn_mode2_Off", "", "", 380, 106, 1, 1500, 400, "vide", 80);
    btn2 = Creer_SimpleBoutton(btn2);
    CSS(btn2->Mabouton->button);

    // signaux sont connectés aux boutons btn1 et btn2 pour appeler la fonction what_btn_mode lorsqu'ils sont cliqués
    g_signal_connect(btn2->Mabouton->button, "clicked", G_CALLBACK(what_btn_mode), btn1->Mabouton->button);
    g_signal_connect(btn1->Mabouton->button, "clicked", G_CALLBACK(what_btn_mode), btn2->Mabouton->button);

    //initialisé avec le label "blanc" et d'autres paramètres.
    //Le bouton est créé à l'aide de la fonction Creer_SimpleBoutton().
    Bouton* color1 = Initialiser_boutton("blanc", "white_color_On", "", "", 190, 106, 1, 1500, 600, "vide", 80);
    color1 = Creer_SimpleBoutton(color1);
    //Les styles CSS du bouton sont appliqués à l'aide de la fonction CSS().
    CSS(color1->Mabouton->button);

    // initialisé avec le label "Noir" et d'autres paramètres.
    //Le bouton est créé à l'aide de la fonction Creer_SimpleBoutton().
    Bouton* color2 = Initialiser_boutton("Noir", "black_color_Off", "", "", 190, 106, 1, 1500, 600, "vide", 80);
    color2 = Creer_SimpleBoutton(color2);
    //Les styles CSS du bouton sont appliqués à l'aide de la fonction CSS().
    CSS(color2->Mabouton->button);

    //signaux sont connectés aux boutons color1 et color2 pour appeler
    // la fonction what_btn_Color lorsqu'ils sont cliqués.
    g_signal_connect(color1->Mabouton->button, "clicked", G_CALLBACK(what_btn_Color), color2->Mabouton->button);
    g_signal_connect(color2->Mabouton->button, "clicked", G_CALLBACK(what_btn_Color), color1->Mabouton->button);

    B2 = Allouer_Box(0, 20);
    Creer_Box(B2, NULL);
    //Les boutons color2 et color1 sont ajoutés à la boîte à l'aide de la fonction Ajouter_Box().
    Ajouter_Box(B2, color2->Mabouton->button, 0, FALSE, FALSE, 0);
    Ajouter_Box(B2, color1->Mabouton->button, 0, FALSE, FALSE, 0);

    //B3 est créée pour contenir les boutons "Commencer" et "Quitter".
    B3 = Allouer_Box(0, 20);
    Creer_Box(B3, NULL);
    //initialiser et creer un boutton simple
    Bouton* Commencer = Initialiser_boutton("Commencer", "btn_mode_commencer", "", "", 190, 106, 1, 1500, 600, "vide", 80);
    Commencer = Creer_SimpleBoutton(Commencer);
    //Les styles CSS du bouton sont appliqués à l'aide de la fonction CSS().
    CSS(Commencer->Mabouton->button);
    // signal est connectés aux boutons pour appeler des fonctions lorsque les boutons sont cliqués.
    g_signal_connect(Commencer->Mabouton->button, "clicked", G_CALLBACK(jeu_commence), fenetre_mode->ma_fenetre);

    //initialiser et creer un boutton simple
    Bouton* Quitter = Initialiser_boutton("Quitter", "btn_mode_quitter", "", "", 190, 106, 1, 1500, 400, "vide", 80);
    Quitter = Creer_SimpleBoutton(Quitter);
    CSS(Quitter->Mabouton->button);
    // signal est connectés aux boutons pour appeler des fonctions lorsque les boutons sont cliqués.
    g_signal_connect(Quitter->Mabouton->button, "clicked", G_CALLBACK(signal_fenetre_destroy), fenetre_mode->ma_fenetre);
    Ajouter_Box(B3, Commencer->Mabouton->button, 0, FALSE, FALSE, 0);
    Ajouter_Box(B3, Quitter->Mabouton->button, 0, FALSE, FALSE, 0);
//B1 est créée pour contenir les éléments principaux de la page de sélection du mode de jeu.
    B1 = Allouer_Box(1, 20);
    Creer_Box(B1, NULL);
    gtk_widget_set_name(B1->mon_box, "BoxMode");
    //Les styles CSS du bouton sont appliqués à l'aide de la fonction CSS().
    CSS(B1->mon_box);

    Label* title_mode;
    //Un label title_mode est initialisé avec le texte "MODE" et les coordonnées de position spécifiées.
    title_mode = Init_label("MODE ", "title_mode", 400, 50);
    CSS(title_mode->leLabel);
    //Le label et les boutons btn1 et btn2 sont ajoutés à la boîte B1 à l'aide de la fonction Ajouter_Box().
    Ajouter_Box(B1, title_mode->leLabel, 0, FALSE, FALSE, 0);
    Ajouter_Box(B1, btn1->Mabouton->button, 0, FALSE, FALSE, 0);
    Ajouter_Box(B1, btn2->Mabouton->button, 0, FALSE, FALSE, 0);
    Ajouter_Box(B1, B2->mon_box, 0, FALSE, FALSE, 0);
    Ajouter_Box(B1, B3->mon_box, 0, FALSE, FALSE, 0);
   //B1 est ajoutée au conteneur fixed à des coordonnées spécifiées.
    Ajouter_Fixed(B1->mon_box, 400, 200, fixed);
    //Le conteneur fixed est ajouté à la fenêtre principale fenetre_mode.
    Ajouter_fenetre(fenetre_mode, fixed->mon_fixed);
    afficher_fenetre(fenetre_mode->ma_fenetre);
}
