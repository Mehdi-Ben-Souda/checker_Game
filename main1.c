#include "Macros.h"
//#include "fonction_XML.h"

char image1[NB_Cara_chemin] = "C:\\Users\\MSB\\Desktop\\Semestre 2\\GTK\\chabab_GTK\\icons\\icone.png";
char image2[NB_Cara_chemin] = "C:\\Users\\MSB\\Desktop\\Semestre 2\\GTK\\chabab_GTK\\icons\\menu2.png";
int main(int argc, char* argv[])
{
    //-------------------------------------     Initialisation de GTK     --------------------------------------------------
    gtk_init(&argc, &argv);
    CelluleItem* item = NULL;
    CelluleItem* item2 = NULL;
    CelluleMenu* menu = NULL;
    //----------------------------------------------------------------------------------------------------------------------
    //-------------------------------------     Création de la fenêtre    --------------------------------------------------
    Fenetre* wind;
    wind = Allouer_Fenetre(WINDOW_TOPLEVEL, 800, 800, "Youssef kassimi", "E:\\chabab_GTK\\icons\\home.png", 200, 0, NULL, "titre", 1);
    wind = Creer_Fenetre(wind);
    GtkAccelGroup* accel_group;
    accel_group = gtk_accel_group_new();
    gtk_window_add_accel_group(GTK_WINDOW(wind->ma_fenetre), accel_group);
    //-------------------------------------  Fixed       -------------------------------------------------
    Fixed* fixed = Allouer_fixed("fixed");
    //-------------------------------------  Menu       --------------------------------------------------
    item = Inserer_CelluleItem(item, "label", GTK_STOCK_NEW, "celluleitem", 'c', accel_group);
    item = Inserer_CelluleItem(item, "copy", GTK_STOCK_COPY, "celluleitem", 'b', accel_group);
    item = Inserer_CelluleItem(item, "cut", GTK_STOCK_CUT, "celluleitem", 'l', accel_group);
    item2 = Inserer_CelluleItem(item2, "label1", GTK_STOCK_NETWORK, "celluleitem", 'c', accel_group);
    item2 = Inserer_CelluleItem(item2, "copy1", GTK_STOCK_CANCEL, "celluleitem", '\0', accel_group);
    item2 = Inserer_CelluleItem(item2, "cut1", GTK_STOCK_CDROM, "celluleitem", 'l', accel_group);
    // item= ajouter_sous_menu(item,item2);
    menu = Inserer_CeluleMenu(menu, item, "file");
    menu = Inserer_CeluleMenu(menu, item2, "creer");
    Menu* principal = Creer_Menu(menu, 0, 0, 0);
    Ajouter_Fixed(principal->main_menu, principal->pos.X, principal->pos.Y, fixed);

    //-------------------------------------    Radio check bouton     --------------------------------------------------
    CelluleBouton* rbtn1 = NULL;
    CelluleBouton* rbtn2 = NULL;
    RadioCheckBouttons* box1, * box2;
    // GtkWidget *btn;

    rbtn1 = Inserer_Bouton(rbtn1, 'r', "rbtn1");
    rbtn1 = Inserer_Bouton(rbtn1, 'r', "rbtn2");
    box1 = Crerr_Radio_Check_Boutons(rbtn1, 100, 40, 0, 10);

    frame* frame1 = Init_frame("mes radio boutons", "name", 20, box1->pos.X, box1->pos.Y, 50, 40);
    Creation_frame(frame1);
    Ajouter_Frame(frame1,box1->groupe->mon_box);
    Ajouter_Fixed(frame1->monframe, frame1->pos.X, frame1->pos.Y, fixed);


    rbtn2 = Inserer_Bouton(rbtn2, 'c', "rbtn3");
    rbtn2 = Inserer_Bouton(rbtn2, 'c', "chbtn");
    box2 = Crerr_Radio_Check_Boutons(rbtn2, 100, 100, 0, 10);
    frame* frame2 = Init_frame("mes check boutons", "name", 20, box2->pos.X, box2->pos.Y, 50, 40);
    Creation_frame(frame2);
    Ajouter_Frame(frame2,box2->groupe->mon_box);
    Ajouter_Fixed(frame2->monframe, frame2->pos.X, frame2->pos.Y, fixed);

    Label* label = NULL;
    label = Init_label("sexe:", "label", 20, 70);
    Ajouter_Fixed(label->leLabel, label->X_Y.X, label->X_Y.Y, fixed);
    int compt1 = 0;
    ToolItem* tool = NULL, * tool2 = NULL;
    tool = Init_CelluleTooolItem("tool", "E:\\chabab_GTK\\icons\\add_icon.png");
    tool = Creer_CelluleToolItem(tool);
    tool2 = Init_CelluleTooolItem("tool", "E:\\chabab_GTK\\icons\\download.png");
    tool2 = Creer_CelluleToolItem(tool2);
    ToolBar* bar = NULL;
    bar = Init_toolbar(1, GTK_TOOLBAR_BOTH, 0, 300, 120);
    bar = Creer_toolbar(bar);
    Inserer_Tool_Item(bar->toolbar, tool, &compt1);
    Inserer_Tool_Item(bar->toolbar, tool2, &compt1);
    Ajouter_Fixed(bar->toolbar, bar->x_y.X, bar->x_y.Y, fixed);

    comboBox* combo = NULL;
    combo = creer_combo_Box(0, 20, 180, "name");
    combo = combo_box_inserer(combo, 1, "option1", "d");
    combo = combo_box_inserer(combo, 1, "option2", "f");
    combo = combo_box_inserer(combo, 1, "option3", "h");

    Ajouter_Fixed(combo->combo_box, combo->pos.X, combo->pos.Y, fixed);

    //-------------------------------------    Simple boutton     --------------------------------------------------
    Bouton* simple = Initialiser_boutton("_Boutton1", "c'est un boutton simple", "vide", 140, 70, 0, 20, 250, "#FF0000");

    simple = Creer_SimpleBoutton(simple);
    Ajouter_Fixed(simple->Mabouton->button, simple->pos.X, simple->pos.Y, fixed);
    image* image1 = creer_image("E:\\chabab_GTK\\icons\\icone.png", 200, 200, 300, 300);
    Ajouter_Fixed(image1->img, image1->pos.X, image1->pos.Y, fixed);


    //-------------------------------------    Asscenceur     --------------------------------------------------
    Assenceur* lassenceur = Allouer_Assenceur("mon assce", POLICY_ALWAYS, POLICY_ALWAYS);
    lassenceur = Ajouter_Assenceur(fixed->mon_fixed, lassenceur);
    Ajouter_fenetre(wind, lassenceur->assc);



    //-------------------------------------    Le dialogue     --------------------------------------------------
    Dialog* mondialog = Init_Dialog("zrferg", "Je suis jebbanma","E:\\chabab_GTK\\icons\\accepter.png");

    Creer_Dialog(mondialog);

    Afficher_dialogue(mondialog);
    afficher_fenetre(wind->ma_fenetre);
    boucle_gtk();

    return 0;
}





//char titre[20] = "Fenetre1";
//char couleur[8] = "#33FEFF";
//char chemin[200] = "C:\\Users\\MSB\\Desktop\\Semestre 2\\GTK\\chabab_GTK\\Gtk App21\\Gtk App21\\icone.png";
//
//
//int main(int argc, char** argv)
//{
//	gtk_init(&argc, &argv);
//
//	Fenetre* window = Allouer_Fenetre(WINDOW_TOPLEVEL, 600, 300, "Inscription", NULL, 0, 0, NULL, "Acceuil", 1);
//
//
//	window = Creer_Fenetre(window);
//	gtk_window_set_resizable(GTK_WINDOW(window->ma_fenetre), 0);
//	Fixed* lefixed = Allouer_fixed("Leixed");
//
//
//
//	Box* box_horizontal1 = Allouer_Box(GTK_ORIENTATION_HORIZONTAL,30);
//
//	Box* box_horizontal2 = Allouer_Box(GTK_ORIENTATION_HORIZONTAL, 30);
//
//	Box* box_horizontal3 = Allouer_Box(GTK_ORIENTATION_HORIZONTAL, 30);
//
//
//
//	Label* username = Init_label("username", "username", 50, 100);
//
//	Entree* entre_username = Entry_init("your unsername", 0, "about.png", 150, 100);
//	entre_username = Creer_Entree(entre_username);
//
//	Ajouter_Box(box_horizontal2, username->leLabel, BoxPositionInsertion_Debut, 0, 0, 5);
//	Ajouter_Box(box_horizontal2, entre_username->entry, BoxPositionInsertion_Debut, 0, 0, 5);
//
//
//
//	add_bgcolor(box_horizontal2->mon_box, "#FFEE00", 0.5);
//
//
//	Label* password = Init_label("password", "password", 50, 145);
//
//	Entree * entre_password = Entry_init("your password", 'X', "C:\\Users\\MSB\\Desktop\\Semestre 2\\GTK\\chabab_GTK\\icons\\about.png", 150, 145);
//	entre_password = Creer_Entree(entre_password);
//
//	Ajouter_Box(box_horizontal1, password->leLabel, BoxPositionInsertion_Debut, 0, 0, 5);
//	Ajouter_Box(box_horizontal1, entre_password->entry, BoxPositionInsertion_Debut, 0, 0, 5);
//
//
//
//
//
//
//
//	Label* ville = Init_label("Ville", "ville", 50, 145);
//	comboBox* combo_ville = creer_combo_Box(1, 0, 0,"combo1");
//	combo_ville =combo_box_inserer(combo_ville, 1, "Meknes", "zfzf");
//	combo_ville = combo_box_inserer(combo_ville, 2, "Fes", "zfzf2");
//	combo_ville = combo_box_inserer(combo_ville, 3, "Tetouan", "zfz3");
//
//	Ajouter_Box(box_horizontal3, ville->leLabel, BoxPositionInsertion_Debut, 0, 0, 5);
//	Ajouter_Box(box_horizontal3, combo_ville->combo_box, BoxPositionInsertion_Debut, 0, 0, 5);
//
//
//
//
//
//	Bouton* inscrire = Initialiser_boutton("S'inscrire", "vide", "vide", 25, 10, 1, 160, 200);
//	inscrire = Creer_SimpleBoutton(inscrire);
//
//
//
//	lefixed = Ajouter_Fixed(box_horizontal2->mon_box,50 ,50, lefixed);
//
//	lefixed = Ajouter_Fixed(box_horizontal1->mon_box, 50,100, lefixed);
//
//
//	lefixed = Ajouter_Fixed(box_horizontal3->mon_box,50,150, lefixed);
//
//	lefixed = Ajouter_Fixed(inscrire->Mabouton->button,150, 200, lefixed);
//
//
//
//
//
//
//
//
//
//
//
//
//
//	Ajouter_fenetre(window, lefixed->mon_fixed);
//		g_signal_connect(window->ma_fenetre, "delete_event", gtk_main_quit, NULL);
//
//	gtk_widget_show_all(window->ma_fenetre);
//	gtk_main();
//
//	return(int)0;
//}
