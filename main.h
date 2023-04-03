#include "Macros.h"
#include "libxml2/libxml/parser.h"
void  entry_call_back(GtkEntry*entry)
{
    const gchar *text = gtk_entry_get_text(GTK_ENTRY(entry));
    guint16 lenght = gtk_entry_get_text_length(GTK_ENTRY(entry));
    g_print("text:%s |lenght:%d", text, lenght);
    gtk_entry_set_text(GTK_ENTRY(entry), "");
}

int main(int argc, char *argv[])
{
//-------------------------------------     Initialisation de GTK     --------------------------------------------------
    gtk_init(&argc, &argv);

//----------------------------------------------------------------------------------------------------------------------
//-------------------------------------     Création de la fenêtre    --------------------------------------------------
    Fenetre* wind;
    wind = Allouer_Fenetre(WINDOW_TOPLEVEL, 100, 100, "salma", NULL, 200, 0, 0, "#FFF000", "titre");
    wind = Creer_Fenetre(wind);
    GtkWidget *fixed;
    fixed = gtk_fixed_new();
    Entree *tt=Entry_init("ceci est un texte",'\0',"rrrr",400,700);
    tt=Creer_Entree(tt);
   g_signal_connect(tt->entry,"activate",G_CALLBACK(entry_call_back),NULL);
        /*-----------------Switch---------------------*/
    Switch*SWitch= Creer_Switch(1,300,400);
    /*-----------------Search---------------------*/
    Search*my_search= Creer_Search("salma",100,200);
    g_signal_connect(my_search->search,"activate",G_CALLBACK(entry_call_back),NULL);
    gtk_container_add(GTK_CONTAINER(wind->ma_fenetre), fixed);
    gtk_fixed_put(GTK_FIXED(fixed), tt->entry,300,300);
    gtk_fixed_put(GTK_FIXED(fixed), SWitch->my_switch,500,300);
    gtk_fixed_put(GTK_FIXED(fixed), my_search->search,700,300);


    // Affichage de la fenêtre
    gtk_widget_show_all(wind->ma_fenetre);
    g_signal_connect_swapped(G_OBJECT(wind->ma_fenetre), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    // Boucle principale de GTK
    gtk_main();
    return 0;
}



