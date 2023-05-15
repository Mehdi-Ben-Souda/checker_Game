#include "Macros.h"

char image1[NB_Cara_chemin] = "C:\\Users\\MSB\\Desktop\\Semestre 2\\GTK\\chabab_GTK\\icons\\icone.png";
char image2[NB_Cara_chemin] = "C:\\Users\\MSB\\Desktop\\Semestre 2\\GTK\\chabab_GTK\\icons\\menu2.png";

void on_button_clicked1(GtkWidget *widget, Fenetre*new)
{

    afficher_fenetre(new->ma_fenetre);
}
void on_bouton_clicked(GtkWidget *widget ,Dialog *MonDialogue)
{
    Afficher_dialogue(MonDialogue);
}
void dialogue_action(GtkWidget *widget ,Dialog *MonDialogue)
{
    g_signal_connect(widget,"clicked",G_CALLBACK(on_bouton_clicked),MonDialogue);

}
int main(int argc, char* argv[])
{
    //-------------------------------------     Initialisation de GTK     --------------------------------------------------
    gtk_init(&argc, &argv);
    Fenetre* wind;
    frame* frame1,*profil,*addimg;
    Box *B1,*B2,*B3,*B4,*B5,*b1,*b2,*b3,*b4;
    Label* mylabel;
    wind = Allouer_Fenetre(0, 800, 800, "Test Macros GTK - 2022-2023", "C:\\Users\\lenovoi\\CLionProjects\\chabab_GTK\\icons\\home.png", 200, 0, NULL, "titre", 1);
    wind = Creer_Fenetre(wind);
    //-------------------------------------  Fixed       -------------------------------------------------
    Fixed* fixed = Allouer_fixed("fixed");

    //-------------------------------------    Simple boutton     --------------------------------------------------
    Bouton* rejouer = Initialiser_boutton("Rejouer", "Voulez vous répéter?", "", 140, 40, 1, 1500, 200, "vide");
    rejouer = Creer_SimpleBoutton(rejouer);
    Ajouter_Fixed(rejouer->Mabouton->button, rejouer->pos.X, rejouer->pos.Y, fixed);
    Ajouter_fenetre(wind, fixed->mon_fixed);

    Bouton* regle_jeu = Initialiser_boutton("Règles de jeu", "découvrir les règles de jeu ", "", 140, 40, 1, 1500, 300, "vide");
    regle_jeu = Creer_SimpleBoutton(regle_jeu);
    Ajouter_Fixed(regle_jeu->Mabouton->button, regle_jeu->pos.X, regle_jeu->pos.Y, fixed);

    Bouton* help = Initialiser_boutton("Help", "", "", 140, 40, 1, 1500, 400, "vide");
    help = Creer_SimpleBoutton(help);
    Ajouter_Fixed(help->Mabouton->button, help->pos.X, help->pos.Y, fixed);
    //-------------------------------------    Le dialogue     --------------------------------------------------
    Dialog* mondialog = Init_Dialog("zrferg", "Do you want to leave this match ? ","E:\\chabab_GTK\\icons\\accepter.png");


    /*---------------------ajouter boutons simples dans une frame-----------------*/

    frame1= Init_frame("", "name", 20, 1400, 500, 50, 70);
    Creation_frame(frame1);
    Ajouter_Fixed(frame1->monframe, frame1->pos.X, frame1->pos.Y, fixed);

    Bouton* re = Initialiser_boutton("", "", "C:\\Users\\lenovoi\\CLionProjects\\chabab_GTK\\icons\\qutter_exporter.png", 80, 20, 1, 1500, 400, "vide");
    re = Creer_SimpleBoutton(re);
    Creer_Dialog(mondialog);
   dialogue_action(re->Mabouton->button,mondialog);
   // Afficher_dialogue(mondialog);



    Bouton* btn1 = Initialiser_boutton("", "", "C:\\Users\\lenovoi\\CLionProjects\\chabab_GTK\\icons\\reload.png", 80, 20, 1, 1500, 400, "vide");
    btn1 = Creer_SimpleBoutton(btn1);

    Bouton* btn2 = Initialiser_boutton("", "", "C:\\Users\\lenovoi\\CLionProjects\\chabab_GTK\\icons\\pause.png", 80, 20, 1, 1500, 400, "vide");
    btn2 = Creer_SimpleBoutton(btn2);

    Bouton* btn3 = Initialiser_boutton("", "", "C:\\Users\\lenovoi\\CLionProjects\\chabab_GTK\\icons\\play.png", 80, 20, 1, 1500, 400, "vide");
    btn3 = Creer_SimpleBoutton(btn3);


    B1= Allouer_Box(1,5);
    Creer_Box(B1,frame1->monframe);
    B2= Allouer_Box(0,5);
    Creer_Box(B2,B1->mon_box);
    B3= Allouer_Box(0,5);
    Creer_Box(B3,B1->mon_box);
    B4= Allouer_Box(0,5);
    Creer_Box(B4,B1->mon_box);
    B5= Allouer_Box(0,5);
    Creer_Box(B5,B1->mon_box);

    Ajouter_Box(B2,re->Mabouton->button,0,TRUE,TRUE,5);
    Ajouter_Box(B2,btn1->Mabouton->button,0,TRUE,TRUE,5);
    Ajouter_Box(B2,btn2->Mabouton->button,0,TRUE,TRUE,5);
    Ajouter_Box(B2,btn3->Mabouton->button,0,TRUE,TRUE,5);

     profil = Init_frame("", "profil", 10, 1470, 100, 100, 100);
    Creation_frame(profil);
    Ajouter_Fixed(profil->monframe, profil->pos.X, profil->pos.Y, fixed);
    b1= Allouer_Box(1,5);
    Creer_Box(b1,profil->monframe);
    b2= Allouer_Box(0,5);
    Creer_Box(b2,b1->mon_box);
    mylabel = Init_label("Machine Vs Joueur", "monlabel", 500, 100);
    Ajouter_Box(b2,mylabel->leLabel,0,TRUE,TRUE,10);
/*-----------------------------------image----------------------------------------------*/


    GtkWidget *image1 = gtk_image_new_from_file("C:\\Users\\lenovoi\\CLionProjects\\chabab_GTK\\icons\\chessboard.png");
    Ajouter_Fixed(image1,1430,130,fixed);
    GtkWidget *image2 = gtk_image_new_from_file("C:\\Users\\lenovoi\\CLionProjects\\chabab_GTK\\icons\\chessboard.png");
    Ajouter_Fixed(image2,1650,130,fixed);
/*-------------------------------------nouvelle fenetre---------------------------*/
    GtkWidget *label;


    label = gtk_label_new("choisis ton mode de jeu !");

    Fenetre* nouvfen;
    // Fixed* fixed = Allouer_fixed("fixed");
    Label* label1;
    nouvfen = Allouer_Fenetre(0, 500, 500, "choix", "C:\\Users\\lenovoi\\CLionProjects\\chabab_GTK\\icons\\home.png", 200, 0, NULL, "titre1", 1);
    nouvfen = Creer_Fenetre(nouvfen);
    Fixed* fixed1 = Allouer_fixed("fixed");
    label1= Init_label("coisis ton mode", "label", 500, 100);
    Ajouter_Fixed(label1->leLabel, label1->X_Y.X, label1->X_Y.Y, fixed1);
    Ajouter_fenetre(nouvfen, fixed1->mon_fixed);
   Bouton *bouton=Initialiser_boutton("choix", "", "C:\\Users\\lenovoi\\CLionProjects\\chabab_GTK\\icons\\qutter_exporter.png", 80, 20, 1, 1500, 50, "vide");
    bouton = Creer_SimpleBoutton(bouton);
  Ajouter_Fixed(bouton->Mabouton->button, bouton->pos.X, bouton->pos.Y, fixed);
    g_signal_connect(bouton->Mabouton->button, "clicked", G_CALLBACK(Signal_afficher_fenetre), nouvfen->ma_fenetre);
    afficher_fenetre(wind->ma_fenetre);
    boucle_gtk();

    return 0;
}
