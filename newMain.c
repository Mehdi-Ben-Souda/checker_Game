#include "Macros.h"
#include "libxml2/libxml/parser.h"

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

Bouton* damier[8][8];

typedef struct
{
    coordonne pion;
    coordonne new_emplacement;
} mouve;

void make_mouve(GtkWidget* widget, mouve* mvt)
{
    GdkPixbuf* pixt;
    // création de l'image

    pixt = gdk_pixbuf_new_from_file_at_size("black_pion.png", 40, 40, NULL);
    GtkWidget* img = gtk_image_new_from_pixbuf(pixt);

    gtk_button_set_image(GTK_BUTTON(widget), NULL);

    gtk_button_set_image(GTK_BUTTON(damier[mvt->new_emplacement.X][mvt->new_emplacement.Y]->Mabouton->button), img);

    gtk_button_set_always_show_image(GTK_BUTTON(damier[mvt->new_emplacement.X][mvt->new_emplacement.Y]->Mabouton->button),
                                     TRUE);
    printf("done");
}

char image1[NB_Cara_chemin] = "C:\\Users\\MSB\\Desktop\\Semestre 2\\GTK\\chabab_GTK\\icons\\icone.png";
char image2[NB_Cara_chemin] = "C:\\Users\\MSB\\Desktop\\Semestre 2\\GTK\\chabab_GTK\\icons\\menu2.png";

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

int main(int argc, char* argv[])
{
    //-------------------------------------     Initialisation de GTK     --------------------------------------------------
    gtk_init(&argc, &argv);

    //-------------------------------------     Initialisation de GTK     --------------------------------------------------
    gtk_init(&argc, &argv);

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
    mylabel = Init_label("Machine Vs Joueur", "framePr", 1330, 200);
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

    //+++++++++++++++ login page++++++++++++++++++++++
    /* Fenetre* login_wind;

    login_wind = Allouer_Fenetre(0, 1600, 900, "Jeu Damier", NULL, 200, 0, "#FF5733", "login_window", 0);
    login_wind = Creer_Fenetre(login_wind);

    */

    // ++++++++++++++++++++++damier++++++++++++++++++++++

    int ligne = 400, colonne = 700, sizeBTN = 80, size_icon = 40;
    char icon_pion[NB_Cara_titre], name[NB_Cara_titre];

    mouve* mvt = NULL;
    mvt = (mouvement*)malloc(sizeof(mouvement));
    mvt->new_emplacement.X = 3;
    mvt->new_emplacement.Y = 1;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
            damier[i][j] = NULL;
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
                    strcpy(name, "my-button_black");
                else
                    strcpy(name, "my-button_gold");
            }
            else
            {
                if ((j % 2) == 0)
                    strcpy(name, "my-button_gold");
                else
                    strcpy(name, "my-button_black");
            }

            strcpy(icon_pion, "vide");

            if (i <= 2)
            {
                if ((i % 2) == 0)
                {
                    if ((j % 2) == 0)
                    {
                        strcpy(icon_pion, "black_pion.png");
                    }
                }
                else
                {
                    if ((j % 2) == 1)
                    {
                        strcpy(icon_pion, "black_pion.png");
                    }
                }
            }

            if (i >= 5)
            {
                if (i % 2 == 0)
                {
                    if (j % 2 == 0)
                    {
                        strcpy(icon_pion, "white_pion.png");
                    }
                }
                else
                {
                    if (j % 2 != 0)
                    {
                        strcpy(icon_pion, "white_pion.png");
                    }
                }
            }
            damier[i][j] = Initialiser_boutton("", name, "", icon_pion, sizeBTN, sizeBTN, 0, ligne, colonne, NULL, size_icon);
            damier[i][j] = Creer_SimpleBoutton(damier[i][j]);

            // add_bgcolor(GTK_WIDGET(damier[i][j]->Mabouton->button), "#bb8141", 1);

            mvt->pion.X = i;
            mvt->pion.X = j;
            //++++++ CSS++++++
            CSS(damier[i][j]->Mabouton->button);

            g_signal_connect(damier[i][j]->Mabouton->button, "clicked", G_CALLBACK(make_mouve), mvt);
            Ajouter_Fixed(damier[i][j]->Mabouton->button, damier[i][j]->pos.X, damier[i][j]->pos.Y, GTK_FIXED(fixed));
            ligne = ligne + sizeBTN;
        }
        colonne = colonne - sizeBTN;
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
    boucle_gtk();

    /*
    g_signal_connect_swapped(G_OBJECT(wind->ma_fenetre), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    // Boucle principale de GTK
    gtk_main();*/
    return 0;
}
